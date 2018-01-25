# include "cloud_of_points.hpp"
using namespace Geometry;

int main()
{
    CloudOfPoints cld{ Point{1.,0.,0.}, Point{0.,1.,0.}};
    CloudOfPoints cld2{ Point{0.,0.,1.}, Point{1.,0.,1.}};
    CloudOfPoints cld3 = cld + cld2;
    std::cout << cld << "\n" << std::string(cld) << std::endl;
    std::cout << std::string(cld3) << std::endl;
    return EXIT_SUCCESS;
}