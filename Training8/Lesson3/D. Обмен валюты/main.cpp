#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long p;
    cin >> n >> p;

    vector<long long> c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    vector<pair<long long, int>> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = {c[i], i};
    }

    sort(arr.begin(), arr.end());

    vector<long long> vals(n);
    for (int i = 0; i < n; ++i) {
        vals[i] = arr[i].first;
    }

    long double best_diff = 1e30;
    int idx_i = -1, idx_j = -1;

    for (int j = 0; j < n; ++j) {
        long long cj = arr[j].first;
        // p * cj <= 1e18 < LLONG_MAX
        long long target = p * cj;

        // Найти позицию первого >= target
        auto it = lower_bound(vals.begin(), vals.end(), target);
        vector<int> candidates;

        if (it != vals.end()) {
            candidates.push_back(it - vals.begin());
        }
        if (it != vals.begin()) {
            candidates.push_back(it - vals.begin() - 1);
        }

        for (int i_pos : candidates) {
            if (i_pos == j) continue;

            long long ci = arr[i_pos].first;
            long double diff = fabsl((long double)ci / (long double)cj - (long double)p);
            if (diff < best_diff) {
                best_diff = diff;
                idx_i = arr[i_pos].second;
                idx_j = arr[j].second;
            }
        }
    }

    cout << idx_i + 1 << " " << idx_j + 1 << "\n";
    return 0;
}