#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

auto main() -> int {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int &a : arr) std::cin >> a;

    int total_sum = 0;
    int max_even = INT_MIN;  // максимум на чётных позициях (i = 2, 4, ...)
    int min_odd = INT_MAX;   // минимум на нечётных позициях (i = 1, 3, ...)

    for (int i = 0; i < n; ++i) {
        int pos = i + 1; // позиция с 1
        if (pos % 2 == 1) { // нечётная позиция
            total_sum += arr[i];
            min_odd = std::min(min_odd, arr[i]);
        } else { // чётная позиция
            total_sum -= arr[i];
            max_even = std::max(max_even, arr[i]);
        }
    }

    int improvement = 2 * std::max(0, max_even - min_odd);
    std::cout << total_sum + improvement << std::endl;

    return 0;
}