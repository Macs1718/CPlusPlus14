# include <vector>
# include <chrono>
# include <iostream>

std::vector<size_t> comp_primes( size_t max_n )
{
    std::vector<size_t> primes;
    primes.reserve(max_n/3+2);
    primes.push_back(2);
    primes.push_back(3);
    for ( int k = 1; k < (max_n-1)/6; ++k)
    {
        int val = 6*k-1;
        bool is_primal = true;
        for ( int i = 0; (i<primes.size()) && (is_primal == true); ++i )
          if ( val%primes[i] == 0 ) is_primal = false;
        if (is_primal) primes.push_back(val);
        val = 6*k+1;
        is_primal = true;
        for ( int i = 0; (i<primes.size()) && (is_primal == true); ++i )
          if ( val%primes[i] == 0 ) is_primal = false;
        if (is_primal) primes.push_back(val);
    }
    primes.shrink_to_fit();
    return primes;
}

int main()
{
    using namespace std::chrono;
    steady_clock::time_point beg = steady_clock::now();
    auto primes = comp_primes(100000);
    steady_clock::time_point end = steady_clock::now();
    auto time_span = duration_cast<duration<double>>(end-beg);
    std::cout << "Time spended for primes: " << time_span.count() << std::endl;
    std::cout << "Primes numbers : ";
    for ( auto v : primes ) std::cout << v << " ";
    std::cout << std::endl;
    return EXIT_SUCCESS;
}
