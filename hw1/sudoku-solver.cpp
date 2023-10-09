#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:

    void solveSudoku(vector<vector<char>> &board) {
        // обход таблицы слева направо сверху вниз
        dfs(board);
    }

private:

    bool dfs(vector<vector<char>> &board, int r = 0, int c = 0) {
        // означает что мы заполнили все ряды
        if (r == 9) {
            return true;
        }
        // означает что мы заполнили текущий ряд
        if (c == 9) {
            return dfs(board, r + 1, 0);
        }
        // если ячейка уже заполнена, то идем дальше
        if (board[r][c] != '.') {
            return dfs(board, r, c + 1);
        }

        // пытаемся поставить в свободную ячейку число от 1 до 9 и перейти к следующей
        // если на каком-то шаге никакое число поставить нельзя,
        // то возвращаемся к предыдущей ячейке и пробуем с другим числом
        for (char num = '1'; num <= '9'; ++num) {
            if (validSell(board, r, c, num)) {
                board[r][c] = num;

                if (dfs(board, r, c + 1)) {
                    return true;
                }

                board[r][c] = '.';
            }
        }

        return false;
    }

    // проверяем, что можем поставить число num в клетку с координатами (r, c)
    bool validSell(vector<vector<char>> board, int r, int c, char num) {
        for (int idx = 0; idx < 9; ++idx) {
            // проверяем, что по горизонтали и вертикали еще нет такого числа
            if (board[r][idx] == num || board[idx][c] == num) {
                return false;
            }

            // номер текущего блока
            int board_idx = (r / 3) * 3 + (c / 3);

            // координаты ячейки в рамках блока
            int board_r = (board_idx / 3) * 3 + (idx / 3);
            int board_c = (board_idx % 3) * 3 + (idx % 3);

            // проверяем, что в блоке еще нет такого числа
            if (board[board_r][board_c] == num) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    auto sol = Solution();

    {
        vector<vector<char>> board = {
                {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                {'.', '.', '.', '.', '8', '.', '.', '7', '9'},
        };


        sol.solveSudoku(board);

        for (auto &row: board) {
            for (auto value: row) {
                std::cout << value << " ";
            }
            std::cout << "\n";
        }
    }
}