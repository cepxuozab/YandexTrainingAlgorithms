#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <vector>

namespace {
struct Interval {
    long long a{}, end{};
    int idx{};
    int color{};
};
}  // namespace

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    long long W;
    std::cin >> N >> W;

    std::vector<Interval> intervals(N);
    std::vector<std::pair<long long, int>> events;  // (x, type), type: -1 = конец, +1 = начало
    events.reserve(2LL * N);

    for (int i = 0; i < N; ++i) {
        long long a, w;
        std::cin >> a >> w;
        const long long end = a + w - 1;
        intervals[i] = {.a = a, .end = end, .idx = i + 1, .color = 0};
        events.emplace_back(a, +1);
        events.emplace_back(a + w, -1);  // точка сразу после конца
    }

    // Сортируем события: при равной координате сначала -1, потом +1
    std::ranges::sort(events);

    int cur = 0, k = 0;
    for (const auto& val : events | std::views::values) {
        cur += val;
        if (cur > k) k = cur;
    }

    // Сортируем отрезки по левой границе
    std::ranges::sort(intervals, {}, &Interval::a);

    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>,
                        std::greater<>>
        active;
    std::priority_queue<int, std::vector<int>, std::greater<>> free_colors;
    for (int c = 1; c <= k; ++c) free_colors.push(c);

    for (auto& in : intervals) {
        // Убираем отрезки, которые закончились до начала текущего
        while (!active.empty() && active.top().first < in.a) {
            free_colors.push(active.top().second);
            active.pop();
        }
        int c = free_colors.top();
        free_colors.pop();
        in.color = c;
        active.emplace(in.end, c);
    }

    // Сортируем по цвету (порядок падения)
    std::ranges::sort(intervals, {}, &Interval::color);

    std::cout << k << '\n';
    for (int i = 0; i < N; ++i) {
        if (i) std::cout << ' ';
        std::cout << intervals[i].idx;
    }
    std::cout << '\n';

    return 0;
}