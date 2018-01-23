# include <iostream>
# include <vector>
# include <algorithm>

int main()
{
    std::vector<std::size_t> fermat(20), primes; primes.reserve(20);
    for (std::size_t i=0; i<20; ++i) fermat[i]=(1UL<<i)+1UL;
    for (std::size_t i = 0; i<20; ++i) {
        bool is_mul = false;
        for ( auto v : primes ) if (fermat[i]%v==0) { is_mul=true; break; }
        if (is_mul==false) primes.push_back(fermat[i]);
    }
    fermat.swap(primes);
    std::cout << "Nbre de fermat premiers : " << fermat.size() << " sur " << fermat.capacity() << std::endl;
    std::for_each(fermat.begin(),fermat.end(),
                  [](std::size_t i){std::cout<<i<<" ";});
    std::cout<<std::endl;
    fermat.shrink_to_fit(); std::cout << "Nvelle capacité :" << fermat.capacity() << std::endl;
    return EXIT_SUCCESS;
}
