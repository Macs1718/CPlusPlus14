#include <vector>
#include <iostream>
#include <thread>
int main( ) {
    auto f = []( int i ) { std::cout << "Hello from thread " << i << std::endl; };
    const int nbThreads = std::thread::hardware_concurrency( );
    std::vector< std::thread > threads;
    threads.reserve( nbThreads );
    for ( int i = 0; i < nbThreads; ++i ) threads.emplace_back( f, i );
    std::cout << "Hello for main program ;-)" << std::endl;
    for ( auto& t : threads ) t.join( );
    return EXIT_SUCCESS;
}