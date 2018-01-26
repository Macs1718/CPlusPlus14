# include <cstdio>
# include <cstdlib>
# include <iostream>
# include <fstream>
# include <vector>


/* Save Bhudda set in gnuplot format
 */
void saveBhudda(int n, const std::vector<int>& bhudda)
{
  FILE* fich = fopen("Bhudda.dat", "w");
  for (int i  = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fprintf(fich,"%d\t%d\t%d\n",i, n-j, bhudda[i*n+j]);
    }
    fprintf(fich, "\n");
  }
  fclose(fich);
}


int
main(int nargc, char* argv[])
{
  double t1,t2;
  int n = 1280;
  int maxIter = 2000;

  if (nargc > 1) n = atoi(argv[1]);
  if (nargc > 2) maxIter = atoi(argv[2]);
  printf("Grid size : %d x %d, Max iterations : %d\n",n,n,maxIter);
  auto bhudda = std::vector<int>(n*n);


  saveBhudda(n,bhudda);

  return EXIT_SUCCESS;
}
