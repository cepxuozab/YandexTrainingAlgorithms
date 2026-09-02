#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(m));
    for (auto& row : a)
        for (int& x : row) cin >> x;

    long long answer = 0;

    for (int i = 0; i <= (n - 1) / 2; ++i) {
        for (int j = 0; j <= (m - 1) / 2; ++j) {
            int i2 = n - 1 - i;
            int j2 = m - 1 - j;

            int cell[4], sz = 0;
            cell[sz++] = a[i][j];
            if (j2 != j) cell[sz++] = a[i][j2];
            if (i2 != i) cell[sz++] = a[i2][j];
            if (i2 != i && j2 != j) cell[sz++] = a[i2][j2];

            int best = 0;
            for (int p = 0; p < sz; ++p) {
                int cnt = 0;
                for (int q = 0; q < sz; ++q)
                    if (cell[q] == cell[p]) ++cnt;
                best = max(best, cnt);
            }
            answer += sz - best;
        }
    }

    cout << answer << '\n';
}