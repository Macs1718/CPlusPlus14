# include <iostream>

template<std::size_t N, std::size_t Low, std::size_t Upp>
struct IRoot_gen{
    static constexpr std::size_t mean = (Low+Upp)/2;
    static constexpr std::size_t down = ((mean*mean)>=N);
};
template<std::size_t N, std::size_t Low=1, std::size_t Upp=N> constexpr std::size_t IRoot = 
             IRoot<N, (IRoot_gen<N,Low,Upp>::down ? Low : IRoot_gen<N,Low,Upp>::mean+1), 
                      (IRoot_gen<N,Low,Upp>::down ? IRoot_gen<N,Low,Upp>::mean : Upp)>;
template<std::size_t N, std::size_t Mean> constexpr std::size_t IRoot<N,Mean,Mean> = Mean;
int main() {
    std::cout << "Racine entiere superieure de 24 = " << IRoot<24> << std::endl;
    return 0;
}