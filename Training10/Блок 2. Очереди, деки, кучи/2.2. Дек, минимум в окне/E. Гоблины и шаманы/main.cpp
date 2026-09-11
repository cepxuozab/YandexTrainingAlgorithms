#include <deque>
#include <iostream>
#include <ranges>

using namespace std;
namespace rng = std::ranges;
namespace view = rng::views;

auto main() -> int {
    int N;
    cin >> N;
    deque<int> left, right;
    for ([[maybe_unused]] auto i : view::iota(0, N)) {
        char priority;
        cin >> priority;
        if (priority == '-') {
            cout << left.front() << '\n';
            left.pop_front();
        } else {
            int n;
            cin >> n;
            if (priority == '+') {
                right.push_back(n);
            } else {
                right.push_front(n);
            }
        }
        while (right.size() > left.size()) {
            left.push_back(right.front());
            right.pop_front();
        }
    }
}