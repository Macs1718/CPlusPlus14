#include <iostream>
#include <array>
#include <iterator>
#include <list>

template<typename InputIterator, std::size_t N> struct DotProduct_generator {
    static auto eval( const InputIterator& iter_a, const InputIterator& iter_b ) {
        return DotProduct_generator<InputIterator,1>::eval(iter_a,iter_b) + 
               DotProduct_generator<InputIterator,N-1>::eval(std::next(iter_a),std::next(iter_b));
    }
};
template<typename InputIterator> struct DotProduct_generator<InputIterator,1> {
    static auto eval( const InputIterator& iter_a, const InputIterator& iter_b ) {
        return (*iter_a)*(*iter_b);
    }
};
template<std::size_t N, typename InputIterator> inline auto dot( const InputIterator& u, const InputIterator& v ) {
    return DotProduct_generator<InputIterator,N>::eval(u,v);
}
int main() {
    std::array<double,4> u = {1.,2.,3.,4.};
    std::array<double,4> v = {4.,3.,2.,1.};
    std::cout << "(u|v) = " << dot<4>(u.begin(),v.begin()) << std::endl;
    std::list<int> li = {1,2,3,4};
    std::list<int> lj = {4,3,2,1};
    std::cout << "(u|v) = " << dot<4>(li.begin(),lj.begin()) << std::endl;
    return 0;
}