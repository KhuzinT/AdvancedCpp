#include <iostream>
#include <vector>

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<TreeNode *> generateTrees(int n) {
        return generateTreesByInterval(1, n);
    }

private:

    // функция генерирует все структурно-уникальные BST, которые хранят значения от min до max включительно
    vector<TreeNode *> generateTreesByInterval(int min, int max) {
        if (min > max) {
            return {nullptr};
        }

        vector<TreeNode *> res;

        // проходим по всем числам от min до max и вызываем
        // функцию снова для левого и правого узла
        for (int curr = min; curr <= max; ++curr) {
            for (TreeNode *left: generateTreesByInterval(min, curr - 1)) {
                for (TreeNode *right: generateTreesByInterval(curr + 1, max)) {
                    res.push_back(new TreeNode(curr, left, right));
                }
            }
        }

        return res;
    }
};

int main() {
    auto sol = Solution();

    {
        int n = 3;

        auto output = sol.generateTrees(n);
    }

    {
        int n = 1;

        auto output = sol.generateTrees(n);
    }
}