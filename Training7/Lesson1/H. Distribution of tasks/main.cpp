#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int task_distribution(const vector<string>& tasks) {
    vector<pair<int, int>> odds;
    int even_buf1 = 0, even_buf2 = 0;

    for (const auto& task : tasks) {
        int even_count = 0, odd_count = 0;
        for (size_t j = 0; j < task.size(); j += 2)
            if (task[j] == 'S') ++even_count;
        for (size_t j = 1; j < task.size(); j += 2)
            if (task[j] == 'S') ++odd_count;

        if (task.size() % 2 == 1) {
            odds.emplace_back(even_count, odd_count);
        } else {
            even_buf1 += even_count;
            even_buf2 += max(even_count, odd_count);
        }
    }

    int ans = odds.empty() ? even_buf1 : even_buf2;

    // Sort by (even_count - odd_count) descending
    ranges::sort(odds, [](const auto& a, const auto& b) {
        return (a.first - a.second) > (b.first - b.second);
    });

    int mid = (static_cast<int>(odds.size()) - 1) / 2;
    for (int i = 0; i < static_cast<int>(odds.size()); ++i) {
        if (i <= mid) {
            ans += odds[i].first;
        } else {
            ans += odds[i].second;
        }
    }

    return ans;
}

int main() {
    int n;
    cin >> n;
    cin.ignore(); // пропустить символ новой строки после числа
    vector<string> tasks(n);
    for (int i = 0; i < n; ++i) {
        getline(cin, tasks[i]);
    }

    cout << task_distribution(tasks) << '\n';
    return 0;
}
