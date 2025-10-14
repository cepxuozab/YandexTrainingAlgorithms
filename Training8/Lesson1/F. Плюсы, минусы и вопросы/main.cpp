#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> table(n);
    for (int i = 0; i < n; i++) cin >> table[i];

    vector<int> baseRow(n, 0), baseCol(m, 0), qRow(n, 0), qCol(m, 0);

    // посчитаем базовые суммы и количество '?'
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (table[i][j] == '+') {
                baseRow[i]++;
                baseCol[j]++;
            } else if (table[i][j] == '-') {
                baseRow[i]--;
                baseCol[j]--;
            } else {
                qRow[i]++;
                qCol[j]++;
            }
        }
    }

    int answer = INT_MIN;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int diff = baseRow[i] - baseCol[j] + qRow[i] + qCol[j];
            if (table[i][j] == '?') diff -= 2;
            answer = max(answer, diff);
        }
    }

    cout << answer << "\n";
    return 0;
}
