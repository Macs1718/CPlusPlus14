#include <iostream>
#include <string>
#include "range/v3/all.hpp"
using namespace ranges;

int main()
{
    auto letters = view::iota('a','g');
    std::cout << letters << '\n';
// prints: {a,b,c,d,e,f,g}
    std::cout << (letters | view::slice(2,5)) << '\n';
// prints : {c,d,e}
    
    auto ints = view::iota(1,100);
    std::cout << ints[{0,5}] << '\n'; 
    std::cout << ints[{end-5,end}] << std::endl;

    std::vector<int> zz{1,3,4,3, 2,4,1};
    auto squared = zz | view::transform([](int i){return i*i;});
    std::cout << squared << std::endl;
    zz |= action::sort | action::unique;
    std::cout << squared << std::endl;
    auto strz = zz | view::transform([](int i){ return std::to_string(i); });
    std::cout << strz << std::endl;
   return 0;
}
