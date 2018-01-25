// Aire signée
# include <array>
# include <iostream>

using Point = std::array<double,2>;
using Vect  = std::array<double,2>;

struct Triangle {
    Point p1, p2, p3;
};

int main()
{
    const Point p = { 0., 0. };
    const Triangle T = { .p1 = {-1., -1.}, .p2 = { +1., -1. }, .p3 = { 0., +1. } };
    Vect edge1 = { T.p1[0] - p[0], T.p1[1] - p[1] };
    Vect edge2 = { T.p2[0] - p[0], T.p2[1] - p[1] };
    Vect edge3 = { T.p3[0] - p[0], T.p3[1] - p[1] };
    double n1  = edge1[0]*edge2[1] - edge1[1]*edge2[0];
    double n2  = edge2[0]*edge3[1] - edge2[1]*edge3[0];
    double n3  = edge3[0]*edge1[1] - edge3[1]*edge1[0];
    if ( (n1*n2 >= 0) && (n2*n3>=0) ) std::cout << "Point interne au triangle" << std::endl;
    else std::cout << "Point externe au triangle" << std::endl;
    return EXIT_SUCCESS;
}