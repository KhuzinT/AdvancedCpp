#include <iostream>
#include <vector>
#include <memory>

using namespace std;


struct TreeNode {
    int val;
    unique_ptr<TreeNode> left;
    unique_ptr<TreeNode> right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, unique_ptr<TreeNode> left, unique_ptr<TreeNode> right)
            : val(x), left(std::move(left)), right(std::move(right)) {}
};

class Solution {
public:
    vector<unique_ptr<TreeNode>> generateTrees(int n) {
        return generateTreesByInterval(1, n);
    }

private:

    // функция генерирует все структурно-уникальные BST, которые хранят значения от min до max включительно
    vector<unique_ptr<TreeNode>> generateTreesByInterval(int min, int max) {
        vector<unique_ptr<TreeNode>> res;

        if (min > max) {
            res.push_back(nullptr);
            return res;
        }

        // проходим по всем числам от min до max и вызываем
        // функцию снова для левого и правого узла
        for (int curr = min; curr <= max; ++curr) {
            for (auto &left: generateTreesByInterval(min, curr - 1)) {
                for (auto &right: generateTreesByInterval(curr + 1, max)) {
                    res.push_back(make_unique<TreeNode>(curr, std::move(left), std::move(right)));
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