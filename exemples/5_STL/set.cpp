# include <set>
# include <algorithm>
# include <iostream>

int main()
{
    std::set<int,std::greater<int>> numbers;
    for ( int i = 0; i < 1000; ++i ) numbers.insert((i*126547)%4097);
    for ( auto v : numbers ) std::cout << v << " ";
    std::cout << std::endl;
    return EXIT_SUCCESS;
}