#include <algorithm>
#include <iostream>
#include <vector>

namespace my_sort {

template <class RandomIt> void sort_heap(RandomIt first, RandomIt last) {
    while (first != last)
        std::pop_heap(first, last--);
}
} // namespace

auto main() -> int {
    freopen("input.txt", "r", stdin);
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int& a : arr) {
        std::cin >> a;
    }
    std::make_heap(arr.begin(), arr.end());
    my_sort::sort_heap(arr.begin(), arr.end());
    for (int a : arr) {
        std::cout << a << " ";
    }
}
