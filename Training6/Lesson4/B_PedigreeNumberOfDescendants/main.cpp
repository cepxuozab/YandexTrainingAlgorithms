#include <iostream>
#include <map>
#include <string>
#include <vector>

auto main() -> int {  // NOLINT
    int n;
    std::cin >> n;
    std::map<std::string, std::vector<std::string>> children;
    std::map<std::string, int> cnt;
    for (int i = 0; i + 1 < n; ++i) {
        std::string child, parent;
        std::cin >> child >> parent;
        children[parent].push_back(child);
        cnt[child] = -1;
        cnt[parent] = -1;
    }
    auto get_cnt = [&](auto&& self, std::string const& name) -> int {
        if (cnt[name] == -1) {
            cnt[name] = 0;
            if (children.contains(name)) {
                for (auto const& child : children[name]) {
                    cnt[name] += self(self, child) + 1;
                }
            }
        }
        return cnt[name];
    };
    for (auto const& [name, _] : cnt) {
        get_cnt(get_cnt, name);
    }
    for (auto const& [name, num] : cnt) {
        std::cout << name << ' ' << num << '\n';
    }
}