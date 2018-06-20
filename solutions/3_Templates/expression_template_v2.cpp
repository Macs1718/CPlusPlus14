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

template<std::size_t N, typename C>
inline auto add ( const C& u, const C& v ) {
    C w(u.size());
    Sum_generator<typename C::iterator,typename C::const_iterator,N>::eval(w.begin(),u.cbegin(),v.cbegin());
    return w;
}

template<std::size_t N, typename K>
inline auto add ( const std::array<K,N>& u, const std::array<K,N>& v ) {
    std::array<K,N> w;
    Sum_generator<typename std::array<K,N>::iterator,typename std::array<K,N>::const_iterator,N>::eval(w.begin(),u.cbegin(),v.cbegin());
    return w;
}

int main() {
    std::array<double,4> u = {1.,2.,3.,4.};
    std::array<double,4> v = {4.,3.,2.,1.};
    auto w = add<4>(u,v);
    std::cout << "u+v = { ";
    for ( auto c : w ) std::cout << c << " ";
    std::cout << "}" << std::endl;
    std::list<int> li = {1,2,3,4};
    std::list<int> lj = {4,3,2,1};
    auto wi = add<4>(li, lj);
    std::cout << "li+lj = { ";
    for ( auto c : wi ) std::cout << c << " ";
    std::cout << "}" << std::endl;
    return 0;
}
