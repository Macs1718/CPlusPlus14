# include <iostream>
# include <chrono>

int main()
{
    using std::chrono::system_clock;
    auto one_day = std::chrono::hours(24);
    system_clock::time_point today = system_clock::now();
    system_clock::time_point tomorrow = today + one_day;
    system_clock::time_point yesterday= today - one_day;
    std::time_t tt;
    tt = system_clock::to_time_t(today);
    std::cout << "Today is " << ctime(&tt) << std::endl;
    tt = system_clock::to_time_t(tomorrow);
    std::cout << "Tomorrow is " << ctime(&tt) << std::endl;
    tt = system_clock::to_time_t(yesterday);
    std::cout << "Yesterday is " << ctime(&tt) << std::endl;
    
    return EXIT_SUCCESS;
}