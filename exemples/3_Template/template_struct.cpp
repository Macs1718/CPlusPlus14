# include <iostream>
# include <vector>

namespace Algebra {
    template<typename K>
    class Vecteur {
    public:
        using value=K;
        using container=std::vector<K>;
        using reference=typename container::reference;
        using const_reference=typename container::const_reference;
        
        Vecteur() = default;
        Vecteur( std::size_t dim ) : m_arr_coefs(dim)  {}
        Vecteur( const std::initializer_list<K>& l ) : m_arr_coefs(l) {}
        Vecteur( const Vecteur& u ) = default;
        Vecteur( Vecteur&& u ) = default;
        ~Vecteur() = default;
        
        std::size_t dim() const { return m_arr_coefs.size(); }
        reference operator []( std::size_t i)
        { return m_arr_coefs[i]; }
        const_reference operator [] ( std::size_t i ) const
        { return m_arr_coefs[i]; }
        Vecteur operator + ( const Vecteur& u ) const;
    private:
        container m_arr_coefs;
    };
    template<typename K> Vecteur<K>
    Vecteur<K>::operator + ( const Vecteur<K>& u ) const
    {
        Vecteur w(dim());
        for (std::size_t i = 0; i < dim(); ++i )
            w[i] = u[i]+(*this)[i];
        return w;
    }
    template<typename K> std::ostream& operator << ( std::ostream& out, const Vecteur<K>& u )
    {
        out << "{ ";
        for ( std::size_t i = 0; i < u.dim(); ++i ) out << u[i] << " ";
        out << "}";
        return out;
    }
}

int main()
{
    using Algebra::Vecteur;
    Vecteur<double> u={1.,2.,3.};
    Vecteur<double> v={4.,5.,6.};
    auto w = u + v;
    std::cout << u << "+" << v << "=" << w << std::endl;
    return EXIT_SUCCESS;
    
}