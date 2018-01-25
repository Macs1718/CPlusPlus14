#include <string>
#include <iostream>
#include <stack>

using value_t = float;

int main( int nargs, char* args[] )
{
    if (nargs < 4 ) {
        std::cerr << "Usage : calc x1 x2 op1 x3 op2 ..." << std::endl;
        return EXIT_FAILURE;
    }
    std::stack<value_t> heap;
    for ( int i = 1; i < nargs; ++ i ) {
        try {
            value_t x = value_t(std::stod(args[i]));
            heap.push(x);
        } catch(std::invalid_argument)
        {
            char op = args[i][0];
            if ( heap.size() < 2 ) {
                std::cerr << "Problème de formulation : manque une valeurs ?" << std::endl;
                return EXIT_FAILURE;
            }
            value_t x2 = heap.top();
            heap.pop();
            value_t x1 = heap.top();
            heap.pop();
            switch(op) {
                case '+':
                    heap.push(x1+x2);
                    break;
               case '-':
                    heap.push(x1-x2);
                    break;
               case 'x':
               case '*':
               case '.':
                    heap.push(x1 * x2);
                    break;
               case '/':
                    heap.push(x1 / x2);
                    break;
               default:
                   std::cerr << "Operation inconnue" << std::endl;
                   return EXIT_FAILURE;
            }// End Switch   
        }//End catch
    }// End loop
    if (heap.size() > 1) {
        std::cerr << "Problème de formulation : manque un opérateur binaire ?" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Résultat : " << heap.top() << std::endl;
    return EXIT_SUCCESS;          
}