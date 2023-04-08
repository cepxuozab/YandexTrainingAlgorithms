#include <iostream>

static const auto FastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr; }();

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    int n, k, row, column;
    std::cin >> n >> k >> row >> column;
    int pos1 = (row - 1) * 2 + column - k;
    int pos2 = (row - 1) * 2 + column + k;
    int row1 = (pos1 + 1) / 2;
    int row2 = (pos2 + 1) / 2;
    if (pos1 > 0 && (pos2 > n || abs(row - row1) < abs(row - row2))) {
        std::cout << row1 << ' ' << 2 - pos1 % 2 << std::endl;
    } else if (pos2 <= n) {
        std::cout << row2 << ' ' << 2 - pos2 % 2 << std::endl;
    } else {
        std::cout << -1 << std::endl;
    }
}
