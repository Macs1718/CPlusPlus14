# include <iostream>
# include <vector>

namespace Algebra {
    template<typename K>
    class Vecteur {
    public:
        using value=K;
        using container=std::vector<K>;
        using reference=container::reference;
        using const_reference=container::const_reference;
        
        Vecteur() = default;
        Vecteur( std::size_t dim ) : m_arr_coefs(dim)  {}
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
        std::vector<K> m_arr_coefs;
    };
    template<typename K> Vecteur<K>
    Vecteur<K>::operator + ( const Vecteur<K>& u ) const
    {
        Vecteur w(dim());
        for (std::size_t i = 0; i < dim(); ++i )
            w[i] = u[i]+(*this)[i];
        return w;
    }
}