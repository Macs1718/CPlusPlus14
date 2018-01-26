# include <iostream>
# include "Rotation2D.hpp"
int main()
{
    Geometry::vecteur<double> v = { 1., 1. };
    Geometry::rotation_2d r(3.1415/2.);

    auto w = r * v;
    std::cout << "w : " << w[0] << "," << w[1] << std::endl;

    return EXIT_SUCCESS;
}