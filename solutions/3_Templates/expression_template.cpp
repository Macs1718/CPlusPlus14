#include <iostream>
#include <array>
#include <iterator>
#include <list>

template<typename OutputIterator, typename InputIterator, std::size_t N> struct Sum_generator {
    static void eval( const OutputIterator& iter_c, const InputIterator& iter_a, const InputIterator& iter_b ) {
        (*iter_c) = (*iter_a) + (*iter_b);
        Sum_generator<OutputIterator,InputIterator,N-1>::eval(std::next(iter_c), std::next(iter_a), std::next(iter_b));
    }
};

template<typename OutputIterator, typename InputIterator> struct Sum_generator<OutputIterator, InputIterator,1> {
    static void eval( const OutputIterator& iter_c, const InputIterator& iter_a, const InputIterator& iter_b ) {
        (*iter_c) = (*iter_a)+(*iter_b);
    }
};

template<std::size_t N, typename OutputIterator, typename InputIterator>
inline void add( const OutputIterator& w, const InputIterator& u, const InputIterator& v ) {
    Sum_generator<OutputIterator,InputIterator,N>::eval(w,u,v);
}
int main() {
    std::array<double,4> u = {1.,2.,3.,4.};
    std::array<double,4> v = {4.,3.,2.,1.};
    std::array<double,4> w;
    add<4>(w.begin(),u.begin(),v.begin());
    std::cout << "u+v = { ";
    for ( auto c : w ) std::cout << c << " ";
    std::cout << "}" << std::endl;
    std::list<int> li = {1,2,3,4};
    std::list<int> lj = {4,3,2,1};
    std::array<int,4> wi;
    add<4>(wi.begin(), li.begin(), lj.begin());
    std::cout << "li+lj = { ";
    for ( auto c : wi ) std::cout << c << " ";
    std::cout << "}" << std::endl;
    return 0;
}
