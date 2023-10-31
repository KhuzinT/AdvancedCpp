#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

class Solution {
public:

    vector<int> singleNumber(vector<int> &nums) {
        // сортируем числа за O(n * log n)
        sort(nums.begin(), nums.end());

        vector<int> res;

        // проходимся по отсортированному массиву
        for (int idx = 0; idx < nums.size() - 1;) {
            // если числа совпадают, то можем их пропустить
            if (nums[idx] == nums[idx + 1]) {
                idx += 2;
                continue;
            }

            // иначе добавляем в ответ и проверяем, если два числа уже нашлись
            res.push_back(nums[idx]);
            if (res.size() == 2) {
                break;
            }

            ++idx;
        }

        // если два числа еще не нашлись, то это значит,
        // что второе число стоит на последнем месте в массиве
        if (res.size() == 1) {
            res.push_back(nums.back());
        }

        return res;
    }
};

int main() {
    auto sol = Solution();

    {
        vector nums = {1, 2, 1, 3, 2, 5};
        auto output = sol.singleNumber(nums);
        auto expected = vector{3, 5};

        assert(output == expected);

        std::cout << "Test 1 passed\n";
    }

    {
        vector nums = {-1, 0};
        auto output = sol.singleNumber(nums);
        auto expected = vector{-1, 0};

        assert(output == expected);

        std::cout << "Test 2 passed\n";
    }

    {
        vector nums = {0, 1};
        auto output = sol.singleNumber(nums);
        auto expected = vector{0, 1};

        assert(output == expected);

        std::cout << "Test 3 passed\n";
    }
}