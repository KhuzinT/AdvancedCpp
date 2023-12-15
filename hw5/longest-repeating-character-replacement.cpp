#include <iostream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

class Solution {
private:

    static const int alphabet_size = 26;

    static const char alphabet_zero = 'A';

public:

    // будем использовать метод скользящего окна
    int characterReplacement(const string &str, int k) {
        // массив частоты символа в окне
        vector<int> freq(alphabet_size, 0);
        // максимальная частота символа в окне
        int max_freq = 0;

        // два указателя - начало и конец окна
        int left_idx = 0, right_idx = 0;
        // останавливаемся когда уже не можем расширять окно
        for (; right_idx < str.size(); ++right_idx) {
            // при расширении окна обновляем частоты
            max_freq = max(max_freq, ++freq[str[right_idx] - alphabet_zero]);

            auto window_size = right_idx - left_idx;
            // если размер окна больше чем максимальная частота + k, то нужно уменьшить окно
            if (window_size > k + (max_freq - 1)) {
                --freq[str[left_idx] - alphabet_zero];
                ++left_idx;
            }
        }

        // возвращаем размер окна
        return right_idx - left_idx;
    }
};


int main() {
    auto sol = Solution();

    {
        auto str = "ABAB";
        auto output = sol.characterReplacement(str, 2);

        assert(output == 4);

        std::cout << "Test 1 passed\n";
    }

    {
        auto str = "AABABBA";
        auto output = sol.characterReplacement(str, 1);

        assert(output == 4);

        std::cout << "Test 2 passed\n";
    }
}
