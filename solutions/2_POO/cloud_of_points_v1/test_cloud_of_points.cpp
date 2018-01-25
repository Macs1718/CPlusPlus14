# include "cloud_of_points.hpp"
using namespace Geometry;

int main()
{
    CloudOfPoints cld{ Point{1.,0.,0.}, Point{0.,1.,0.}};
    std::cout << cld << "\n" << std::string(cld) << std::endl;
    return EXIT_SUCCESS;
}