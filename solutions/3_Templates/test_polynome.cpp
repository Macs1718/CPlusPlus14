#include <iostream>
#include <fstream>
#include "polynome.hpp"

int main()
{
    // p = 0 + x + x^2 + 2.x^{3}
    auto p = poly({0.,1.,1.,2.});
    auto y = p(3.);
    std::cout << "p(3) = " << y << std::endl;
    std::cout << "p :" << std::string(p) << " en 3 = " << y << std::endl;

    auto q = poly({1.,1.});

    auto r = q+p;
/*    auto s = q*p;
*/
    std::cout << "r = " << std::string(r) << std::endl;
/*    std::cout << "s = " << std::string(s) << std::endl;

    std::ofstream fich("poly.dat");
    fich << s;
    fich.close();

    std::ifstream fich2("poly.dat");
    fich2 >> p;
    fich.close();

    std::cout << "p = " << p << std::endl;*/
    // Polynomes à coefficients entiers
    auto p2 = poly({1,3,5});
    std::cout << "p2(2) = " << p2(2) << std::endl;

  return 0;
}