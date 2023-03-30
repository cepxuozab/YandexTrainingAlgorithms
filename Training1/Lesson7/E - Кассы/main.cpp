#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int
{
    freopen("input.txt", "r", stdin);
    int const MINUTES = 60;
    int const HOURS = 24;
    std::vector<int> cashboxes(MINUTES * HOURS, 0);
    int const SIZE = (int)cashboxes.size();
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        int lhs = a * MINUTES + b;
        int rhs = c * MINUTES + d;
        if (rhs > lhs) {
            for (; lhs != rhs; ++lhs) {
                cashboxes[lhs]++;
            }
        } else {
            for (int i = 0; i < rhs; ++i) {
                cashboxes[i]++;
            }
            for (int i = lhs; i != SIZE; ++i) {
                cashboxes[i]++;
            }
        }
    }
    std::cout << count(cashboxes.begin(), cashboxes.end(), n) << std::endl;
}
