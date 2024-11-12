#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

auto Empty(const vector<deque<pair<int, int>>>& roads) -> bool {
    return std::ranges::all_of(roads, [](auto const& elem) {
        return elem.empty();
    });
}

auto circleOf4Down(int num) -> int {
    return num == 0 ? 3 : num - 1;
}

auto circleOf4Up(int num) -> int {
    return (num + 1) % 4;
}

auto circleOf4other(int num) -> int {
    return (num + 2) % 4;
}

auto main() -> int {  // NOLINT
    int n;
    cin >> n;
    int a, b;
    cin >> a >> b;
    vector<deque<pair<int, int>>> roads(4);
    vector<bool> mainlands(4, false);
    vector<int> ans(n);

    mainlands[a - 1] = true;
    mainlands[b - 1] = true;
    int index = 0;
    while (n--) {
        int d, t;
        cin >> d >> t;
        roads[d - 1].emplace_back(index++, t);
    }

    for (auto& road : roads) {
        std::ranges::sort(road, [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
        });
    }

    int time = 1;
    vector<bool> queue_of_ans(4, false);
    while (!Empty(roads)) {
        for (int i = 0; i < 4; i++) {
            if (!roads[i].empty() && roads[i].front().second <= time) {
                if (mainlands[i] == true) {
                    if (mainlands[circleOf4Down(i)] != true || roads[circleOf4Down(i)].empty()
                        || roads[circleOf4Down(i)].front().second > time) {
                        ans[roads[i].front().first] = time;
                        queue_of_ans[i] = true;
                    }
                } else {
                    if (((mainlands[circleOf4Up(i)] != true || roads[circleOf4Up(i)].empty()
                          || roads[circleOf4Up(i)].front().second > time)
                         && (roads[circleOf4Down(i)].empty()
                             || roads[circleOf4Down(i)].front().second > time))
                        && (mainlands[circleOf4other(i)] != true || roads[circleOf4other(i)].empty()
                            || roads[circleOf4other(i)].front().second > time)) {
                        ans[roads[i].front().first] = time;
                        queue_of_ans[i] = true;
                    }
                }
            }
        }
        for (int i = 0; i < 4; i++) {
            if (queue_of_ans[i] == true) {
                queue_of_ans[i] = false;
                ans[roads[i].front().first] = time;
                roads[i].pop_front();
            }
        }
        time++;
    }
    for (int i : ans) {
        cout << i << '\n';
    }
}
