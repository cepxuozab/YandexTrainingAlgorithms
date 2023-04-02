#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

int main()
{
    std::vector<int> arr;
    for (int x; std::cin >> x && x != 0;) {
        arr.push_back(x);
    }
    auto const min = *std::ranges::max_element(arr);
    std::cout << std::ranges::count(arr, min);
}
