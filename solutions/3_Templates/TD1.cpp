#include <iostream>
#include <cmath>
#include <complex>

template<typename K> K pow_n(const K& x, int n)
{
    if (n==0) return 1;
    if (n==1) return x;
    K res = K(0);
    if (n%2==0) {
        K y = pow_n(x,n/2);
        res = y*y;
    }
    else {
        res = x * pow_n(x,n-1);
    }
    return res;
}

template<typename K, K v, int n> constexpr K dpow_n=K(n%2==0 ? dpow_n<K,v*v,n/2> :
                     v *dpow_n<K,v,n-1>);
template<typename K,K v> constexpr K dpow_n<K,v,1> = v;
template<typename K,K v> constexpr K dpow_n<K,v,0> = K(1);

template<typename K> auto norm( const K& x, const K& y )
{
    return std::sqrt(x*x+y*y);
}

template<typename K> auto norm( const std::complex<K>& x,
                                const std::complex<K>& y )
{
    return std::sqrt(std::norm(x)*std::norm(y));
} 

template<int n> long fibraction() { 
    return fibraction<n-2>() - fibraction<n-1>(); }

template<> long fibraction<1>() { return 1L; }
template<> long fibraction<2>() { return 2L; }

int main()
{
    std::cout << pow_n(3.,5) << std::endl;
    std::cout << dpow_n<long,3,5> << std::endl;

    auto nrm1 = norm(1.,1.);
    auto nrm2 = norm( std::complex<double>{1.,1.},
                      std::complex<double>{1.,1.} );
    std::cout << "nrm1 = " << nrm1 << " et nrm2 = " << nrm2 << std::endl;

    std::cout << fibraction<32>() << std::endl;
    return 0;
}