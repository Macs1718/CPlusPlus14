# include <map>
# include <string>
# include <utility>
# include <iostream>

struct id_perso {
    std::string adresse;
    std::string num_tel;
    unsigned long id_secu;
};

std::ostream& operator << ( std::ostream& out, const id_perso& id )
{
    out << "adresse : " << id.adresse << "\nNum tél. : " << id.num_tel << "\nid_secu :" << id.id_secu;
    return out;
}

using database = std::map<std::pair<std::string,std::string>,id_perso>;

int main() {
    database db;
    db[std::make_pair("Robert","Chambier")] = { .adresse = "4 rue du Moulin,\n 62432 Moulinsard", .num_tel = "06486969", .id_secu=158042345 };
    db[std::make_pair("Ginette","Chambier")] = { .adresse = "4 rue du Moulin,\n 62432 Moulinsard", .num_tel = "06483396", .id_secu=261012176 };

    std::cout << "Id de Rober C. " << db[std::make_pair("Robert","Chambier")] << std::endl;
    std::cout << "Personnes enregistrées dans mon agenda : " 
             <<"\n======================================== " << std::endl;
    for ( const auto& d : db ) {
        std::cout << d.first.first << " " << d.first.second << " : " << d.second << std::endl << std::endl;
    }
    
    return EXIT_SUCCESS;
}