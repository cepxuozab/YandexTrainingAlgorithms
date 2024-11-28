#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

struct Chair {
    int h{}, w{};
    auto operator<=>(Chair const&) const = default;
};
auto main() -> int {
    int n, person_height;
    std::cin >> n >> person_height;
    std::vector<int> h(n), w(n);
    for (int& i : h) std::cin >> i;
    for (int& i : w) std::cin >> i;
    if (std::ranges::any_of(w, [&](int i) {
            return i >= person_height;
        })) {
        std::cout << 0;
        return 0;
    }
    std::vector<Chair> chairs(n);
    for (int i = 0; i < n; ++i) {
        chairs[i] = {.h = h[i], .w = w[i]};
    }
    std::ranges::sort(chairs);
    std::deque<int> deq;
    int ans = chairs.back().h - chairs.front().h;
    int now_len = chairs.front().w;
    int right = 1;
    for (int left = 0; left < n - 1; ++left) {
        while (right < n && now_len < person_height) {
            now_len += chairs[right].w;
            while (!deq.empty() && deq.back() < chairs[right].h - chairs[right - 1].h) {
                deq.pop_back();
            }
            deq.push_back(chairs[right].h - chairs[right - 1].h);
            right++;
        }
        if (now_len >= person_height) {
            ans = std::min(ans, deq.front());
        }
        now_len -= chairs[left].w;
        if (!deq.empty() && deq.front() == chairs[left + 1].h - chairs[left].h) {
            deq.pop_front();
        }
    }
    std::cout << ans;
}