# include <list>
# include <vector>
# include <iostream>

int main()
{   const int n = 10;
    std::list<std::vector<int>> pascal{ {std::vector<int>{1,1} } };
    for ( int i = 1; i <= n; ++i ) {
        const std::vector<int>& curdev = pascal.back();
        std::vector<int> devel(i+2, 1);
        for ( int j = 0; j < i; ++j ) devel[j+1] = curdev[j]+curdev[j+1];
        pascal.push_back(devel); }
    for ( const auto& pol : pascal ) {
        int deg = pol.size()-1;
        std::cout << "Dév. de (x+y)^" << pol.size()-1 << " = " << pol[0] << ".x^" << deg << " + ";
        for ( int d=1; d<deg; ++d ) std::cout << pol[d] << ".x^" << (deg-d) << ".y^" << d << " + ";
        std::cout << pol[deg] << ".y^" << deg << std::endl;
    }
    return 0; }