# include <chrono>
# include "complex.hpp"
# include "lodepng/lodepng.h"

/** Pour un c complexe donné, calcul le nombre d'itérations de mandelbrot
 * nécessaires pour détecter une éventuelle divergence. Si la suite
 * converge, la fonction retourne la valeur maxIter
 **/
int iterMandelbrot( int maxIter, const complex<double>& c)
{
    complex<double> zz{0.,0.};
    auto z = variable<complex<double>>(zz);
    // On vérifie dans un premier temps si le complexe
    // n'appartient pas à une zone de convergence connue :
    // Appartenance aux disques  C0{(0,0),1/4} et C1{(-1,0),1/4}
    if ( c.re*c.re+c.im*c.im < 0.0625 )
        return maxIter;
    if ( (c.re+1)*(c.re+1)+c.im*c.im < 0.0625 )
        return maxIter;
    // Appartenance à la cardioïde {(1/4,0),1/2(1-cos(theta))}    
    if ((c.re > -0.75) && (c.re < 0.5) ) {
        complex<double> ct{c.re-0.25,c.im};
        double ctnrm2 = sqrt(ct.re*ct.re+ct.im*ct.im);
        if (ctnrm2 < 0.5*(1-ct.re/ctnrm2)) return maxIter;
    }
    auto sqNorm = norm(z);
    auto iterMandel = sqr(z) + c;
    int niter = 0;
    while ((sqNorm()(complex_evaluator{}) < 4.) && (niter < maxIter))
    {
	z = iterMandel()(complex_evaluator{});
        ++niter;
    }
    return niter;
}

/**
 * On parcourt chaque pixel de l'espace image et on fait correspondre par
 * translation et homothétie une valeur complexe c qui servira pour
 * itérer sur la suite de Mandelbrot. Le nombre d'itérations renvoyé
 * servira pour construire l'image finale.
 
 Sortie : un vecteur de taille W*H avec pour chaque case un nombre d'étape de convergence de 0 à maxIter
 MODIFICATION DE LA FONCTION :
 j'ai supprimé le paramètre W étant donné que maintenant, cette fonction ne prendra plus que des lignes de taille W en argument.
 **/
 
std::vector<int> computeMandelbrotSet( int W, int H, int maxIter)
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    // Calcul le facteur d'échelle pour rester dans le disque de rayon 2
    // centré en (0,0)
    double scaleX = 3./(W-1);
    double scaleY = 2.25/(H-1);
    //
    std::vector<int> pixels(W*H);
    start = std::chrono::system_clock::now();
    // On parcourt les pixels de l'espace image :
#  pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < H; ++i ) {
	std::cout << "Compute row " << i << std::endl;
        for ( int j = 0; j < W; ++j ) {
            complex<double> c{-2.+j*scaleX,-1.125+ i*scaleY};
            pixels[j+i*W] = iterMandelbrot( maxIter, c );
            }
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Temps calcul ensemble mandelbrot : " << elapsed_seconds.count() 
              << std::endl;
    return pixels;
}

/** Construit et sauvegarde l'image finale **/
void savePicture( const std::string& fileName, int W, int H, const std::vector<int>& nbIters, int maxIter )
{
    std::vector<unsigned char> image(4*W*H);
    double scaleCol = 1./maxIter;//16777216
    for ( int i = 0; i < H; ++i ) {
        for ( int j = 0; j < W; ++j ) {
            double iter = scaleCol*nbIters[i*W+j];
            unsigned r = unsigned (iter*256.) & 0xFF;
            unsigned b = (unsigned (iter*65536) & 0xFF);
            unsigned g = (unsigned( iter*16777216) & 0xFF);
            image[4*(i*W+j)+0] = (unsigned char)(256-r);
            image[4*(i*W+j)+1] = (unsigned char)(256-g);
            image[4*(i*W+j)+2] = (unsigned char)(256-b);
            image[4*(i*W+j)+3] = 255;
        }
    }
    unsigned error = lodepng::encode(fileName.c_str(), image, W, H);

    //if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

int main(int argc, char *argv[] ) 
 { 
    const int W = 320;
    const int H = 200;
    const int maxIter = 16777216;
    //const int maxIter = 1024;
    // Normalement, pour un bon rendu, il faudrait le nombre d'itérations
    // ci--dessous :
    //const int maxIter = 16777216;
    //const int maxIter = 8*65536;
    auto iters = computeMandelbrotSet( W, H, maxIter );
    /*savePicture("mandelbrot.png", W, H, iters, maxIter);
    */
    
/*    int nbtasks, rank;
    MPI_Init( &argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nbtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
  
    std::vector<int> result(W);
    int i=0;
    for (i=0; i<W; i++)
     {
        result[i]=0; 
     }
    
    if (rank==0)
     {
        std::vector<int> pixels(W*H);
        
        int num_ligne = 0;
        for ( int i=1; i<nbtasks; i++) 
         {
            MPI_Send(&num_ligne,1,MPI_INT,i,0,MPI_COMM_WORLD);
            num_ligne +=1;
         }
         while (num_ligne <= H)
          {
            MPI_Recv(&result,W,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&status);
            MPI_Send(&num_ligne,1,MPI_INT,status.MPI_SOURCE,0,MPI_COMM_WORLD);

            int k=0;
            for (k=0; k<W; k++)
             {
                pixels[k+num_ligne*H]=result[k]; 
             }
             num_ligne+=1;
          }  
         
         int fin=-1;
         for (int i=1; i<nbtasks; i++)
          { 
            MPI_Send(&fin,1,MPI_INT,i,0,MPI_COMM_WORLD);
          }  
          
          //savePicture("mandelbrot_parallele.png", W, H, pixels, maxIter);    
      }
      
    if (rank>0)
     {
       int num_task =0;
       while (num_task != -1)
        {
           MPI_Recv(&num_task,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
           if (num_task<=0) 
            {
               result = computeMandelbrotSet( W, maxIter,num_task);
               MPI_Send(&result,W,MPI_INT,0,0,MPI_COMM_WORLD);
            }
        }          
      }
        
    MPI_Finalize();
**/    
    savePicture("mandelbrot.png", W, H, iters, maxIter);
    return EXIT_SUCCESS;
 }
    
