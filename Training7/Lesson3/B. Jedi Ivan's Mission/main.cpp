#include <bitset>
#include <iostream>
#include <vector>


auto read_matrix(int n) -> std::vector<std::vector<short>> {
  std::vector<std::vector<short>> matrix(n, std::vector<short>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> matrix[i][j];
    }
  }
  return matrix;
}

auto solve(const std::vector<std::vector<short>> &matrix)
    -> std::vector<short> {
  int n = matrix.size();
  std::vector<short> result(n, 0);
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      result[k] |= matrix[i][k];
    }
    for(int j = 0; j < n; ++j) {
      result[k] |= matrix[k][j];
    }
  }
  return result;
}
int main() {
    int n;
    std::cin >> n;
    auto matrix = read_matrix(n);
    auto result = solve(matrix);
    for (const auto &value : result) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    return 0;
}