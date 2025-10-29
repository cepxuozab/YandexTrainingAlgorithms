#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::cin >> m;
    std::vector<int> b(m);
    for (int i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    // Лямбда-функция для вычисления суммы с весами
    auto compute_weighted_sum = [](const std::vector<int> &values, const std::vector<int> &other_values) -> long long {
        std::vector<int> sorted_other = other_values;
        std::sort(sorted_other.begin(), sorted_other.end());

        int other_size = sorted_other.size();
        std::vector<long long> prefix(other_size + 1, 0);
        for (int i = 0; i < other_size; i++) {
            prefix[i + 1] = prefix[i] + sorted_other[i];
        }
        long long total_sum_other = prefix[other_size];

        long long result = 0;
        int values_size = values.size();

        for (int i = 0; i < values_size; i++) {
            int pos = std::upper_bound(sorted_other.begin(), sorted_other.end(), values[i]) - sorted_other.begin();
            int count_le = pos;
            long long sum_le = prefix[count_le];

            long long S = (2LL * count_le - other_size) * values[i] + total_sum_other - 2 * sum_le;
            result += (i + 1) * S;
        }

        return result;
    };

    long long F1 = compute_weighted_sum(a, b);
    long long F2 = compute_weighted_sum(b, a);

    std::cout << F1 - F2 << std::endl;

    return 0;
}