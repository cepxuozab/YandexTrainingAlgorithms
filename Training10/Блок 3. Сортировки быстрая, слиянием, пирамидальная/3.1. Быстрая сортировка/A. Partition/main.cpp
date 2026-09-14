#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename Predicate, typename ForwardIterator>
auto partition_impl(ForwardIterator first, ForwardIterator last, Predicate pred)
    -> ForwardIterator
{
    while (true) {
        if (first == last) {
            return first;
        }
        if (not pred(*first)) {
            break;
        }
        ++first;
    }
    for (auto p = first; ++p != last;) {
        if (pred(*p)) {
            std::iter_swap(first, p);
            ++first;
        }
    }
    return first;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int& i : arr) {
        std::cin >> i;
    }
    int b;
    std::cin >> b;
    auto predicat = [b](int a) { return a < b; };
    auto middle = partition_impl(arr.begin(), arr.end(), predicat);
    std::cout << std::distance(arr.begin(), middle) << '\n'
              << std::distance(middle, arr.end()) << std::endl;
}
