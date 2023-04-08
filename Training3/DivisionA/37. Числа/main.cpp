#include <algorithm>
#include <array>
#include <deque>
#include <iostream>
#include <iterator>
#include <vector>

auto main() -> int
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    int start, end;
    std::cin >> start >> end;
    const int SIZE = 10'000;
    typedef int (*Func)(int);
    Func AddOne = [](int x) { return x / 1000 != 9 ? x + 1000 : x; };
    Func MinusOne = [](int x) { return x % 10 > 1 ? x - 1 : x; };
    Func ShiftLeft = [](int x) { return (x % 1000) * 10 + x / 1000; };
    Func ShiftRight = [](int x) { return (x % 10) * 1000 + x / 10; };
    std::array<Func, 4> rules{ AddOne, MinusOne, ShiftLeft, ShiftRight };
    std::vector<int> visited(SIZE, 0), prevs(SIZE, -1);
    visited[start] = 1;
    std::deque<int> queue{ start };
    while (!queue.empty()) {
        auto now = queue.front();
        queue.pop_front();
        if (now == end) {
            break;
        }
        for (auto rule : rules) {
            int v = rule(now);
            if (visited[v] == 0) {
                visited[v] = 1;
                prevs[v] = now;
                queue.push_back(v);
            }
        }
    }
    std::vector<int> ans{ end };
    for (int prev = prevs[end]; prev != -1; prev = prevs[prev]) {
        ans.push_back(prev);
    }
    std::copy(ans.rbegin(), ans.rend(), std::ostream_iterator<int>(std::cout, " "));
    return 0;
}
