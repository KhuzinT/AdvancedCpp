#include <iostream>
#include <ranges>
#include <string>
#include <vector>

using namespace std;

template<typename InputIter, typename OutputIter>
void myCopy(InputIter begin, InputIter end, OutputIter target) {
    for (auto iter{begin}; iter != end; ++iter, ++target) {
        *target = *iter;
    }
}

struct Person {
    string first_name;
    string last_name;
};

ostream &operator<<(ostream &out, const Person &person) {
    out << person.first_name << " " << person.last_name;
    return out;
}

int main() {
    vector<pair<Person, int>> people = {
            {{"Павел", "Смирнов"},   34},
            {{"Петр",  "Сенаторов"}, 78},
            {{"Илья",  "Матвеев"},   20},
            {{"Азат",  "Хайруллин"}, 5},
            {{"Иван",  "Лескин"},    28},
    };

    auto filter_people = people
                         | views::take(4)
                         | views::transform([](pair<Person, int> &curr) { return curr.first; });

    myCopy(filter_people.begin(), filter_people.end(), ostream_iterator<Person>(cout, "\n"));

    cout << "===================\n";

    auto filter_people_last_name =
            filter_people | views::transform([](const Person &person) { return person.last_name; });

    myCopy(filter_people_last_name.begin(), filter_people_last_name.end(), ostream_iterator<string>(cout, "\n"));

}