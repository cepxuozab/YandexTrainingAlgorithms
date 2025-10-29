#include <bits/stdc++.h>
using namespace std;

const long double EPS = 1e-9L;
struct Event {
    long double t;
    int type; // 0 = collision, 1 = border crash, 2 = finish
    int a, b; // a = index (or first index), b = second index for collision or -1
};
struct Model {
    long double x, y, vx, vy;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    long double L, W;
    if(!(cin >> N >> L >> W)) return 0;
    vector<Model> m(N);
    for (int i = 0; i < N; ++i) {
        double xi, yi, vxi, vyi;
        cin >> xi >> yi >> vxi >> vyi;
        m[i].x = xi; m[i].y = yi; m[i].vx = vxi; m[i].vy = vyi;
    }

    vector<Event> events;
    events.reserve(N + N + (long long)N*(N-1)/2);

    // border crashes (y=0 or y=W)
    for (int i = 0; i < N; ++i) {
        if (fabsl(m[i].vy) < EPS) continue;
        if (m[i].vy > 0) {
            long double t = (W - m[i].y) / m[i].vy;
            if (t > EPS) events.push_back({t, 1, i, -1});
        } else {
            long double t = -m[i].y / m[i].vy; // vy<0 so denominator negative, t>0
            if (t > EPS) events.push_back({t, 1, i, -1});
        }
    }

    // finishes (x = L) if vx>0 and y at finish strictly inside (0,W)
    for (int i = 0; i < N; ++i) {
        if (m[i].vx <= 0) continue;
        long double t = (L - m[i].x) / m[i].vx;
        if (t <= EPS) continue;
        long double yf = m[i].y + m[i].vy * t;
        // if equals 0 or W -> it's border crash instead of finish; those border events already added
        if (yf > EPS && yf < W - EPS) {
            events.push_back({t, 2, i, -1});
        }
    }

    // collisions pairs
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            long double dx = m[i].x - m[j].x;
            long double dy = m[i].y - m[j].y;
            long double dvx = m[i].vx - m[j].vx;
            long double dvy = m[i].vy - m[j].vy;

            if (fabsl(dvx) < EPS && fabsl(dvy) < EPS) continue; // parallel identical velocities -> never meet
            long double t = NAN;
            bool ok = false;
            if (fabsl(dvx) < EPS) {
                // need dx == 0 and solve by dvy
                if (fabsl(dx) < EPS && fabsl(dvy) > EPS) {
                    t = -dy / dvy;
                    ok = (t > EPS);
                } else if (fabsl(dx) < EPS && fabsl(dvy) < EPS) {
                    // both differences 0 (shouldn't: handled above), or no relative motion in y -> no meet
                    ok = false;
                }
            } else if (fabsl(dvy) < EPS) {
                if (fabsl(dy) < EPS && fabsl(dvx) > EPS) {
                    t = -dx / dvx;
                    ok = (t > EPS);
                } else ok = false;
            } else {
                long double tx = -dx / dvx;
                long double ty = -dy / dvy;
                if (fabsl(tx - ty) < 1e-9L && tx > EPS) {
                    t = tx;
                    ok = true;
                } else ok = false;
            }

            if (ok && isfinite((double)t)) {
                events.push_back({t, 0, i, j});
            }
        }
    }

    // sort events by time, and type order: collisions & border (0,1) before finish (2)
    sort(events.begin(), events.end(), [](const Event &a, const Event &b){
        if (fabsl(a.t - b.t) > 1e-12L) return a.t < b.t;
        return a.type < b.type; // collisions(0), border(1) first, finish(2) last
    });

    vector<char> alive(N, 1);
    int idx = 0;
    int M = (int)events.size();

    // we'll scan events grouped by time
    while (idx < M) {
        int j = idx;
        long double t = events[idx].t;
        // group [idx, j)
        while (j < M && fabsl(events[j].t - t) <= 1e-9L) ++j;

        // snapshot of alive at start of this time
        vector<char> alive_start = alive;

        // first find all models to remove due to collisions or border crashes at this time
        vector<char> will_remove(N, 0);
        for (int k = idx; k < j; ++k) {
            const Event &e = events[k];
            if (e.type == 0) {
                int a = e.a, b = e.b;
                if (alive_start[a] && alive_start[b]) {
                    will_remove[a] = 1;
                    will_remove[b] = 1;
                }
            } else if (e.type == 1) {
                int a = e.a;
                if (alive_start[a]) will_remove[a] = 1;
            }
        }

        // apply removals
        for (int i = 0; i < N; ++i) if (will_remove[i]) alive[i] = 0;

        // now process finishes at this time: those alive after removal and have finish event at this time
        vector<int> finishing_now;
        for (int k = idx; k < j; ++k) {
            const Event &e = events[k];
            if (e.type == 2) {
                int a = e.a;
                if (alive[a]) finishing_now.push_back(a);
            }
        }

        if (!finishing_now.empty()) {
            sort(finishing_now.begin(), finishing_now.end());
            // print winners (1-based indices)
            cout << finishing_now.size() << "\n";
            for (size_t ii = 0; ii < finishing_now.size(); ++ii) {
                if (ii) cout << " ";
                cout << (finishing_now[ii] + 1);
            }
            cout << "\n";
            return 0;
        }

        idx = j;
    }

    // if we got here — никто не финишировал
    cout << 0 << "\n";
    return 0;
}
