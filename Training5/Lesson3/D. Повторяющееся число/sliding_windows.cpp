#include <iostream>
#include <span>
#include <unordered_set>
#include <vector>

auto FindRepeatingNumber(std::span<int> nums, int k) -> const char* {
    std::unordered_set<int> sets;
    int i = 0;
    for (auto&& num : nums) {
        if (sets.contains(num)) {
            return "YES";
        }
        sets.insert(num);
        if (i >= k) {
            sets.erase(nums[i - k]);
        }
        i++;
    }
    return "NO";
}

auto main() -> int {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> nums(n);
    for (int& num : nums) {
        std::cin >> num;
    }
    puts(FindRepeatingNumber(nums, k));
}