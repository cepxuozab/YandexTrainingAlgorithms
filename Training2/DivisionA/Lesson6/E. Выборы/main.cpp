#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

pair<bool, ull> rearrange_voters(const vector<pair<size_t, ull>>& v,
    const vector<ull>& prefix_sums, ull thr,
    size_t cur_party) {
    pair<size_t, ull> thr_tmp = { 0, thr };
    auto it = upper_bound(v.begin(), v.end(), thr_tmp,
        [](const auto& lhs, const auto& rhs) {
            return lhs.second < rhs.second;
        });
    size_t idx = it - v.begin();
    ull new_voters =
        prefix_sums[v.size()] - prefix_sums[idx] - (v.size() - idx) * thr;
    if (cur_party >= idx) {
        new_voters -= v[cur_party].second - thr;
    }
    bool is_winner = v[cur_party].second + new_voters > thr;
    return { is_winner, new_voters };
}

int main() {
    ull n;
    cin >> n;
    vector<pair<size_t, ull>> v(n);
    vector<ll> p(n);
    for (size_t i = 0; i < n; ++i) {
        ull tmp;
        cin >> tmp;
        v[i] = { i, tmp };
        cin >> p[i];
    }
    sort(v.begin(), v.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.second < rhs.second;
        });

    vector<ull> prefix_sums(n + 1, 0);
    for (size_t i = 0; i < n; ++i) {
        prefix_sums[i + 1] = prefix_sums[i] + v[i].second;
    }

    size_t res_idx = 0;
    ull res = 1 << 30;
    ull res_thr;
    ull res_new_voters;
    ull res_rest_voters;
    for (size_t i = 0; i < n; ++i) {
        if (p[v[i].first] == -1) {
            continue;
        }
        ull bot = 0;
        ull top = 1 << 30;
        bool is_winner;
        ull new_voters;
        while (bot < top) {
            ull thr = (top + bot) / 2 + 1;
            tie(is_winner, new_voters) =
                rearrange_voters(v, prefix_sums, thr, i);
            if (is_winner) {
                bot = thr;
            }
            else {
                top = thr - 1;
            }
        }
        tie(is_winner, new_voters) = rearrange_voters(v, prefix_sums, bot, i);
        if (!is_winner) {
            continue;
        }
        ull rest_voters = 0;
        if (v[i].second + new_voters > bot + 2) {
            rest_voters = v[i].second + new_voters - bot - 2;
            new_voters = bot + 2 - v[i].second;
        }
        ull res_tmp = new_voters + p[v[i].first];
        if (res_tmp < res) {
            res_idx = i;
            res = res_tmp;
            res_thr = bot;
            res_new_voters = new_voters;
            res_rest_voters = rest_voters;
        }
    }
    vector<ull> v_res(n);
    for (size_t i = 0; i < n; ++i) {
        if (i == res_idx) {
            v_res[v[i].first] = v[i].second + res_new_voters;
            continue;
        }
        if (v[i].second > res_thr) {
            v_res[v[i].first] = res_thr;
            if (res_rest_voters > 0) {
                ++v_res[v[i].first];
                --res_rest_voters;
            }
            continue;
        }
        v_res[v[i].first] = v[i].second;
    }

    cout << res << endl << v[res_idx].first + 1 << endl;
    for (size_t i = 0; i < n; ++i) {
        cout << v_res[i] << " ";
    }
    cout << endl;

    return 0;
}