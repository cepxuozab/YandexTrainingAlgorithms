#include <iostream>
#include <limits>
#include <span>
#include <vector>

auto MinimumPossibleNumberSegments(std::span<int> nums) -> std::vector<int> {
    std::vector<int> segmentLengths;
    int currentSegmentLength = 0;
    int maximumAllowedLength = std::numeric_limits<int>::max();
    for (auto&& currentValue : nums) {
        if (currentSegmentLength >= maximumAllowedLength || currentSegmentLength >= currentValue) {
            segmentLengths.push_back(currentSegmentLength);
            currentSegmentLength = 1;
            maximumAllowedLength = currentValue;
        } else {
            ++currentSegmentLength;
            maximumAllowedLength = std::min(maximumAllowedLength, currentValue);
        }
    }
    if (currentSegmentLength > 0) {
        segmentLengths.push_back(currentSegmentLength);
    }
    return segmentLengths;
}

auto main() -> int {
    int test_count;
    std::cin >> test_count;
    for (int test = 0; test < test_count; ++test) {
        int n;
        std::cin >> n;
        std::vector<int> nums(n);
        for (int& num : nums) {
            std::cin >> num;
        }
        auto ans = MinimumPossibleNumberSegments(nums);
        std::cout << ans.size() << '\n';
        for (auto&& a : ans) {
            std::cout << a << ' ';
        }
        std::cout << '\n';
    }
}