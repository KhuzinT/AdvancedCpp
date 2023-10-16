#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

class Solution {
public:

    vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        // сортируем числа, чтобы в дальнейшем мы могли "пропускать" дубликаты
        sort(nums.begin(), nums.end());

        vector<vector<int>> res;

        // начинаем идти по входному массиву
        vector<int> empty_subset;
        dfs(nums, 0, empty_subset, res);

        return res;
    }

private:

    void dfs(vector<int>& nums, int nums_idx, vector<int>& curr_subset, vector<vector<int>>& res) {
        // добавляем текущее подмножество в ответ
        res.push_back(curr_subset);

        for (int idx = nums_idx; idx < nums.size(); ++idx) {
            // если мы встречаем число не первый раз и оно повторяем предыдущее, то пропускаем его
            if (idx != nums_idx && nums[idx] == nums[idx - 1]) {
                continue;
            }

            // добавляем число в подмножество и повторяем алгоритм уже для него
            curr_subset.push_back(nums[idx]);
            dfs(nums, idx + 1, curr_subset, res);
            curr_subset.pop_back();
        }
    }
};

int main() {
    auto sol = Solution();

    {
        vector nums = {1, 2, 2};
        auto output = sol.subsetsWithDup(nums);

        vector<vector<int>> expected = {
                {},
                {1},
                {1, 2},
                {1, 2, 2},
                {2},
                {2, 2}
        };

        assert(output == expected);

        std::cout << "Test 1 passed\n";
    }

    {
        vector nums = {0};
        auto output = sol.subsetsWithDup(nums);

        vector<vector<int>> expected = {
                {},
                {0}
        };

        assert(output == expected);

        std::cout << "Test 2 passed\n";
    }

}