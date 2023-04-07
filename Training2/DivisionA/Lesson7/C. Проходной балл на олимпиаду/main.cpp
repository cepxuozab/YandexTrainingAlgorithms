#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

int main() {
    ull n, m, r;
    cin >> n >> m >> r;
    map<ull, vector<ll>> regions;
    map<ull, bool> region_flags;
    for (size_t i = 0; i < n; ++i) {
        ull id, region, is_prizewinner;
        ll score;
        cin >> id >> region >> score >> is_prizewinner;
        if (is_prizewinner) {
            --m;
            region_flags[region] = true;
            continue;
        }
        regions[region].push_back(score);
    }
    vector<ll> all_scores;
    for (auto& [region, scores] : regions) {
        sort(scores.begin(), scores.end());
        if (!region_flags[region] && scores.size() >= 1) {
            --m;
            scores.pop_back();
        }
        for (auto score : scores) {
            all_scores.push_back(score);
        }
    }
    sort(all_scores.begin(), all_scores.end());
    if (m >= all_scores.size()) {
        cout << 0 << endl;
        return 0;
    }
    cout << all_scores[all_scores.size() - m - 1] + 1 << endl;

    return 0;
}