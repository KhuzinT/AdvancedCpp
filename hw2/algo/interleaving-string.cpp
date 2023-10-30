#include <iostream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

class OldSolution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int len1 = s1.length();
        int len2 = s2.length();
        int len3 = s3.length();

        // быстро отсекаем вариант, когда такое невозможно
        if (len1 + len2 != len3) {
            return false;
        }

        // isParse[i][j] == true если s3(0, i+j-1) это чередование s1(0, i-1) и s2(0, j-1)
        vector<vector<bool>> isParse(len1 + 1, vector<bool>(len2 + 1, false));
        // отдельно рассматриваем случай, когда все строки пустые
        isParse[0][0] = true;

        for (int idx1 = 0; idx1 <= len1; ++idx1) {
            for (int idx2 = 0; idx2 <= len2; ++idx2) {
                // индекс текущей буквы в s3
                int idx3 = idx1 + idx2 - 1;

                // если текущая буква s3 совпадает с буквой в s1, то обновляем ответ
                if (idx1 > 0 && s1[idx1 - 1] == s3[idx3]) {
                    isParse[idx1][idx2] = isParse[idx1][idx2] || isParse[idx1 - 1][idx2];
                }
                // если текущая буква s3 совпадает с буквой в s2, то обновляем ответ
                if (idx2 > 0 && s2[idx2 - 1] == s3[idx3]) {
                    isParse[idx1][idx2] = isParse[idx1][idx2] || isParse[idx1][idx2 - 1];
                }
            }
        }

        return isParse[len1][len2];
    }
};

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int len1 = s1.length();
        int len2 = s2.length();
        int len3 = s3.length();

        // быстро отсекаем вариант, когда такое невозможно
        if (len1 + len2 != len3) {
            return false;
        }

        vector<bool> isParse(len2 + 1);
        isParse[0] = true;

        for (int idx1 = 0; idx1 <= len1; ++idx1) {
            for (int idx2 = 0; idx2 <= len2; ++idx2) {
                // индекс текущей буквы в s3
                int idx3 = idx1 + idx2 - 1;

                // если текущая буква s3 совпадает с буквой в s1, то обновляем ответ
                if (idx1 > 0) {
                    isParse[idx2] = isParse[idx2] && s1[idx1 - 1] == s3[idx3];
                }
                // если текущая буква s3 совпадает с буквой в s2, то обновляем ответ
                if (idx2 > 0) {
                    isParse[idx2] = isParse[idx2] || (isParse[idx2 - 1] && s2[idx2 - 1] == s3[idx3]);
                }
            }
        }

        return isParse[len2];
    }
};

int main() {
    auto sol = Solution();

    {
        string s1 = "aabcc";
        string s2 = "dbbca";

        string s3 = "aadbbcbcac";

        assert(sol.isInterleave(s1, s2, s3) == true);

        std::cout << "Test 1 passed\n";
    }

    {
        string s1 = "aabcc";
        string s2 = "dbbca";

        string s3 = "aadbbbaccc";

        assert(sol.isInterleave(s1, s2, s3) == false);

        std::cout << "Test 2 passed\n";
    }

    {
        string s1;
        string s2;

        string s3;

        assert(sol.isInterleave(s1, s2, s3) == true);

        std::cout << "Test 3 passed\n";
    }
}