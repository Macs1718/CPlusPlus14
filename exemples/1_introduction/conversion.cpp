# include <iostream>
# include <string>

int main()
{
    // Conversion explicite
{
double x = 1.5;
int    i = int(x);// i = 1
const std::string s("Coucou");
const char* cs = s.c_str();
int* pt_i = (int*)&s;// Fonctionne mais...on ne peut rien en faire.
std::cout << *pt_i << std::endl;
pt_i = (int*)cs;
(*pt_i)++;
std::cout << s << std::endl;// Affiche Doudou sur Arm, ? sur intel
}    
    // Conversion statique
{
double x = 1.5;
int    i = static_cast<int>(x);// i = 1
const std::string s("Coucou");
const char* cs = s.c_str();
// const int * pt_i = static_cast<const int*>(&s); Erreur car ne sait pas comment convertir
const double A[] = {1.,2.,3.};
// double* pt_x = static_cast<double*>(A); Erreur car conversion de const à non const
const double* pt_x = static_cast<const double*>(A);
}
    return EXIT_SUCCESS;
}