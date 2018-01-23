# include <iostream>
# include <iomanip>

// On utilise la méthode de Newton pour trouver la racine carrée de x:
// x_n+1 = x_n - f(x_n)/f'(x_n) = x_n - (x_n²-x)/(2.x_n)
double constexpr sqrt_NewtonRaphson( double x, double curr, double prev ) 
{ return curr == prev ? curr : sqrt_NewtonRaphson(x, 0.5*(curr +  x/curr), curr ); }
// On gère quand même les cas où la racine n'existe pas !
double constexpr cst_sqrt(double x)
{ return x >= 0 && x < std::numeric_limits<double>::infinity() ?
                   sqrt_NewtonRaphson(x,x,0) : std::numeric_limits<double>::quiet_NaN(); }

// Calcul de la racine d'un vecteur 3D en expression constante
double constexpr normL2( double x, double y, double z ) { return cst_sqrt(x*x+y*y+z*z); }
/* Le calcul de pi peut se faire à l'aide d'une triple suite. Cette formule double 
   en décimal le nombre de chiffre exact après la virgule à chaque itération.
   Cette formule est inspirée de celle de brent - salamin ( 1976 ) :
   A_0 = 1;          A_n+1   = (A_n + B_n)/2.
   B_0 = sqrt(1/2);  B_{n+1} = sqrt(A_n * B_n)
   C_0 = 1/4;        C_{n+1} = C_{n} - 2^{n}*((A_n-B-n)/2)²
   et on calcul pi_n comme pi_n = (A_n+B_n)²/(4*C_n)
*/

double constexpr brent_salamin( int n, double an, double bn, double cn,
                                double cur, double prev ) {
  return cur == prev ? cur : brent_salamin(n+1, 0.5*(an+bn), cst_sqrt(an*bn),
                         cn - (1<<n)*0.25*(an-bn)*(an-bn), 0.25*(an+bn)*(an+bn)/cn, cur);
}
int main()
{
    const int constexpr N = 100;
    const int constexpr M = N + 21;
    const int constexpr O = ( M%2 == 0 ? M/2 : 3*N+1);
    const double constexpr sqrt2 = cst_sqrt(2);
    const double constexpr sqr3 = normL2(1.,1.,1.);
    const double constexpr pi = brent_salamin(0,1.,cst_sqrt(0.5),0.25,3.,0.);
    double x = 3, y = 5, z = 8;
    double nrmp = normL2(x,y,z);
    std::cout << O << " sqrt(2) -> " << std::setprecision(10)  << sqrt2 << " pi = " << pi << " sqrt(3) = " << sqr3 << " ||u|| = " << nrmp << std::endl;
    return EXIT_SUCCESS;
}