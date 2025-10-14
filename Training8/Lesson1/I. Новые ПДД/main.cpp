#include <bits/stdc++.h>
using namespace std;
auto main() -> int {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long x,y,f,g;
    if(!(cin>>x>>y)) return 0;
    cin>>f>>g;
    long long dx = llabs(f - x);
    long long dy = llabs(g - y);

    long long ans;
    if (dx == 0 && dy == 0) {
        ans = 0;
    } else if (dx == 0 || dy == 0) {
        long long m = max(dx,dy);
        ans = 3*m - 3; // (moves = 3*m - 2) -> maneuvers = moves - 1
    } else {
        ans = 3*(dx + dy) - 5; // (moves = 3*(dx+dy)-4) -> maneuvers = moves - 1
    }

    cout << ans << '\n';
    return 0;
}
