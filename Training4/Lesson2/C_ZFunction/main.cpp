#include <iostream>
#include <string>
#include <string_view>
#include <vector>

std::vector<int> ZFunction(std::string_view str);
void Print(std::vector<int> const& arr);

int main()
{
    std::string str;
    std::cin >> str;
    Print(ZFunction(str));
    return 0;
}

std::vector<int> ZFunction(std::string_view str)
{
    int n = (int)str.length();
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) {
            z[i] = std::min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && str[z[i]] == str[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

void Print(std::vector<int> const& arr)
{
    bool first = true;
    for (int a : arr) {
        if (!first) {
            std::cout << ' ';
        }
        first = false;
        std::cout << a;
    }
}
