// cloud_of_points.cpp
#include <sstream>
#include "cloud_of_points.hpp"

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
