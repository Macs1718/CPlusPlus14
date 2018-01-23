#include <iostream>
#include <range/v3/all.hpp>
#include <vector>
using namespace ranges;

// Define a range of all the unsigned shorts:

int main( ) {
    // ===================================
    auto integers = view::iota( 1, 13 );
    std::cout << integers << std::endl;
    std::cout << integers[{2, end - 1}] << std::endl;
    std::vector<int> x{1,2,3,4}, y{9,8,7,6};
    auto zprng = view::zip(x,y);
    for ( auto z : zprng ) 
        std::cout << "(" << z.first << "," << z.second << ") ";
    std::cout << std::endl;
    // ===================================
    auto rng = view::repeat_n( view::iota( 0, 3 ), 3 );
    std::cout << rng << std::endl;
    // ===================================
    std::string hello("Hello, World!");
    auto lower = hello | view::transform([](char c){ return (char)std::tolower(c);});
    std::cout << lower << std::endl;
    // ===================================
    // Calcul les triplets pythagoriciens vérifiant x^2+y^2=z^2
    auto const intsFrom = view::iota;
    auto const ints = [=]( int i, int j ) { return view::take( intsFrom( i ), j - i + 1 ); };
    // Define an infinite range of all the Pythagorean
    // triples:
    auto triples = view::for_each( intsFrom( 1 ), [ints]( int z ) {
        return view::for_each( ints( 1, z ), [=]( int x ) {
            return view::for_each(
                ints( x, z ), [=]( int y ) { return yield_if( x * x + y * y == z * z, std::make_tuple( x, y, z ) ); } );
        } );
    } );

    // Display the first 10 triples
    // Ne marche qu'avec C++ 2017 !
    for ( auto triple : triples | view::take( 10 ) ) {
        std::cout << '(' << std::get< 0 >( triple ) << ',' << std::get< 1 >( triple ) << ',' << std::get< 2 >( triple )
                  << ')' << '\n';
    }
    return 0;
}