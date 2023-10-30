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

struct Person {
    string first_name;
    string last_name;
};

double mean_filter_age(const vector<pair<Person, int>> &people) {
    auto ages = people
                | views::values
                | views::filter([](int age) { return age >= 12 && age <= 65; });

    double ages_sum =  sum(ages.begin(), ages.end());
    auto ages_count = count_if(ages.begin(), ages.end(), [](auto) { return true; });

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