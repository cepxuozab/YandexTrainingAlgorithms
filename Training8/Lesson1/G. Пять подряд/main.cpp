#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    // Направления: (di, dj)
    // →, ↓, ↘, ↙
    const int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c = grid[i][j];
            if (c == '.') continue;

            for (auto const& [di, dj] : directions) {
                // Проверим, хватает ли места для 5 клеток
                int end_i = i + 4 * di;
                int end_j = j + 4 * dj;
                if (end_i < 0 || end_i >= n || end_j < 0 || end_j >= m) {
                    continue;
                }

                // Проверим, все ли 5 клеток равны c
                bool ok = true;
                for (int k = 1; k < 5; k++) {
                    if (grid[i + k * di][j + k * dj] != c) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    cout << "Yes\n";
                    return 0;
                }
            }
        }
    }

    cout << "No\n";
    return 0;
}