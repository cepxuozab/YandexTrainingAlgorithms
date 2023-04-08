#include <iostream>
#include <vector>

[[maybe_unused]] static auto const faster = []() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  return nullptr;
}();

class NumMatrix {
  size_t rows = 0;
  size_t columns = 0;
  std::vector<std::vector<int>> const &inpt;
  std::vector<std::vector<int>> dp;
  void generate() {
    rows = inpt.size();
    if (rows == 0) {
      return;
    }
    columns = inpt.front().size();
    if (columns == 0) {
      return;
    }

    dp.resize(rows + 1, std::vector<int>(columns + 1));
    for (size_t r = 0; r < rows; ++r) {
      for (size_t c = 0; c < columns; ++c) {
        dp[r + 1][c + 1] = dp[r + 1][c] + dp[r][c + 1] + inpt[r][c] - dp[r][c];
      }
    }
  }

public:
  NumMatrix(std::vector<std::vector<int>> const &matrix)
      : inpt(matrix) {
    generate();
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    if (rows == 0 || columns == 0) {
      return 0;
    }
    return dp[row2 + 1][col2 + 1] - dp[row1][col2 + 1] - dp[row2 + 1][col1] + dp[row1][col1];
  }
};

int main() {
  freopen("input.txt", "r", stdin);
  int n, m, k;
  std::cin >> n >> m >> k;
  std::vector<std::vector<int>> matrix(n, std::vector<int>(m));
  for (auto &arr : matrix) {
    for (int &i : arr) {
      std::cin >> i;
    }
  }
  auto prefix = NumMatrix(matrix);
  for (int j = 0; j < k; ++j) {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    a--, b--, c--, d--;
    std::cout << prefix.sumRegion(a, b, c, d) << std::endl;
  }
}
