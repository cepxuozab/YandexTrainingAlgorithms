#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

namespace {
template <std::bidirectional_iterator Iterator, typename Predicate>
auto partition_impl(Iterator first, Iterator last, Predicate pred) -> Iterator {
    while (true) {
        while (first != last && pred(*first)) ++first;
        if (first == last) break;
        do {
            --last;
            if (first == last) return first;
        } while (!pred(*last));
        std::iter_swap(first, last);
        ++first;
    }
    return first;
}
template <std::bidirectional_iterator Iterator>
void quicksort_impl(Iterator first, Iterator last) {
    if (first == last) return;

    auto pivot = *std::next(first, std::distance(first, last) / 2);
    auto middle1 = partition_impl(first, last, [pivot](const auto& em) -> auto {
        return em < pivot;
    });
    auto middle2 = partition_impl(middle1, last, [pivot](const auto& em) -> auto {
        return !(pivot < em);
    });
    quicksort_impl(first, middle1);
    quicksort_impl(middle2, last);
}
}  // namespace

auto main() -> int {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int& i : arr) {
        std::cin >> i;
    }
    quicksort_impl(arr.begin(), arr.end());
    for (int& i : arr) {
        std::cout << i << ' ';
    }
}
