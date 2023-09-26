#include <iostream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:

    vector<string> generateParenthesis(int n) {
        vector<string> res;

        // отслеживаем строку с уже добавленными скобками
        string curr;
        dfs(n, curr, 0, 0, res);

        return res;
    }

private:

    void dfs(int n, string &curr, int open_count, int close_count, vector<string> &res) {
        // останавливаемся если собрали ПСП
        if (curr.length() == 2 * n) {
            res.push_back(curr);
            return;
        }

        // можем добавить еще одну открывающую скобку
        if (open_count < n) {
            curr.push_back('(');
            dfs(n, curr, open_count + 1, close_count, res);
            curr.pop_back();
        }

        // можем добавить еще одну закрывающую скобку
        if (close_count < open_count) {
            curr.push_back(')');
            dfs(n, curr, open_count, close_count + 1, res);
            curr.pop_back();
        }
    }
};

int main() {
    auto sol = Solution();

    {
        int n = 3;
        auto output = sol.generateParenthesis(n);

        vector<string> expected = {
                "((()))",
                "(()())",
                "(())()",
                "()(())",
                "()()()"
        };

        assert(output == expected);

        std::cout << "Test 1 passed\n";
    }

    {
        int n = 1;
        auto output = sol.generateParenthesis(n);

        vector<string> expected = {"()"};

        assert(output == expected);

        std::cout << "Test 2 passed\n";
    }

}