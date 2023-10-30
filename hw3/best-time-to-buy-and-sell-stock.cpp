#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

class Solution {
public:

    int maxProfit(vector<int>& prices) {
        // нет акций - нет прибыли
        if (prices.empty()) {
            return 0;
        }

        // хотим найти минимальную цену
        int min_price = prices[0];

        int res = 0;
        for (int idx = 1; idx < prices.size(); ++idx) {
            // профит - это максимальная разница между текущей ценой и минимальной, которая была до нее
            res = max(res, prices[idx] - min_price);
            min_price = min(min_price, prices[idx]);
        }

        return res;
    }
};

int main() {
    auto sol = Solution();

    {
        vector prices = {7, 1, 5, 3, 6, 4};
        auto output = sol.maxProfit(prices);

        assert(output == 5);

        std::cout << "Test 1 passed\n";
    }

    {
        vector prices = {7, 6, 4, 3, 1};
        auto output = sol.maxProfit(prices);

        assert(output == 0);

        std::cout << "Test 2 passed\n";
    }
}