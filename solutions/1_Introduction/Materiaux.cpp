# include <iostream>
# include <string>
# include <map>
# include <fstream>

struct Materiau {
    double young, T, R;
};

using MDB_Materiaux = std::map<std::string,Materiau>;

std::istream& operator >> ( std::istream& inp, Materiau& mat )
{
    inp >> mat.young >> mat.T >> mat.R;
    return inp;
}

std::istream& operator >> ( std::istream& inp, MDB_Materiaux& mdb )
{
    std::string mat_name;
    std::size_t nb_mat;
    inp >> nb_mat;
    double y,t,r;
    for ( int i = 0; i < nb_mat; ++i ) {
        inp >> mat_name >> y >> t >> r;
        mdb[mat_name] = Materiau{ .young=y, .T = t, .R = r };
    }
    return inp;
}

std::ostream& operator << ( std::ostream& out, const Materiau& mat )
{
    out << mat.young << "\t" << mat.T << "\t" << mat.R;
    return out;
}

std::ostream& operator << ( std::ostream& out, const MDB_Materiaux& mdb )
{
    out << mdb.size() << std::endl;
    for ( const auto& m : mdb )
        out << m.first << "\t" << m.second << std::endl;
    return out;
}

int main()
{
    Materiau acier { .young = 100., .T = 260, .R = 0.1 };
    Materiau chene { .young = 90. , .T = 100, .R = 60  };
    MDB_Materiaux mdb;
    mdb["acier"] = acier;
    mdb["chene"] = chene;
    std::ofstream ofich("Materiaux.mdb");
    ofich << mdb;
    ofich.close();
    MDB_Materiaux mdb2;
    std::ifstream ifich("Materiaux.mdb");
    ifich >> mdb2;
    ifich.close();
    std::cout << mdb2["acier"] << "\n" << mdb2["chene"] << std::endl;
    return EXIT_SUCCESS;
}