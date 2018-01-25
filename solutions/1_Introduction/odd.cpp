#include <vector>
#include <iostream>

int main()
{
    std::vector<int> odd1{{ 1,3,5,7,9,11}};
    std::vector<int> odd(13);
    for (int i=0;i < odd.size(); ++i)
      odd[i] = 2*i+1;
    for (auto& val : odd ) std::cout << val << " "; 
    std::cout << std::endl;
    return EXIT_SUCCESS;
}