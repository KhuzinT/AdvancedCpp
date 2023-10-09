#include <iostream>
#include <cassert>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int> &nums) {
        vector<vector<int>> res;

        // создаем map: элемент nums --- сколько он встречается в массиве
        unordered_map<int, int> freq_by_nums;
        for (auto curr: nums) {
            freq_by_nums[curr]++;
        }

        // начинаем обходить дерево решений
        dfs(nums, 0, freq_by_nums, res);

        return res;
    }

private:

    void dfs(vector<int> &permutation, int idx, unordered_map<int, int> &freq_by_nums, vector<vector<int>> &res) {
        // если глубина обхода равна размеру массива, то добавляем в ответ
        if (idx == permutation.size()) {
            res.push_back(permutation);
            return;
        }

        for (auto& entry: freq_by_nums) {
            // проверяем, что все еще можем использовать число
            if (entry.second > 0) {
                entry.second--;

                // добавляем число в перестановку и повторяем алгоритм для поддерева
                permutation[idx] = entry.first;
                dfs(permutation, idx + 1, freq_by_nums, res);

                entry.second++;
            }
        }

    }
};


int main() {
    auto sol = Solution();

    {
        vector nums = {1, 1, 2};
        auto output = sol.permuteUnique(nums);

        vector<vector<int>> expected = {
                {2, 1, 1},
                {1, 2, 1},
                {1, 1, 2}
        };

        assert(output == expected);

        std::cout << "Test 1 passed\n";
    }

    {
        vector nums = {1, 2, 3};
        auto output = sol.permuteUnique(nums);

        vector<vector<int>> expected = {
                {3, 2, 1},
                {3, 1, 2},
                {2, 3, 1},
                {2, 1, 3},
                {1, 3, 2},
                {1, 2, 3}
        };

        assert(output == expected);

        std::cout << "Test 2 passed\n";
    }
}