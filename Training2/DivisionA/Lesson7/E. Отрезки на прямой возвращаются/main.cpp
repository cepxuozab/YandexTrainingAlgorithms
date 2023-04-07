#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

struct Event {
    ll x;
    ull l;
    size_t idx;
};

bool operator<(const Event& lhs, const Event& rhs) {
    return lhs.x == rhs.x && lhs.l > rhs.l || lhs.x < rhs.x;
}

int main() {
    ll n;
    cin >> n;
    vector<pair<ll, ll>> pairs;
    pairs.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        ll a, b;
        cin >> a >> b;
        pairs.push_back({ a, b });
    }

    vector<Event> events;
    events.reserve(n * 2);
    for (size_t i = 0; i < n; ++i) {
        auto [a, b] = pairs[i];
        events.push_back(Event{ a, static_cast<ull>(b - a), i });
    }
    sort(events.begin(), events.end());

    deque<size_t> st;
    vector<size_t> res(n, 0);
    for (size_t i = 0; i < n; ++i) {
        auto& event = events[i];
        while (!st.empty() &&
            pairs[event.idx].second > pairs[st.back()].second) {
            st.pop_back();
        }
        res[event.idx] = st.empty() ? 0 : st.back() + 1;
        st.push_back(event.idx);
    }

    for (size_t i = 0; i < n; ++i) {
        cout << res[i] << " ";
    }
    cout << endl;

    return 0;
}