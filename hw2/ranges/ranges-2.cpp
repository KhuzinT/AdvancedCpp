#include <iostream>
#include <ranges>
#include <string>
#include <vector>

using namespace std;

template<typename InputIter>
auto sum(InputIter begin, InputIter end) {
    auto sum{*begin};
    for (auto iter{++begin}; iter != end; ++iter) {
        sum += *iter;
    }
    return sum;
}

template<typename InputIter>
auto count(InputIter begin, InputIter end) {
    auto count = 0;
    for (auto iter{begin}; iter != end; ++iter, ++count) {}
    return count;
}

struct Person {
    string first_name;
    string last_name;
};

double mean_filter_age(const vector<pair<Person, int>> &people) {
    auto ages = people
                | views::filter([](const pair<Person, int>& curr) { return curr.second >= 12 && curr.second <= 65; })
                | views::transform([](const pair<Person, int>& curr) { return curr.second; });

    auto ages_sum = 1.0 * sum(ages.begin(), ages.end());
    auto ages_count = count(ages.begin(), ages.end());

    return ages_sum / ages_count;
}

int main() {
    vector<pair<Person, int>> people = {
            {{"Павел", "Смирнов"},   34},
            {{"Петр",  "Сенаторов"}, 78},
            {{"Илья",  "Матвеев"},   20},
            {{"Азат",  "Хайруллин"}, 5},
            {{"Иван",  "Лескин"}, 28},
    };

    std::cout << mean_filter_age(people);
}