#include <iostream>
#include <cassert>
#include <numeric>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;

class Solution {
private:

    using VertexT = int32_t;
    using WeightT = int32_t;

    const WeightT infty = INT32_MAX;

    // алгоритм Прима для плотных графов за O(n^2)
    WeightT PrimAlgorithm(const vector<vector<int>> &points) {
        VertexT size = points.size();

        // отслеживаем непосещенные вершины
        vector<bool> visited(size, false);

        // массив с весом наименьшего ребра из вершины
        vector<WeightT> min_weight(size, infty);
        min_weight[0] = 0;

        WeightT res = 0;
        for (int idx = 0; idx < size; ++idx) {
            VertexT curr = infty;

            // ищем вершину с минимальным весом
            for (VertexT next = 0; next < size; ++next) {
                // проверяем, что вершина еще не в МОД
                if (visited[next]) {
                    continue;
                }

                // если curr еще не определена, то берем любую
                if (curr == infty) {
                    curr = next;
                    continue;
                }

                // сравниваем веса
                if (min_weight[next] < min_weight[curr]) {
                    curr = next;
                }
            }

            // добавляем вершину в ответ
            visited[curr] = true;
            res += min_weight[curr];

            // обновляем массив наименьших весов
            for (VertexT next = 0; next < size; ++next) {
                // если вершина уже посещена, то веса можно не обновлять
                if (visited[next]) {
                    continue;
                }

                min_weight[next] = min(min_weight[next],
                                       abs(points[curr][0] - points[next][0]) + abs(points[curr][1] - points[next][1]));
            }
        }

        return res;
    }

public:

    int minCostConnectPoints(vector<vector<int>> &points) {
        // считаем вес МОД с помощью алгоритма Прима
        return PrimAlgorithm(points);
    }
};


class OldSolution {
public:

    // используем алгоритм Крускала с DSU
    int minCostConnectPoints(vector<vector<int>> &points) {
        int size = points.size();

        // считаем веса ребер между точками
        auto edges = vector<Edge>();
        for (int idx = 0; idx < size; ++idx) {
            auto curr = points[idx];
            for (int pos = idx + 1; pos < size; ++pos) {
                auto next = points[pos];
                auto weight = abs(curr[0] - next[0]) + abs(curr[1] - next[1]);
                edges.push_back(Edge{idx, pos, weight});
            }
        }

        // сортируем ребра по весам
        sort(edges.begin(), edges.end());

        int res = 0;

        // проходимся по всем ребрам, объединяя вершины графа
        auto dsu = DSU(size);
        for (auto edge: edges) {
            // если вершины еще не объединены, то объединяем их и добавляем ребро в ответ
            // т.к. ребра отсортированы, то добавленное ребро будет минимальным
            if (dsu.unionSets(edge.begin_idx, edge.end_idx)) {
                res += edge.weight;
            }
        }

        return res;
    }

private:

    // ребро графа
    struct Edge {
        // номер точек начала и
        // конца ребра в points
        int begin_idx;
        int end_idx;

        int weight;

        bool operator<(const Edge &other) const {
            return std::tie(weight, begin_idx, end_idx) <
                   std::tie(other.weight, other.begin_idx, other.end_idx);
        }
    };

    // система непересекающихся множеств с эвристикой сжатия путей
    // и эвристикой объединения по рангу
    class DSU {
    private:
        vector<int> parent_;
        vector<int> rank_;

    public:
        explicit DSU(int size) : parent_(size) {
            iota(parent_.begin(), parent_.end(), 0);
            rank_.resize(size, 0);
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
                if (rank_[new_first] < rank_[new_second]) {
                    parent_[new_first] = new_second;
                    if (rank_[new_first] == rank_[new_second]) {
                        ++rank_[new_second];
                    }
                } else {
                    parent_[new_second] = new_first;
                    if (rank_[new_first] == rank_[new_second]) {
                        ++rank_[new_first];
                    }
                }
                return true;
            }
            return false;
        }
    };

};


int main() {
    auto sol = Solution();

    {
        vector<vector<int>> points = {
                {0, 0},
                {2, 2},
                {3, 10},
                {5, 2},
                {7, 0}
        };
        auto output = sol.minCostConnectPoints(points);

        assert(output == 20);

        std::cout << "Test 1 passed\n";
    }

    {
        vector<vector<int>> points = {
                {3,  12},
                {-2, 5},
                {-4, 1}
        };
        auto output = sol.minCostConnectPoints(points);

        assert(output == 18);

        std::cout << "Test 2 passed\n";
    }
}