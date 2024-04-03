#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

template <class T>
void print(const std::vector<std::vector<T>>& data) {
    for (auto& vec : data) {
        for (auto v : vec) {
            std::cout << v << " ";
        }
        std::cout << '\n';
    }
}
uint64_t getSum(int lx, int ly, int rx, int ry, const std::vector<std::vector<uint64_t>>& presum) {
    return presum[rx][ry] - presum[lx][ry] - presum[rx][ly] + presum[lx][ly];
}

int countInCrest(int x, int y, int k, const std::vector<std::vector<uint64_t>>& vec) {
    auto center = getSum(x, y + k, x + 3 * k, y + 2 * k, vec);
    auto left = getSum(x + k, y, x + 2 * k, y + k, vec);
    auto right = getSum(x + k, y + 2 * k, x + 2 * k, y + 3 * k, vec);
    auto result = center + left + right;
    return result;
}

bool check(int k, const std::vector<std::vector<uint64_t>>& vec, int n, int m) {
    for (int x = 0; x <= n - 3 * k; ++x) {
        for (int y = 0; y <= m - 3 * k; ++y) {
            if (countInCrest(x, y, k, vec) == 5 * k * k) {
                return true;
            }
        }
    }
    return false;
}
template <typename Func>
int binarySearch(int l, int r, const std::vector<std::vector<uint64_t>>& vec, Func fun, int n,
                 int m) {
    while (l < r) {
        auto med = (l + r + 1) / 2;
        if (fun(med, vec, n, m)) {
            l = med;
        } else {
            r = med - 1;
        }
    }
    return l;
}
std::vector<std::vector<uint64_t>> getPresum(const std::vector<std::vector<int>>& data) {
    size_t rows = data.size();
    size_t columns = data[0].size();
    std::vector<std::vector<uint64_t>> b(rows + 1, std::vector<uint64_t>(columns + 1, 0));
    for (size_t j = 0; j < columns; ++j) {
        for (size_t i = 0; i < rows; ++i) {
            b[i + 1][j + 1] = b[i][j + 1] + b[i + 1][j] - b[i][j] + data[i][j];
        }
    }
    return b;
}

auto main() -> int {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;

    std::vector<std::vector<int>> data(n, std::vector<int>(m, 0));
    std::string str;
    for (int i = 0; i < n; ++i) {
        std::cin >> str;
        for (int j = 0; j < m; ++j) {
            if (str[j] == '#') {
                data[i][j] = 1;
            }
        }
    }
    auto presum = getPresum(data);

    auto result = binarySearch(1, std::min(n, m) / 3, presum, check, n, m);

    std::cout << result;
}