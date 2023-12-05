#include <iostream>
#include <cassert>
#include <numeric>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;

class Solution {
private:

    using VertexT = int64_t;
    using WeightT = int64_t;

    using DistT = int64_t;
    const DistT infty = INT64_MAX;

    // структура для хранения конца и веса ребра
    struct EndPoint {
        VertexT vertex;
        WeightT weight;

        bool operator<(const EndPoint &other) const {
            return std::tie(weight, vertex) < std::tie(other.weight, other.vertex);
        }
    };

    // граф на списках смежности
    class Graph {
    private:

        vector<vector<EndPoint>> list_;

    public:

        explicit Graph(const VertexT &size) : list_(size, vector<EndPoint>()) {}

        void addEdge(const VertexT &begin, const VertexT &end, const WeightT &weight = 1) {
            list_[begin].push_back(EndPoint{end, weight});
        }

        [[nodiscard]] vector<EndPoint> getNeighbors(const VertexT &curr) const {
            return list_[curr];
        }

        [[nodiscard]] VertexT getSize() const {
            return list_.size();
        }
    };

    // алгоритм Дейкстры для нахождения кратчайшего пути от вершины до всех остальных в графе
    vector<DistT> DijkstraAlgorithm(const Graph &graph, const VertexT &start) {
        auto dist = vector<DistT>(graph.getSize(), infty);
        dist[start] = 0;

        priority_queue<EndPoint> queue;
        queue.push(EndPoint{start, dist[start]});

        while (!queue.empty()) {
            auto curr = queue.top();
            queue.pop();

            if (curr.weight != dist[curr.vertex]) {
                continue;
            }

            for (auto end_point: graph.getNeighbors(curr.vertex)) {
                VertexT next = end_point.vertex;
                WeightT weight = end_point.weight;
                if (dist[curr.vertex] + weight < dist[next]) {
                    dist[next] = dist[curr.vertex] + weight;
                    queue.push(EndPoint{next, dist[next]});
                }
            }
        }

        return dist;
    }

public:

    // идея решения - если есть подграф, который удовлетворяет условию, то в нем существует такая вершина x,
    // что есть путь от src1 и src2 до x, а также от x до dest (или от dest до x в инвертированном графе)
    // тогда мы можем найти минимальное пути от нужных вершин до x - их сумма и будет ответом
    DistT minimumWeight(int n, vector<vector<int>> &edges, int src1, int src2, int dest) {
        // создаем два графа - один обычный, а в другом меняем направление ребер
        auto graph = Graph(n);
        auto revGraph = Graph(n);

        // добавляем ребра
        for (auto edge: edges) {
            graph.addEdge(edge[0], edge[1], edge[2]);
            revGraph.addEdge(edge[1], edge[0], edge[2]);
        }

        // подсчитываем расстояния
        auto src1_dist = DijkstraAlgorithm(graph, src1);
        auto src2_dist = DijkstraAlgorithm(graph, src2);

        auto dest_dist = DijkstraAlgorithm(revGraph, dest);

        // проверяем, что можем добраться из src1 или src2 до dest
        if (dest_dist[src1] == infty || dest_dist[src2] == infty) {
            return -1;
        }

        DistT res = infty;

        for (VertexT curr = 0; curr < n; ++curr) {
            // проверяем, что текущая вершина может связать все три необходимые
            if (src1_dist[curr] == infty || src2_dist[curr] == infty || dest_dist[curr] == infty) {
                continue;
            }
            // обновляем результат
            res = min(res, src1_dist[curr] + src2_dist[curr] + dest_dist[curr]);
        }

        return res;
    }
};


int main() {
    auto sol = Solution();

    {
        int n = 6;
        vector<vector<int>> edges = {{0, 2, 2},
                                     {0, 5, 6},
                                     {1, 0, 3},
                                     {1, 4, 5},
                                     {2, 1, 1},
                                     {2, 3, 3},
                                     {2, 3, 4},
                                     {3, 4, 2},
                                     {4, 5, 1}};
        int src1 = 0;
        int src2 = 1;
        int dest = 5;

        auto output = sol.minimumWeight(n, edges, src1, src2, dest);

        assert(output == 9);

        std::cout << "Test 1 passed\n";
    }

    {
        int n = 3;
        vector<vector<int>> edges = {{0, 1, 1},
                                     {2, 1, 1}};
        int src1 = 0;
        int src2 = 1;
        int dest = 2;

        auto output = sol.minimumWeight(n, edges, src1, src2, dest);

        assert(output == -1);

        std::cout << "Test 2 passed\n";
    }
}