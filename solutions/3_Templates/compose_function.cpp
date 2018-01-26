# include <iostream>
# include <cmath>

template<typename K, typename F> auto compose(const K& x, F f) { return f(x);  }
template<typename K, typename F, typename... Args>
auto compose( const K& x, const F& f, Args... args )
{
    std::cout << "Nombre de fonctions à composer : " << sizeof...(args) << std::endl;
    return f(compose(x,args...));
}

double dsqrt(double x)
{
    return std::sqrt(x);
}
double dcos(double x)
{
    return std::cos(x);
}

double dabs(double x)
{
    return std::abs(x);
}


int main()
{
    // calcul sqrt(abs(cos(5)));
    auto a = compose(5., dsqrt,dabs,dcos);
    std::cout << "a  = " << a << std::endl;
    return 0;
}