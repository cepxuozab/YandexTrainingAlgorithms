#include <algorithm>
#include <iostream>
#include <vector>

auto ReadArray() -> std::vector<int>;

auto LCS(std::vector<int> const& lhs, std::vector<int> const& rhs) -> std::vector<int>;

void PrintArray(std::vector<int> const& arr);

auto main() -> int
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    auto first = ReadArray();
    auto second = ReadArray();
    PrintArray(LCS(first, second));
    return 0;
}

auto ReadArray() -> std::vector<int>
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int& i : arr) {
        std::cin >> i;
    }
    return arr;
}

auto LCS(std::vector<int> const& lhs, std::vector<int> const& rhs) -> std::vector<int>
{
    int m = lhs.size();
    int n = rhs.size();
    std::vector<std::vector<int>> LCS_table(m + 1, std::vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (lhs[i - 1] == rhs[j - 1])
                LCS_table[i][j] = LCS_table[i - 1][j - 1] + 1;
            else
                LCS_table[i][j] = std::max(LCS_table[i - 1][j], LCS_table[i][j - 1]);
        }
    }
    int index = LCS_table.back().back();
    std::vector<int> ans(index);
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (lhs[i - 1] == rhs[j - 1]) {
            ans[index - 1] = lhs[i - 1];
            i--;
            j--;
            index--;
        }

        else if (LCS_table[i - 1][j] > LCS_table[i][j - 1])
            i--;
        else
            j--;
    }

    return ans;
}

void PrintArray(std::vector<int> const& arr)
{
    for (int a : arr) {
        std::cout << a << ' ';
    }
    std::cout << std::endl;
}
