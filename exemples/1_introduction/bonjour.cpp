// Ceci est un commentaire sur une ligne
#include <iostream> // <--- inclusion module d'affichage
#include <string> // <--- module chaîne de caractères 

/* Fonction disant bonjour à <nom>
   Input : <nom> le nom de la personne à qui
                 le programme dit bonjour.
*/
void dit_bonjour ( const std::string& nom ) {
  std::cout << "Bonjour " << nom << "!" << std::endl;
}

/* Programme principal */
int main (int nargs, const char* argv[]) {
    if (nargs == 1) return EXIT_FAILURE;
    dit_bonjour( argv[1]);
    return EXIT_SUCCESS;
}