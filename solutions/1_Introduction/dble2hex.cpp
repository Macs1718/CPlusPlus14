#include <iostream>
#include <iomanip>
#include <string>

union double2short {
    double x;
    short si[4];
};

int main( int nargs, char* args[] )
{
    double2short dsx;
    double x = 3.1415;
    if (nargs > 1) x = std::stod(args[1]);
    dsx.x = x;
    std::cout << x << " = " << std::hex << dsx.si[0] << " " << dsx.si[1] << " " << dsx.si[2] << " " << dsx.si[3] << std::endl;
    return EXIT_SUCCESS;
}