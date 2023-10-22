#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

class Solution {
public:

    // для каждого столба найдем самые высокие столбы слева и справа от него
    // разница между текущим столбом и минимумом из двух найденных -
    // это кол-во воды, которое хранится над текущим столбом
    int trap(vector<int> &height) {
        int n = height.size();
        if (n == 0) {
            return 0;
        }

        // массив самого высокого столба слева от текущего
        vector<int> left(n, height[0]);
        for (int idx = 1; idx < n; ++idx) {
            left[idx] = max(left[idx - 1], height[idx]);
        }

        // массив самого высокого столба справа от текущего
        vector<int> right(n, height[n - 1]);
        for (int idx = n - 2; idx >= 0; --idx) {
            right[idx] = max(right[idx + 1], height[idx]);
        }

        // так как максимумы уже подсчитаны, то можем быстро найти ответ
        int res = 0;
        for (int idx = 1; idx < n - 1; ++idx) {
            int curr = min(left[idx - 1], right[idx + 1]);
            if (curr > height[idx]) {
                // добавляем в ответ разницу между текущим столбом
                // и меньшим максимальным столбом слева или справа
                res += (curr - height[idx]);
            }
        }

        return res;
    }
};

int main() {
    auto sol = Solution();

    {
        vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
        int res = 6;

        assert(sol.trap(height) == res);

        std::cout << "Test 1 passed\n";
    }

    {
        vector<int> height = {4, 2, 0, 3, 2, 5};
        int res = 9;

        assert(sol.trap(height) == res);

        std::cout << "Test 2 passed\n";
    }
}