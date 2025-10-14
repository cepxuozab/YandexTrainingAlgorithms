#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;

    int len = n / m;

    unordered_map<string, queue<int>> piece_indices;
    for (int i = 0; i < m; i++) {
        string piece;
        cin >> piece;
        piece_indices[piece].push(i + 1); // индексы с 1
    }

    vector<int> result;
    for (int i = 0; i < m; i++) {
        string block = s.substr(i * len, len);
        int idx = piece_indices[block].front();
        piece_indices[block].pop();
        result.push_back(idx);
    }

    for (int i = 0; i < m; i++) {
        cout << result[i] << " ";
    }
    cout << '\n';

    return 0;
}