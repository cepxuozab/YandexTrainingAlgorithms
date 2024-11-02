#include <iostream>
#include <queue>
#include <set>

template <typename T>
auto operator>>(std::istream& input, std::vector<T>& arr) -> std::istream& {
    for (auto& a : arr) input >> a;
    return input;
}

struct Task {
    int a{}, b{}, idx{};
};

auto main() -> int {  // NOLINT
    int n;
    std::cin >> n;
    std::vector<int> a(n), b(n), c(n);
    std::cin >> a >> b >> c;
    auto compare = [](Task const& lhs, Task const& rhs) -> bool {
        return std::tuple(lhs.a, lhs.b, -lhs.idx) < std::tuple(rhs.a, rhs.b, -rhs.idx);
    };
    std::priority_queue<Task, std::vector<Task>, decltype(compare)> one{compare};
    auto compare1 = [](Task const& lhs, Task const& rhs) -> bool {
        return std::tuple(lhs.b, lhs.a, -lhs.idx) < std::tuple(rhs.b, rhs.a, -rhs.idx);
    };
    std::priority_queue<Task, std::vector<Task>, decltype(compare1)> two{compare1};
    std::set<int> deleted_id;
    for (int i = 0; i < n; ++i) {
        one.push({a[i], b[i], i});
        two.push({a[i], b[i], i});
    }
    for (int i : c) {
        if (i == 0) {
            while (!one.empty() && deleted_id.contains(one.top().idx)) {
                one.pop();
            }
            auto res = one.top();
            one.pop();
            std::cout << res.idx + 1 << ' ';
            deleted_id.insert(res.idx);
        } else {
            while (!two.empty() && deleted_id.contains(two.top().idx)) {
                two.pop();
            }
            auto res = two.top();
            two.pop();
            std::cout << res.idx + 1 << ' ';
            deleted_id.insert(res.idx);
        }
    }
}