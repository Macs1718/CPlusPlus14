// Résolution équation second degré
#include <iostream>
#include <cmath>
#include <cstdlib>

int main()
{
    double a,b,c;
    a = 1;
    b = 4;
    c = -1;
    if ( a == 0 ) {
        std::cerr << u8"a doit être différent de zéro !"
                  << std::endl;
        return EXIT_FAILURE;
    }

    double delta = b*b-4*a*c;
    if ( delta < 0 ) {
        std::cerr << u8"Delta négatif ! " << std::endl;
        return EXIT_FAILURE;
    }
    double x1 = (-b-std::sqrt(delta))/(2*a);
    double x2 = (-b+std::sqrt(delta))/(2*a);
    std::cout << "Les solutions sont " << x1
              << " et " << x2 << std::endl;
    return EXIT_SUCCESS;
}
