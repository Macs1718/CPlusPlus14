# include <iostream>

int main()
{
    int i = 0;
    int& ref_i = i;
    int j = i;// j vaut 0
    ref_i = 3;// Affecte 3 à la valeur de i et de ref_i
    j = 4;// j vaut 4 et i vaut 3
    std::cout << "i = " << i << " = " << ref_i << " != " << j << std::endl;
    return EXIT_SUCCESS;
}