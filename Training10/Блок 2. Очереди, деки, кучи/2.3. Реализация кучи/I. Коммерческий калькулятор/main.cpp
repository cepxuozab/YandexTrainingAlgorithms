#include <algorithm>
#include <iostream>
#include <print>
#include <queue>
#include <vector>

auto main() -> int {
    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (auto& num : numbers) {
        std::cin >> num;
    }
    std::ranges::make_heap(numbers, std::greater<>());
    double total_cost = 0;
    while (!numbers.empty()) {
        std::ranges::pop_heap(numbers, std::greater<>());
        int current_value = numbers.back();
        numbers.pop_back();
        if (numbers.empty()) {
            break;
        }
        std::ranges::pop_heap(numbers, std::greater<>());
        current_value += numbers.back();
        numbers.pop_back();
        constexpr double kTaxRate = 0.05;
        total_cost += current_value * kTaxRate;
        numbers.push_back(current_value);
        std::ranges::push_heap(numbers, std::greater<>());
    }
    std::println("{:.2f}", total_cost);
    return 0;
}