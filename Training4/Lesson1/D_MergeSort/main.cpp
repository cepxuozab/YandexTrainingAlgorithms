#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

auto const FASTIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

std::vector<int> Read()
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int& i : arr) {
        std::cin >> i;
    }
    return arr;
}
template <typename RandomIt>
void MergeSort(RandomIt first, RandomIt last)
{
    auto range = std::distance(first, last);
    if (range < 2) {
        return;
    }
    std::vector<typename RandomIt::value_type> tmp(first, last);
    auto middle = std::next(tmp.begin(), range / 2);
    MergeSort(tmp.begin(), middle);
    MergeSort(middle, tmp.end());
    std::merge(tmp.begin(), middle, middle, tmp.end(), first);
}
int main()
{
    auto arr = Read();
    MergeSort(arr.begin(), arr.end());
    for (int i : arr) {
        std::cout << i << ' ';
    }
}
