#include <algorithm>
#include <iostream>
#include <vector>

int MaximalSide(std::vector<std::vector<int>>& matrix);

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> matrix(n);
    for (auto& arr : matrix) {
        arr.resize(m);
        for (int& a : arr) {
            std::cin >> a;
        }
    }
    std::cout << MaximalSide(matrix) << std::endl;
}

int MaximalSide(std::vector<std::vector<int>>& matrix)
{
    int rst = 0;
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            int a = (i > 0 && j > 0) ? matrix[i - 1][j - 1] : 0;
            int b = (i > 0) ? matrix[i - 1][j] : 0;
            int c = (j > 0) ? matrix[i][j - 1] : 0;

            matrix[i][j] = (matrix[i][j] != 0) ? (std::min({ a, b, c }) + 1) : 0;

            rst = std::max(rst, matrix[i][j]);
        }
    }
    return rst;
}
