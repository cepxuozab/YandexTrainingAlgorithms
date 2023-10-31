#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> ratings(n);
    for (int& rating : ratings) {
        std::cin >> rating;
    }
    std::vector<int> prefix_sum(n + 1);
    for (size_t i = 1; i < prefix_sum.size(); ++i) {
        prefix_sum[i] = prefix_sum[i - 1] + ratings[i - 1];
    }
    for (int i = 0; i < n; ++i) {
        int dissatisfaction = (i * ratings[i] - prefix_sum[i])
            + ((prefix_sum[n] - prefix_sum[i + 1]) - (n - i - 1) * ratings[i]);
        std::cout << dissatisfaction << ' ';
    }
}
