# include "expression_template.hpp"

template<typename K>
struct complex {
    K re, im;
    complex(const K& v) : re(v),im(0) {}
    complex(const K& x, const K& y) : re(x), im(y) {}
};

template<typename K>
struct expr_traits<complex<K>>
{
    using type=constante_<complex<K>>;
};

template<typename K>
std::ostream& operator << ( std::ostream& out, const complex<K>& c )
{
    out << c.re << "+" << c.im <<"i";
    return out;
}

struct complex_evaluator {
    template<typename K>
    auto operator() ( typename constante_<K>::tag, const K& v) { return v; }
    template<typename K>
    K operator() ( typename variable_<K>::tag, const K& v) { return v; }
    template<typename K>
    complex<K> operator() (sum_op_tag, const complex<K>& e1, const complex<K>& e2 ) { return {e1.re+e2.re,e1.im+e2.im}; }
    template<typename K>
    complex<K> operator() (sum_op_tag, const complex<K>& e1, const K& e2 ) { return {e1.re+e2,e1.im}; }
    template<typename K>
    complex<K> operator() (sub_op_tag, const complex<K>& e1, const complex<K>& e2) { return {e1.re-e2.re,e1.im-e2.im}; }
    template<typename K>
    complex<K> operator() (sub_op_tag, const complex<K>& e1, const K& e2) { return {e1.re-e2,e1.im}; }
    template<typename K>
    complex<K> operator() (mul_op_tag, const complex<K>& e1, const complex<K>& e2) { return {e1.re*e2.re-e1.im*e2.im,e1.re*e2.im+e1.im*e2.re}; }
    template<typename K>
    complex<K> operator() (mul_op_tag, const complex<K>& e1, const K& e2) { return {e1.re*e2,e1.im*e2}; }
    template<typename K>
    complex<K> operator() (div_op_tag, const complex<K>& e1, const complex<K>& e2) { K nrm2 = e2.re*e2.re+e2.im*e2.im; return {(e1.re*e2.re+e1.im*e1.im)/nrm2,(e1.im*e2.re-e1.re*e2.im)/nrm2}; }
    template<typename K>
    complex<K> operator() (div_op_tag, const complex<K>& e1, const K& e2) { return {e1.re/e2,e1.im/e2}; }
    template<typename K>
    complex<K> operator() (usub_op_tag, const K& e) { return -e; }
    template<typename K>
    K operator() (norm_tag, const complex<K>& z) { return z.re*z.re+z.im*z.im; }
    template<typename K>
    complex<K> operator() (sqr_tag, const complex<K>& z) { return {z.re*z.re-z.im*z.im,2.*z.re*z.im}; }
/*template<typename Expr>
  complex<K> operator() (sqrt_tag, const Expr& e ) { return std::sqrt(e); }*/
};

#if defined(TESTING)
// tests
// -----------
int main()
{
    auto z = variable<complex<double>>(complex<double>{1.,1.});
    auto t = z + (z*z)/2.;
    auto zr = t()(complex_evaluator{});
    std::cout << "z retourne : " << zr.re << " + " << zr.im << "i" << std::endl;
    return 0;
}
#endif
