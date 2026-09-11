#include <iostream>
#include <queue>
#include <vector>

auto main() -> int {
    int n;
    std::cin >> n;
    std::priority_queue<int> left;
    std::priority_queue<int, std::vector<int>, std::greater<>> right;
    std::vector<int> ans;
    ans.reserve(n);

    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;

        if (left.empty() || x < left.top())
            left.push(x);
        else
            right.push(x);

        if (left.size() > right.size() + 1) {
            right.push(left.top());
            left.pop();
        } else if (right.size() > left.size()) {
            left.push(right.top());
            right.pop();
        }

        ans.push_back(left.top());
    }
    for (auto x : ans)
        std::cout << x << ' ';
}