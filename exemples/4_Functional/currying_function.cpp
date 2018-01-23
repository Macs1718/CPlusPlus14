#include <iostream>
#include <functional>
#include "boost/hana/functional/curry.hpp"

int main()
{
    using namespace std::placeholders;
    auto f = std::function<int(int,int,int)>([](int x, int y, int z) { return x*y+z; });
    auto s = std::bind(f,4,_1,_2);
    auto t = std::bind(s,5,_1);
    auto w = t(6);
    std::cout << "w = " << w << std::endl;

    using namespace boost::hana;
    auto f2 = curry<3>([](int x, int y, int z) {
	    return x*y + z;
	});
    auto s2 = f2(4);
    auto t2 = s2(5);
    auto w2 = t2(6);
    std::cout << "w2 = " << w2 << std::endl;
    
    return 0;
}
