#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>> &grid) {
        num_rows = grid.size();
        num_cols = grid[0].size();

        // применяем алгоритм поиска компонент связности
        // с помощью dfs
        int comp_count = 0;
        for (int row = 0; row < num_rows; ++row) {
            for (int col = 0; col < num_cols; ++col) {
                if (grid[row][col] == '1') {
                    dfs(grid, row, col);
                    ++comp_count;
                }
            }
        }

        return comp_count;
    }

private:

    int num_rows = 0;
    int num_cols = 0;

    void dfs(vector<vector<char>>& grid, int row, int col) {
        // проверяем что не вышли за границы по строкам
        if (0 > row || row >= num_rows) {
            return;
        }

        // проверяем что не вышли за границы по столбцам
        if (0 > col || col >= num_cols) {
            return;
        }

        // проверяем что это 1 - "земля"
        if (grid[row][col] != '1') {
            return;
        }

        // помечаем вершину как visited
        grid[row][col] = 'v';

        // идем вниз
        dfs(grid, row + 1, col);
        // идем вверх
        dfs(grid, row - 1, col);
        // идем влево
        dfs(grid, row, col - 1);
        // идем вправо
        dfs(grid, row, col + 1);
    }
};

int main() {
    auto sol = Solution();

    {
        vector<vector<char>> grid = {
                {'1', '1', '1', '1', '0'},
                {'1', '1', '0', '1', '0'},
                {'1', '1', '0', '0', '0'},
                {'0', '0', '0', '0', '0'}
        };
        auto output = sol.numIslands(grid);

        assert(output == 1);

        std::cout << "Test 1 passed\n";
    }

    {
        vector<vector<char>> grid = {
                {'1', '1', '0', '0', '0'},
                {'1', '1', '0', '0', '0'},
                {'0', '0', '1', '0', '0'},
                {'0', '0', '0', '1', '1'}
        };
        auto output = sol.numIslands(grid);

        assert(output == 3);

        std::cout << "Test 2 passed\n";
    }
}