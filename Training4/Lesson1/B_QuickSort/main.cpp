#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename ForwardIterator>
void quicksort_impl(ForwardIterator first, ForwardIterator last)
{
    if (first == last)
        return;

    auto pivot = *std::next(first, std::distance(first, last) / 2);
    auto middle1 = std::partition(first, last, [pivot](const auto& em) {
        return em < pivot;
    });
    auto middle2 = std::partition(middle1, last, [pivot](const auto& em) {
        return !(pivot < em);
    });

    quicksort_impl(first, middle1);
    quicksort_impl(middle2, last);
}

int main()
{
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
