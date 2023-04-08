#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <ranges>
#include <vector>

int main()
{
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
        double summ = numbers.back();
        numbers.pop_back();
        if (numbers.empty()) {
            std::cout << std::setprecision(2) << std::fixed << total_cost;
            return 0;
        }
        std::ranges::pop_heap(numbers, std::greater<>());
        summ += numbers.back();
        numbers.pop_back();
        total_cost += summ * 0.05;
        numbers.push_back(summ);
        std::ranges::push_heap(numbers, std::greater<>());
    }
    std::cout << std::setprecision(2) << std::fixed << total_cost;
    return 0;
}
