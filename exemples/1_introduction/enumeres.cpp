#include <iostream>
#include <string>
#include <array>

enum Couleur {
    Black = 0,
    Red   = 1,
    Blue  = 2,
    Violet = Red + Blue,
    Green = 4,
    Maroon = Red + Green,
    Yellow = Blue + Green,
    EndCouleur
};

std::array<std::string,EndCouleur> colourName = { "black", "red", "blue", "violet", "green",
                                                       "marron", "yellow" }; 

int main()
{
    std::cout << "One colour : " << colourName[Yellow] << std::endl;
    return EXIT_SUCCESS;
}