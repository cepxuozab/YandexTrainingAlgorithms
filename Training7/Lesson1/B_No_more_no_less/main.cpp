#include <iostream>
#include <vector>
#include <climits>

void Handle(std::vector<int> const& query) {
    std::vector<int> ans;
    int counter = 0;
    int length = 0;
    int min_number = INT_MAX;
    for (int number : query) {
        if (number > length && min_number > length) {
            length += 1;
            min_number = std::min(min_number, number);
        } else {
            counter += 1;
            ans.push_back(length);
            length = 1;
            min_number = number;
        }
    }
    if (length > 0) {
        counter += 1;
        ans.push_back(length);
    }
    std::cout << counter << '\n';
    for (int a : ans) std::cout << a << ' ';
    std::cout << '\n';
}

void NoMoreNoLess() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        int n;
        std::cin >> n;
        std::vector<int> query(n);
        for (auto& a : query) std::cin >> a;
        Handle(query);
    }
}

auto main() -> int {
    NoMoreNoLess();
}