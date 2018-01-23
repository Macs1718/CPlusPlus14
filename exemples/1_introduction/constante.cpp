#include <iostream>

int main()
{
    const int A[] = { 1, 2, 3, 4 };
    const int& i = A[0];
    // i = 0 génère une erreur...
    // A[0] = -1; génère une erreur
    //const_cast<int&>(A[0]) = -1;// Comportement indéfini
    const int n = 10;
    double arr[n];
    const double* pt_arr = arr;
    const_cast<double&>(pt_arr[0]) = 3.14;
    std::cout << arr[0] << std::endl;
    //const_cast<int&>(n) = 15;// Compile mais gros bogue !
    double arr2[n];
    std::cout << "n = " << n << std::endl;
    for ( auto& v : A )
        std::cout << v << " ";
    std::cout << std::endl;
    return EXIT_SUCCESS;
}