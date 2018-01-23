# include <array>
# include <iostream>
# include <cassert>

int main()
{
    std::array<int,10> primes= {2,3,5,7,11,13,17,19,23,27};
    decltype(primes) primes2(primes);
    for (auto r_it=primes.crbegin(); r_it!=primes.crend(); ++r_it) std::cout << (*r_it) << " ";
    std::cout << std::endl;
    primes[9] = 29; // 27 n'était pas un nombre premier, on corrige !
    for ( const auto& v : primes ) std::cout << v << " "; std::cout << std::endl;
    std::cout<<"nbre élt dans tableau : "<<primes.size()<<" == "<<primes.max_size()<<std::endl;
    std::cout<<"1er élt : "<<primes.front()<<", dernier : "<<primes.back()<<std::endl;
    try { primes.at(10) = 31; } catch ( std::out_of_range& ) {
        std::cerr << "Pas de 11ème élt pour ce tableau" << std::endl; }
    auto p = std::get<4>(primes);// Le calcul pour l'accès au 5e élt se fait à la compilation
    if (false==primes.empty()){if (primes==primes2) std::cerr << "Ne devrait plus être égaux"<<std::endl;}
    assert(primes != primes2 );
    return EXIT_SUCCESS;
}