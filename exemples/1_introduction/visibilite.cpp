#include <iostream>

int i = 0;

int main()
{
    std::cout << i << std::endl;
    int i = 1; 
    std::cout << i << " != " << ::i << std::endl;
    {
        int i = 2;
        std::cout << i << "!=" << ::i << "!=" << std::endl;
        // Par contre, impossible d'atteindre le i du main...
    }
    return EXIT_SUCCESS;  
}
