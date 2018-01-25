# include <iostream>
# include <set>
# include <cctype>

int main(int nargs, char* argv[] )
{
    if ( nargs < 2 ) {
        std::cout << "Usage : stat_string blablabla" << std::endl;
        return 1;
    }
    std::string s(argv[1]);
    std::set<char> characters;
    int nbNum = 0, nbAlpha = 0, nbSpace = 0, nbOther = 0;
    for ( auto c  : s ) {
        if (isalpha(c)) nbAlpha ++;
        else if (isdigit(c)) nbNum++;
        else if (isspace(c)) nbSpace++;
        else nbOther++;
        characters.insert(c);        
    }
    std::cout << "Nombre de lettres : " << nbAlpha << std::endl;
    std::cout << "Nombre de chiffres : " << nbNum << std::endl;
    std::cout << "Nombre d'espaces : " << nbSpace << std::endl;
    std::cout << "Autres : " << nbOther << std::endl;
    std::cout << "caractères trouvés : ";
    for ( auto c : characters ) std::cout << c << ' ';
    std::cout << std::endl;
    return EXIT_SUCCESS;
}