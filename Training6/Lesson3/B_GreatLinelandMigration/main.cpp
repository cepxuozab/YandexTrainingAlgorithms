#include <iostream>
#include <stack>
#include <vector>

int main() {  // NOLINT

    int n;
    std::cin >> n;
    std::vector<int> input(n);
    for (int& a : input) std::cin >> a;

    std::stack<int> nums;
    nums.push(-1);
    std::stack<int> costs;
    costs.push(-1);

    std::vector<int> ans(n, -1);
    for (int i = 0; i < n; ++i) {
        int cost = input[i];
        while (cost < costs.top()) {
            ans[nums.top()] = i;
            costs.pop();
            nums.pop();
        }
        costs.push(cost);
        nums.push(i);
    }
    for (auto& i : ans) std::cout << i << " ";

    return 0;
}