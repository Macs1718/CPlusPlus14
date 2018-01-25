#ifndef _GEOMETRY_CLOUD_OF_POINTS_HPP_
# define _GEOMETRY_CLOUD_OF_POINTS_HPP_
# include <vector>
# include <array>
#include <string>
#include <iostream>
namespace Geometry
{
    using Point=std::array<double,3>;
    class CloudOfPoints {
    public:
        using Container=std::vector<Point>;
        using iterator = Container::iterator;
        using const_iterator = Container::const_iterator;
        // Constructeurs et destructeur
        CloudOfPoints( ) :                        // Constructeur par défaut
            m_arr_vtx()
        {}
        CloudOfPoints( std::size_t nbVertices ) :  // Constructeur instanciant nbVertices sommets
            m_arr_vtx(nbVertices)
        {}
        CloudOfPoints( const CloudOfPoints& cop ) :// Constructeur de copie
            m_arr_vtx(cop.m_arr_vtx)
         {}        
        CloudOfPoints( std::size_t beg,           // Constructeur recopiant les sommets de veg à end non compris 
                       std::size_t end, const CloudOfPoints& cop ) :
            m_arr_vtx(cop.m_arr_vtx.data()+beg, cop.m_arr_vtx.data()+end)
        {}
        CloudOfPoints( const std::initializer_list<Point>& lst_pts ) : // Initialise le nuage de points avec ses valeurs.
            m_arr_vtx(lst_pts)
        {}
        CloudOfPoints( CloudOfPoints&& cop ) = default;
        
        ~CloudOfPoints() = default;
        
        CloudOfPoints& operator = ( const CloudOfPoints& cld ) = default;
        CloudOfPoints& operator = ( CloudOfPoints& cld ) = default;
        
        std::ostream& save( std::ostream& out ) const;
        explicit operator std::string() const;

        Point& operator [] ( std::size_t i ) { return m_arr_vtx[i]; }
        const Point& operator [] ( std::size_t i ) const { return m_arr_vtx[i]; }
                        
        std::size_t size() const { return m_arr_vtx.size(); }
        
        CloudOfPoints operator + ( const CloudOfPoints& cld ) const;
        CloudOfPoints& operator += ( const Point& pt );
        Point barycenter() const;
        
        iterator begin() { return m_arr_vtx.begin(); }
        const_iterator begin() const { return cbegin(); }
        const_iterator cbegin() const { return m_arr_vtx.cbegin(); }
        iterator end() { return m_arr_vtx.end(); }
        const_iterator end() const { return cend(); }
        const_iterator cend() const { return m_arr_vtx.cend(); }
    private:
        Container m_arr_vtx;
    };
    inline std::ostream& operator << ( std::ostream& out, const CloudOfPoints& cld )
    {
        return cld.save(out);
    }
    
}

#endif