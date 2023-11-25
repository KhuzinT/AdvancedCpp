#include <iostream>
#include <ranges>

using namespace std;

int main() {
    for (auto value: views::iota(10, 101)
                     | views::transform([](int x) { return x * x; })
                     | views::filter([](int x) { return x % 5 != 0; })
                     | views::transform([](int x) { return std::to_string(x); })) {
        std::cout << value << "\n";
    }
}