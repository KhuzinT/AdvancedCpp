#include <iostream>
#include <cassert>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
    const int garbage = 0;

    vector<int> findRedundantDirectedConnection(vector<vector<int>> &edges) {
        // чтобы отслеживать родителей вершин
        vector<int> parents(edges.size() + 1, garbage);

        // ребра-кандидаты на ответ
        vector<int> first = {};
        vector<int> second = {};

        // идем по всем ребрам и запоминаем родителей
        for (auto &edge: edges) {
            auto start = edge[0];
            auto end = edge[1];

            // если родитель уже есть
            if (parents[end] != garbage) {
                // сохраняем кандидатов
                first = {parents[end], end};
                second = {start, end};

                // отмечаем вершину, в которую ведут два ребра,
                // чтобы далее отделить кандидатов от остальных ребер
                edge[1] = garbage;

                continue;
            }

            parents[end] = start;
        }

        // заводим DSU, чтобы объединять вершины
        auto dsu = DSU(edges.size() + 1);
        for (auto &edge: edges) {
            auto start = edge[0];
            auto end = edge[1];

            // если edge является кандидатом, то скип
            if (end == garbage) {
                continue;
            }

            // если две вершины уже объединены, то значит мы нашли цикл
            if (!dsu.unionSets(start, end)) {
                if (first.empty()) {
                    return edge;
                }
                return first;
            }
        }

        return second;
    }

private:

    // система непересекающихся множеств с эвристикой сжатия путей
    // (можно было использовать и эвристику объединения по рангу,
    //  но тогда по памяти будет так себе)
    class DSU {
    private:
        vector<int> parent_;

    public:
        explicit DSU(int size) : parent_(size) {
            iota(parent_.begin(), parent_.end(), 0);
        }

        int findSet(int value) {
            if (value == parent_[value]) {
                return value;
            }
            parent_[value] = findSet(parent_[value]);
            return parent_[value];
        }

        bool unionSets(int first, int second) {
            int new_first = findSet(first);
            int new_second = findSet(second);
            if (new_first != new_second) {
                parent_[new_second] = new_first;
                return true;
            }

            return false;
        }
    };
};

int main() {
    auto sol = Solution();

    {
        vector<vector<int>> edges = {
                {1, 2},
                {1, 3},
                {2, 3},
        };
        auto output = sol.findRedundantDirectedConnection(edges);
        auto expected = vector{2, 3};

        assert(output == expected);

        std::cout << "Test 1 passed\n";
    }

    {
        vector<vector<int>> edges = {
                {1, 2},
                {2, 3},
                {3, 4},
                {4, 1},
                {1, 5}
        };
        auto output = sol.findRedundantDirectedConnection(edges);
        auto expected = vector{4, 1};

        assert(output == expected);

        std::cout << "Test 2 passed\n";
    }

}