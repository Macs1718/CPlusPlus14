# include <iostream>
# include <cstdlib>

namespace Units
{
  namespace Distance
  {
    class Metre
    {
    public:
      class DoubleIsM{};// A Tag
      explicit constexpr Metre(DoubleIsM, double dist ) : m_dist(dist) {}

      explicit operator double() const { return m_dist; }

      Metre operator + ( const Metre& m )
      {
        return Metre{DoubleIsM{}, m_dist + m.m_dist};
      }

      std::ostream& print( std::ostream& out ) const
      {
        out << m_dist << "m";
        return out;
      }

      template<typename U>
      Metre operator = ( const U& d ) {
       if ( this != &d ) {
         Metre md = Metre(d);
         m_dist = md.m_dist;
       }
       return *this;
      }

    private:
      double m_dist;
    };

    inline std::ostream& operator << ( std::ostream& out, const Metre& m ) {
      return m.print(out);
    }

    class Kilometre
    {
    public:
      class DoubleIsKm{};// A Tag
      explicit constexpr Kilometre(DoubleIsKm, double dist ) : m_dist(dist) {}
      Kilometre( const Metre& d ) : m_dist(0.001*double(d)) {}

      explicit operator double() const { return m_dist; }

      operator Metre()
      {
        return Metre{Metre::DoubleIsM{},1000.*double(m_dist)};
      }

      Kilometre operator + ( const Kilometre& m )
      {
        return Kilometre{DoubleIsKm{}, m_dist + m.m_dist};
      }

      std::ostream& print( std::ostream& out ) const
      {
        out << m_dist << "km";
        return out;
      }

      template<typename U> Kilometre operator = ( const U& d ) {
        if ( this != &d ) {
          Kilometre kd = Kilometre(d);
          m_dist = kd.m_dist;
        }
        return *this;
      }
    private:
      double m_dist;
    };

    inline std::ostream& operator << ( std::ostream& out, const Kilometre& km ) {
      return km.print(out);
    }
    
    namespace operators
    {
      constexpr Kilometre operator"" _km( long double dst )
      {
        return Kilometre{Kilometre::DoubleIsKm{},static_cast<double>(dst)};
      }
      constexpr Metre operator"" _m( long double dst )
      {
        return Metre{Metre::DoubleIsM{}, static_cast<double>(dst)};
      }
    }
  }
}

int main()
{
  using namespace Units::Distance::operators;
  auto d1 = 1.2_km;
  auto d2 = 100.0_m;
  double a = double(d2);
  auto d3 = d2 + d1;
  std::cout << d1 << " + " << d2 << " = " << d3 << std::endl;
  auto d4 = d1 + d2;
  std::cout << d1 << " + " << d2 << " = " << d4 << std::endl;
  std::cout << 5.0_km << " + " << 1235.0_m << " = " << 5.0_km + 1235.0_m << std::endl;
  Units::Distance::Metre d5 = d1 + d2;
  std::cout << d1 << " + " << d2 << " = " << d5 << std::endl;

  Units::Distance::Kilometre d6 = d1 + d2;
  std::cout << d1 << " + " << d2 << " = " << d6 << std::endl;

  return EXIT_SUCCESS;
}
