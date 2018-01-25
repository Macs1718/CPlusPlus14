#include <string>
#include <iostream>

using value_t = float;

int main( int nargs, char* args[] )
{
    if (nargs != 4 ) {
        std::cerr << "Usage : calc x1 x2 op" << std::endl;
        return EXIT_FAILURE;
    }    
    value_t x1 = value_t(std::stod(args[1]));
    value_t x2 = value_t(std::stod(args[2]));
    value_t res;
    char op = args[3][0];
    switch(op) {
        case '+':
          res = x1 + x2;
          break;
        case '-':
          res = x1 - x2;
          break;
        case 'x':
          res = x1 * x2;
          break;
        case '/':
          res = x1 / x2;
          break;
        default:
          std::cerr << "Operation inconnue" << std::endl;
          return EXIT_FAILURE;
    }
    std::cout << x1 << op << x2 << "=" << res << std::endl;
    return EXIT_SUCCESS;          
}