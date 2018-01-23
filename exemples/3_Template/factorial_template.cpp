# include <iostream>

template<typename T, long n> constexpr T factorial = factorial<T,n-1>*T(n);
template<typename T> constexpr T factorial<T,0> = 1L;
int main() {
    std::cout << factorial<long, 5> << std::endl;
    return -1;
}