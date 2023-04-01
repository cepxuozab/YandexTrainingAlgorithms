#include <iostream>

int main()
{
    int n, i, j, a;
    std::cin >> n >> i >> j;
    if (i < j)
        a = i + abs(j - n) - 1;
    else
        a = j + abs(i - n) - 1;
    int b = abs(i - j) - 1;
    std::cout << (a < b ? a : b) << '\n';
    return 0;
}