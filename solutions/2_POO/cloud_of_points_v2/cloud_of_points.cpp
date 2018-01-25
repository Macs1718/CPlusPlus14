// cloud_of_points.cpp
#include <sstream>
#include <algorithm>
#include "cloud_of_points.hpp"

// ----------------------------------------------------------------------
std::ostream& Geometry::CloudOfPoints::save( std::ostream& out ) const
{
    out << size() << " ";
    for ( const auto& p : m_arr_vtx ) out << p[0] << " " << p[1] << " " << p[2] << "\t";
    out << std::endl;
    return out;
}
// ----------------------------------------------------------------------
Geometry::CloudOfPoints::operator std::string() const
{
    std::ostringstream sout;
    sout << "{\t";
    for ( std::size_t i = 0; i < (size() > 2 ? 2 : size()); ++i)
    {
      const Point& p = m_arr_vtx[i];
      sout << "[ " << p[0] << ", " << p[1] << ", " << p[2] << " ]\t";
    }
    if (size() > 2) {
        const Point& p = m_arr_vtx[size()-1];
        sout << "...\t[ " << p[0] << ", " << p[1] << ", " << p[2] << " ]\t";
    }
    sout << "}";
    return sout.str();
}
// ----------------------------------------------------------------------
Geometry::CloudOfPoints Geometry::CloudOfPoints::operator +( const Geometry::CloudOfPoints& cld ) const
{
    Geometry::CloudOfPoints cld3(cld.size()+size());
    std::copy(begin(), end(), cld3.begin());
    std::copy(cld.begin(), cld.end(), cld3.begin()+size());
    return cld3;
}
// ----------------------------------------------------------------------
Geometry::CloudOfPoints& Geometry::CloudOfPoints::operator +=( const Geometry::Point& pt )
{
    for ( auto& p : *this ){
        p[0] += pt[0]; p[1] += pt[1]; p[2] += pt[2];
    }
    return *this;
}
// ----------------------------------------------------------------------
Geometry::Point Geometry::CloudOfPoints::barycenter() const
{
    Point bary{0.,0.,0.};
    for ( const auto& p : *this ) {
        bary[0]+=p[0];
        bary[1]+=p[1];
        bary[2]+=p[2];
    }
    bary[0] /= size();
    bary[1] /= size();
    bary[2] /= size();
    return bary;
}