# include <iostream>
# include <list>
# include <vector>

template<template<typename,typename> class C, typename K, typename Allocator> C<K,Allocator> init_vector(int ni, C<K,Allocator>& v)
{
    for ( int i = 0; i < ni; ++i) v.push_back(i+1.);
    return v;
}

template<template<typename,typename> class C> C<double,std::allocator<double>> init_vector(int ni) {
    C<double,std::allocator<double>> v;
    for ( int i = 0; i < ni; ++i) v.push_back(i+1.);
    return v;
}

int main() {
    auto z = init_vector<std::list>(10);
    for ( auto x : z ) std::cout << x << " ";

    std::vector<double> v;
    init_vector(10,v);
    for ( auto x : v ) std::cout << x << " ";
    std::cout << std::endl;
    //
    std::list<double> l;
    init_vector(10,l);
    for ( auto x : l ) std::cout << x << " ";
    std::cout << std::endl;
    
    return EXIT_SUCCESS;
}