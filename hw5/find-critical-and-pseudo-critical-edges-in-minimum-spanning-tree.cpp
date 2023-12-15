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

    using Edge = vector<int>;

    static bool compareEdges(const Edge &first, const Edge &second) {
        return std::tie(first[2], first[0], first[1]) < std::tie(second[2], second[0], second[1]);
    }

public:

    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>> &edges) {
        // сортируем ребра по весам
        vector<Edge> sorted_edges(edges);
        sort(sorted_edges.begin(), sorted_edges.end(), compareEdges);

        // считаем вес МОД со всеми ребрами
        int mst_size = 0;

        // проходимся по всем ребрам, объединяя вершины графа
        auto dsu = DSU(n);
        for (auto &edge: sorted_edges) {
            // если вершины еще не объединены, то объединяем их и добавляем ребро в ответ
            // т.к. ребра отсортированы, то добавленное ребро будет минимальным
            if (dsu.unionSets(edge[0], edge[1])) {
                mst_size += edge[2];
            }
        }

        vector<vector<Edge>> res_edge(2);

        for (auto &edge: sorted_edges) {

            // критические ребра
            {
                // вес МОД без текущего ребра
                int crit_mst_size = 0;

                // проходимся по всем ребрам
                auto crit_dsu = DSU(n);
                for (auto &next: sorted_edges) {
                    // пропускаем если ребро совпадает с текущим
                    if (next == edge) {
                        continue;
                    }

                    // делаем то же, что делали, когда считали вес МОД для всего графа
                    if (crit_dsu.unionSets(next[0], next[1])) {
                        crit_mst_size += next[2];
                    }
                }

                // если не получилось объединить все вершины или
                // если получилось, но вес МОД увеличился,
                // то ребро критическое
                if (crit_dsu.getSize() > 1 || crit_mst_size > mst_size) {
                    res_edge[0].push_back(edge);
                    continue;
                }
            }

            // псевдо-критические ребра
            {
                // вес МОД с текущим ребром
                int pcrit_mst_size = edge[2];

                // проходимся по всем ребрам
                auto pcrit_dsu = DSU(n);
                pcrit_dsu.unionSets(edge[0], edge[1]);
                for (auto &next: sorted_edges) {
                    // пропускаем если ребро совпадает с текущим
                    if (next == edge) {
                        continue;
                    }

                    // делаем то же, что делали, когда считали вес МОД для всего графа
                    if (pcrit_dsu.unionSets(next[0], next[1])) {
                        pcrit_mst_size += next[2];
                    }
                }

                // если вес МОД не изменился после добавления ребра, то ребро псевдо-критическое
                if (pcrit_mst_size == mst_size) {
                    res_edge[1].push_back(edge);
                }
            }
        }

        // приводим ответ к виду, который требуют в задании
        vector<vector<int>> res(2);
        for (int idx = 0; idx < edges.size(); ++idx) {
            auto edge = edges[idx];
            for (auto &crit_edge: res_edge[0]) {
                if (crit_edge == edge) {
                    res[0].push_back(idx);
                }
            }
            for (auto &pcrit_edge: res_edge[1]) {
                if (pcrit_edge == edge) {
                    res[1].push_back(idx);
                }
            }
        }

        return res;
    }

private:

    // система непересекающихся множеств с эвристикой сжатия путей
    // и эвристикой объединения по рангу
    class DSU {
    private:

        int size_ = 0;

        vector<int> parent_;
        vector<int> rank_;

    public:
        explicit DSU(int size) : size_(size), parent_(size) {
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
                --size_;
                return true;
            }
            return false;
        }

        [[nodiscard]] int getSize() const {
            return size_;
        }
    };

};

int main() {
    auto sol = Solution();

    {
        int n = 5;
        vector<vector<int>> edges = {{0, 1, 1},
                                     {1, 2, 1},
                                     {2, 3, 2},
                                     {0, 3, 2},
                                     {0, 4, 3},
                                     {3, 4, 3},
                                     {1, 4, 6}};
        auto output = sol.findCriticalAndPseudoCriticalEdges(n, edges);

        vector<vector<int>> expected = {{0, 1},
                                        {2, 3, 4, 5}};

        assert(output == expected);

        std::cout << "Test 1 passed\n";
    }

    {
        int n = 4;
        vector<vector<int>> edges = {{0, 1, 1},
                                     {1, 2, 1},
                                     {2, 3, 1},
                                     {0, 3, 1}};
        auto output = sol.findCriticalAndPseudoCriticalEdges(n, edges);

        vector<vector<int>> expected = {{},
                                        {0, 1, 2, 3}};

        assert(output == expected);

        std::cout << "Test 2 passed\n";
    }

}
