#include <iostream>
#include <string>

template <typename T> concept Number = std::is_integral_v<T> || std::is_floating_point_v<T>;
template <typename T> concept ToString = requires(T t) { std::to_string(t); };

template <typename T1, typename T2>
requires Number<T1> && ToString<T1> && Number<T2> && ToString<T2>
std::string concat(T1 t1, T2 t2) {
    return std::to_string(t1) + std::to_string(t2);
}

int main() {

    std::cout << concat(3.141592, 6535) << "\n";

    return 0;
}