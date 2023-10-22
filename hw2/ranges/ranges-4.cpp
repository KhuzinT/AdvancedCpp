#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>

int main() {

    std::vector<int> numbers;

    // with for

    auto stream = std::ranges::istream_view<int>(std::cin) | std::views::take_while([](int x) { return x != -1; });
    for (std::movable auto value: stream) {
        numbers.push_back(value);
        std::cout << value << " ";
    }

    // without for

    numbers.clear();

    std::ranges::copy(stream.begin(), stream.end(), back_inserter(numbers));
    std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
}