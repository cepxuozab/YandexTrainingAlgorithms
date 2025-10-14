#include <bits/stdc++.h>

using namespace std;

struct Node {
    double d;
    int loc, carried, delivered;

    auto operator<(Node const &o) const -> bool { return d > o.d; } // for min-heap
};

auto main() -> int {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int a, b, c;
    double v0, v1, v2;
    if (!(cin >> a >> b >> c >> v0 >> v1 >> v2)) return 0;

    // distances between nodes: 0=Home(H),1=Shop(S),2=Post(P)
    double D[3][3]{};
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) D[i][j] = 1e18;
    D[0][1] = D[1][0] = a;
    D[0][2] = D[2][0] = b;
    D[1][2] = D[2][1] = c;
    D[0][0] = D[1][1] = D[2][2] = 0.0;

    auto speed = [&](int carried) -> double {
        int cnt = ((carried & 1) ? 1 : 0) + ((carried & 2) ? 1 : 0);
        if (cnt == 0) return v0;
        if (cnt == 1) return v1;
        return v2;
    };

    // distance table: loc (0..2), carried (0..3), delivered (0..3)
    const double INF = 1e100;
    double dist[3][4][4]{};
    for (int i = 0; i < 3; i++) for (int j = 0; j < 4; j++) for (int k = 0; k < 4; k++) dist[i][j][k] = INF;

    priority_queue<Node> pq;
    dist[0][0][0] = 0.0;
    pq.push({0.0, 0, 0, 0});

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();
        if (cur.d > dist[cur.loc][cur.carried][cur.delivered] + 1e-15) continue;

        // check goal: at home and both delivered
        if (cur.loc == 0 && cur.delivered == 3) {
            cout.setf(std::ios::fixed);
            cout << setprecision(15) << cur.d << "\n";
            return 0;
        }

        // 1) If at home, can drop carried into delivered (instant)
        if (cur.loc == 0 && cur.carried != 0) {
            int nd = cur.delivered | cur.carried;
            if (dist[0][0][nd] > cur.d + 1e-15) {
                dist[0][0][nd] = cur.d;
                pq.push({cur.d, 0, 0, nd});
            }
        }

        // 2) If at shop (1), can pick products if not yet delivered and not already carried
        if (cur.loc == 1) {
            bool notDelivered = !(cur.delivered & 1);
            bool notCarried = !(cur.carried & 1);
            if (notDelivered && notCarried) {
                int nc = cur.carried | 1;
                if (dist[1][nc][cur.delivered] > cur.d + 1e-15) {
                    dist[1][nc][cur.delivered] = cur.d;
                    pq.push({cur.d, 1, nc, cur.delivered});
                }
            }
        }

        // 3) If at post (2), can pick parcel similarly
        if (cur.loc == 2) {
            bool notDelivered = !(cur.delivered & 2);
            bool notCarried = !(cur.carried & 2);
            if (notDelivered && notCarried) {
                int nc = cur.carried | 2;
                if (dist[2][nc][cur.delivered] > cur.d + 1e-15) {
                    dist[2][nc][cur.delivered] = cur.d;
                    pq.push({cur.d, 2, nc, cur.delivered});
                }
            }
        }

        // 4) Move to other locations
        double spd = speed(cur.carried);
        for (int to = 0; to < 3; ++to) {
            if (to == cur.loc) continue;
            double len = D[cur.loc][to];
            if (len >= 1e17) continue;
            double ndist = cur.d + len / spd;
            if (ndist + 1e-15 < dist[to][cur.carried][cur.delivered]) {
                dist[to][cur.carried][cur.delivered] = ndist;
                pq.push({ndist, to, cur.carried, cur.delivered});
            }
        }
    }

    // should never reach here as problem constraints guarantee feasibility
    return 0;
}
