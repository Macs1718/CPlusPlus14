// Exemples de différents styles de déclarations des variables
#include <complex>  // Pour utiliser des complexes
#include <utility> // nécessaire pour std::unique_ptr et std::shared_ptr
#include <iostream> // pour afficher sur une console
#include <string>   // Pour utiliser les chaînes de caractères
#include <cmath>    // Pour utiliser les fonctions mathématiques usuelles

int main( ) {
    // Les types de base en C++
    // ==========================
    {
// booléens
bool b1, b2, b3; 
b1 = true; b2 = false; 
b3 = b1 or b2; // b3 = true
b3 = b1 and b2;// b3 = false
b3 = b1 xor b2;// b3 = true ( ou exclusif )
b3 = (2>3); // b3 = false;
b3 = b1 and ((2>3) or (3-3==0));
b3 = not b1; // b3 = false
if (b2) { b3 = b1 or b2; } else { b3 = b1 and b2; }
b3 = ( b2 ? b1 or b2 : b1 and b2 );// equiv. ligne au dessus
        std::cout << "b1 = " << b1 << " et b3 = " << b3 << std::endl;
// entiers
signed char ib = 3;// -128 <= ib <= 127
ib += 128;// ib vaut -125 ! 
        std::cout << "ib = " << int(ib) << std::endl;
unsigned char uib = 3; // 0 <= uib <= 255
uib -= 4; // uib vaut 255...
        std::cout << "uib = " << int(uib) << std::endl;
        // Note : ne pas utiliser char car signé ou non signé selon les os
short si = 68; // -32768 <= si <= 32767
si += 32700; // si vaut -32768
        std::cout << "si : " << si << std::endl;
unsigned short usi = 36; // 0<= usi <= 65535
usi += 65500; //usi vaut 0
        std::cout << "usi : " << usi << std::endl;
int i; // -2^31 <= i <= (2^31)-1
unsigned int ui; // 0 <= i <= (2^32)-1
long li; 
unsigned long uli;
long long lli;
unsigned long long ulli;
        // Réels et complexes
float fx; // Réel flottant 32 bits ( simple précision )
double x,y; // Réel flottant 64 bits ( double précision )
long double lx; // Réel étendu
x= 3.14; y = 0.5; x = x + y; y += 2 * x * x; 
y = std::cos(x); // <--- #include <cmath> en début de fichier

std::complex<float> fz; // complexe simple précision
std::complex<double> z; // complexe double précision
std::complex<long double> lz; // complexe précision étendue
std::complex<int> iz;   // complexe d'entiers
x = z.real(); i = iz.imag();
x = std::norm(z); y = std::abs(z);
    }
        // Chaînes de caractères
{
std::string str1,str2, str3;
str1 = "tin"; str2 = "et"; str3 = "Pilou";
str1 += str1 + " " + str3;
size_t pos_pilou = str1.find(str3); str1[pos_pilou] = 'M';
str1[0] = std::toupper(str1[0]);
str1.insert(pos_pilou, str2+" "); std::cout << str1 << std::endl;
int i; double x;
str2 = "123"; str3 = "3.14";
i = std::stoi(str2); x = std::stod(str3);
std::cout << i << " : " << x << std::endl;
str1 = u8"chaînes avec accents en utf8";
str2 = R"RAW(C'est une chaine
        multiligne qui marche bien)RAW";
str3 = u8R"RAW(Caractères utf8 raws !!!!)RAW";
std::cout << str1 << "\n" << str2 << "\n" << str3 << std::endl;
}
    // Alias de type ( C++ 2011 )
    // =================================================================
using dcomplex = std::complex<double>;

    // Déclarations explicites et initialisations de variables
    // =================================================================
    int i0;          // exemple instanciation sans initialisation
    int p1, p2, p3;  // Multiple instanciation sans initialisation
    // Compatible ISO 98
int           i1 = 4, j1 = 2;
double        x1( 0.5 ), y1( 1.3 );
unsigned long u1( 9834541u );
std::size_t   addr1 = 0xFFA2045C;
dcomplex      z1( 0.5, 1.2 );
// Compatible uniquement 2011 ou supérieur :
int           i2{4}, j2{2};
double        x2{3.4}, y2{1.3};
unsigned long u2{9834541u};
std::size_t   addr2{0xFFA2045C};
dcomplex      z2{0.5, 1.2};
// Compatible 2014 ou supérieur :
unsigned long u3 = 9'834'541u;   // Ecriture du nombre avec separateurs
std::size_t   addr3{0xFF'A2'04'5C};  // Idem pour la notation hexadécimale
// Nouvelle écriture binaire en C++ 14 :
std::size_t addr4 = 0b11111111'10100010'00000100'01011110;  // Même adresse que addr3
double ex  = 3'432.4123'6543;
// Indispensable pour utiliser la nouvelle notation pour les complexes
using namespace std::complex_literals;
dcomplex z3 = 0.5 + 1.2i;

    // Pointeur/références et qualifieur const
    // ================================================================
    {
    double* pt_x = &x1; // pointeur 'fondamental' sur x1 = adresse mémoire
    int* pt_i = nullptr; // pointeur sur rien...
    // Créer un nouveau double pointé par un pointeur unique
    std::unique_ptr<double> pt_y = std::make_unique<double>(3.14);
    std::unique_ptr<double> pt_z = std::move(pt_y); // pt_z pointe sur 3.14, pt_y sur nullptr
    std::cout << "z = " << *pt_z << std::endl;
    // Créer un nouveau double pointé par un pointeur partagé
    std::shared_ptr<double> pt_sy = std::make_shared<double>(3.14);
    std::shared_ptr<double> pt_sz = pt_sy; // pt_sy et pt_sz pointe tous les deux sur 3.14
    int nbRef = pt_sz.use_count();// nbRef = 2 car deux pointeurs pointent sur 3.14
    std::cout << "nbRef : " << nbRef << std::endl;
    // les deux valeurs pointées par shared et unique libèrent la mémoire à la fin du bloc
    }
    // Déclarations implicites des variables ( C++ 2011 )
    // ================================================================
    {
auto i  = 1;         // De la valeur à droite de =, on déduit que i est un int
auto x  = 0.5 * i;   // Idem, ici on déduit que x est un double
auto fx = 0.5f * i;  // Et ici, fx est un float
auto& fy = fx; // fy est une reference sur un float
auto const& fz = fx; // et fz une référence constante
auto const* pt_x = &fx; // pointeur  double constant sur pt_x 
// auto z : Interdit car on ne peut pas déduire le type
i = 3.5;  // i prend la valeur 3, car toujours un int !
    }

    // Déclaration déductive des variables ( C++ 2011 )
    // ================================================================
    decltype( 1 + 3.5 )         xx;  // xx est un double car 1+3.5 renvoie un double...
    decltype((i1+x1)) rx = xx; // deduit type double qu'il met en reference
    decltype(x1<0) b = x1<0; // Déduit le type boolean
    decltype( std::norm( z1 ) ) dz;  // dz est double car la fonction std::norm renvoie ici un double
    // decltype permet d'avoir une déduction implicite pour les pointeurs
    using ret_abs_t = decltype(std::abs(z1));
    std::shared_ptr<ret_abs_t> pt_res = std::make_shared<ret_abs_t>(std::abs(z1));

    return EXIT_SUCCESS;
}