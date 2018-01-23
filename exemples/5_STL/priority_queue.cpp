# include <queue>
# include <iostream>

int main()
{
    std::priority_queue<int> numbers;
    for ( int i = 0; i < 1000; ++i ) numbers.push((i*126547)%4097);
    while( not numbers.empty() ) {
        std::cout << numbers.top() << " ";
        numbers.pop();
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}