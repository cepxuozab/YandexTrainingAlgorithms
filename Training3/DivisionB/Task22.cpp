#include <iostream>
#include <vector>

int main()
{
    int n, k;
    std::cin >> n >> k;
    k = k > n ? n : k;
    std::vector<int> desk(n + k, 0);
    desk[k] = 1;
    for (int i = k; i != n + k; ++i) {
        for (int j = i - 1; j != i - k - 1; --j) {
            desk[i] += desk[j];
        }
    }
    std::cout << desk.back() << std::endl;
}
