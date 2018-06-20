#include <iostream>
#include <range/v3/all.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/format.hpp>
#include <vector>
using namespace ranges;
namespace greg = boost::gregorian;
using date=greg::date;
using day = greg::date_duration;


namespace boost { namespace gregorian {
    date& operator ++(date& d ) { return d = d + day(1); }
    date operator ++(date &d, int i) { return ++d - day(1); }
}}

namespace ranges {
    template<> struct difference_type<date> {
        using type = date::duration_type::duration_rep::int_type;
    };
}
CONCEPT_ASSERT(Incrementable<date>());

// Manipulating dates
auto dates_in_year(int year) {
    return view::iota(date{year,greg::Jan,1},
                      date{year+1,greg::Jan,1});
}

auto by_month() {
    return view::group_by([](date a, date b) {
        return a.month() == b.month();
    });
}

auto by_week() {
    return view::group_by([](date a, date b) {
        // ++a car week_number est de Lundi à Dimanche et on veut de Dimanche à Samedi
        return (++a).week_number() == (++b).week_number();
    });
}

auto month_by_week() {
    return view::transform([](auto month) {
        return month | by_week();
    });
}

std::string format_day(date d)
{
    return boost::str(boost::format("%|3|") % d.day());
}

// In : Range<Range<date>>: mois regroupés par semaines
// Out: Range<std::string>: mois avec semaines formatées
auto format_weeks() {
    return view::transform([](auto week) {
        return boost::str(boost::format("%1%%2%%|22t|") 
                          %std::string((int)front(week).day_of_week() *3, ' ' )
                          % (week | view::transform(format_day)| action::join));
    });
}

// In : Range<Range<date>>: année des mois des jours 
// Out: Range<Range<std::string>>: année des mois des semaines formatées
auto layout_months() {
    return view::transform([]( auto month ) {
        return month | by_week() | format_weeks();
    });
}

int main( ) {
    // ===================================
    auto integers = view::iota( 1, 13 );
    std::cout << integers << std::endl;
    std::cout << integers[{2, end - 1}] << std::endl;
    std::vector<int> x{1,2,3,4}, y{9,8,7,6};
    auto zprng = view::zip(x,y);
    for ( auto z : zprng ) 
        std::cout << "(" << z.first << "," << z.second << ") ";
    std::cout << std::endl;
    // ===================================
    auto rng = view::repeat_n( view::iota( 0, 3 ), 3 );
    std::cout << rng << std::endl;
    // ===================================
    std::string hello("Hello, World!");
    auto lower = hello | view::transform([](char c){ return (char)std::tolower(c);});
    std::cout << lower << std::endl;
    // ===================================
    // Calcul les triplets pythagoriciens vérifiant x^2+y^2=z^2
    auto const intsFrom = view::iota;
    auto const ints = [=]( int i, int j ) { return view::take( intsFrom( i ), j - i + 1 ); };
    // Define an infinite range of all the Pythagorean
    // triples:
    auto triples = view::for_each( intsFrom( 1 ), [ints]( int z ) {
        return view::for_each( ints( 1, z ), [=]( int x ) {
            return view::for_each(
                ints( x, z ), [=]( int y ) { return yield_if( x * x + y * y == z * z, std::make_tuple( x, y, z ) ); } );
        } );
    } );

    // Display the first 10 triples
    // Ne marche qu'avec C++ 2017 !
    for ( auto triple : triples | view::take( 10 ) ) {
        std::cout << '(' << std::get< 0 >( triple ) << ',' << std::get< 1 >( triple ) << ',' << std::get< 2 >( triple )
                  << ')' << '\n';
    }
    // Manipulation de calendrier grégorien ( à l'aide de boost également )
    auto year = dates_in_year(2018);
    RANGES_FOR(auto month, year | by_month())
        std::cout << front(month) << std::endl;

    RANGES_FOR(auto month, dates_in_year(2018) | by_month() | month_by_week()) {
        RANGES_FOR(auto week, month)
            std::cout << view::transform(week, &date::day) << std::endl;
        std::cout << "<==============>\n";
    }

    auto year18 = dates_in_year(2018) | by_month() | layout_months();
    RANGES_FOR(auto month, year18)
    {
        RANGES_FOR(std::string week, month)
            std::cout << week << '\n';
        std::cout << "<==============>" << std::endl;
    }

    return 0;
}