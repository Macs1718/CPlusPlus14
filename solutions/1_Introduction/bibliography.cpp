# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <sstream>


struct Bibliographie {
    enum kind {
        Bibliography, Thesis, Fiction, Fantastic, SF, Horror,Manga, Book, Journal, Essai,  end_kind
    };
    
    struct item {
        std::string title, author, editor;
        int year; 
        kind book_type;       
    };
    std::vector<item> m_books;
};

void add(Bibliographie& bib, const Bibliographie::item& book )
{
    bib.m_books.push_back(book);
}

std::ostream& operator << ( std::ostream& out, const Bibliographie::item& book)
{
    out << book.title << " from " << book.author << ", editor "<< book.editor << ", first edition "
        << book.year << ", kind of document : " << book.book_type;
    return out;
}

std::ostream& write( std::ostream& out, const Bibliographie& biblio )
{
        out << biblio.m_books.size() << std::endl;
        for ( const auto& b : biblio.m_books )
            out << b.title << "\n" << b.author << "\n" << b.editor << "\n"
                << b.year << " " << int(b.book_type) << std::endl;
        return out;
}

std::istream& read( std::istream& inp, Bibliographie& biblio )
{
    char stmp[256];
    std::size_t sz;
    inp >> sz;
    biblio.m_books.reserve(sz);
    inp.getline(stmp,256);
    for ( int i = 0; i < sz; ++i ) {
        int tp;
        biblio.m_books.emplace_back(Bibliographie::item{});
        Bibliographie::item& book = biblio.m_books.back();
        inp.getline(stmp,256);
        book.title = stmp;
        inp.getline(stmp,256);
        book.author = stmp;
        inp.getline(stmp,256);
        book.editor = stmp;
        inp.getline(stmp,256);
        std::istringstream fii(stmp);
        fii >> book.year >> tp;
        book.book_type = static_cast<Bibliographie::kind>(tp);
    }
    return inp;
}

const Bibliographie::item& bib_oldest( const Bibliographie& bib ) {
    const Bibliographie::item* pt_book = &bib.m_books[0];
    for ( const auto& bk : bib.m_books ) {
        if ( bk.year < pt_book->year ) pt_book = &bk;
    }
    return *pt_book;
}

const Bibliographie::item& bib_newest( const Bibliographie& bib ) {
    const Bibliographie::item* pt_book = &bib.m_books[0];
    for ( const auto& bk : bib.m_books ) {
        if ( bk.year > pt_book->year ) pt_book = &bk;
    }
    return *pt_book;
}

int main()
{
    using Book=Bibliographie::item;
    Bibliographie bib;
    add(bib, Book { .title = "L'homme qui rit", 
                    .author= "Victor Hugo",
                    .editor= "Albert Lacroix", 
                    .year= 1869, 
                    .book_type=Bibliographie::Fiction });
    add(bib, Book { .title = "Eloge de la folie", 
                    .author= "Erasme de Rotterdam",
                    .editor= "Jehan petit et Gilles de Gourmont", 
                    .year= 1511, 
                    .book_type=Bibliographie::Essai });
    add(bib, Book { .title = "Malpertuis", 
                    .author= "Jean Ray",
                    .editor= "Les auteurs associés", 
                    .year= 1943, 
                    .book_type=Bibliographie::Fantastic });
   std::ofstream fich_o("Biblio.dat");
   write(fich_o, bib);
   fich_o.close();
   auto& recent = bib_newest(bib);
   std::cout << "Plus récent : " << recent << std::endl;
   auto& ancien = bib_oldest(bib);
   std::cout << "Plus ancien : " << ancien << std::endl;
   Bibliographie bib2;
   std::ifstream fich_i("Biblio.dat");   
   read(fich_i, bib2);
   fich_i.close();
   for ( const auto& bk : bib2.m_books )
     std::cout << bk << std::endl;
   return EXIT_SUCCESS; 
}