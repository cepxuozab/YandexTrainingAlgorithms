#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

int main()
{
    std::unordered_map<int, int> nums;
    std::vector<int> arr;
    for (int x; std::cin >> x;) {
        nums[x]++;
        arr.push_back(x);
    }
    auto only_one = [&](int a) { return nums.contains(a) && nums.at(a) == 1; };
    std::ranges::copy(std::ranges::views::filter(arr, only_one), std::ostream_iterator<int>(std::cout, " "));
    return 0;
}
