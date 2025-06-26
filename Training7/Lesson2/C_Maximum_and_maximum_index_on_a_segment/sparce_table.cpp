#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Element {
    int value;
    int index;
};

class SparseTable {
private:
    vector<vector<Element>> table;
    vector<int> log_table;

public:
    SparseTable(const vector<int>& arr) {
        int n = arr.size();
        int max_log = 32 - __builtin_clz(n);
        table.resize(max_log, vector<Element>(n));

        for (int i = 0; i < n; ++i) {
            table[0][i] = {arr[i], i + 1}; // индексация с 1 в задаче
        }

        for (int j = 1; j < max_log; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                if (table[j-1][i].value > table[j-1][i + (1 << (j-1))].value) {
                    table[j][i] = table[j-1][i];
                } else {
                    table[j][i] = table[j-1][i + (1 << (j-1))];
                }
            }
        }

        log_table.resize(n + 1);
        log_table[1] = 0;
        for (int i = 2; i <= n; ++i) {
            log_table[i] = log_table[i/2] + 1;
        }
    }

    Element query(int l, int r) {
        l--; r--; // переводим в 0-индексацию
        int length = r - l + 1;
        int k = log_table[length];
        if (table[k][l].value > table[k][r - (1 << k) + 1].value) {
            return table[k][l];
        } else {
            return table[k][r - (1 << k) + 1];
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    SparseTable st(arr);

    int K;
    cin >> K;
    while (K--) {
        int l, r;
        cin >> l >> r;
        Element result = st.query(l, r);
        cout << result.value << ' ' << result.index << '\n';
    }

    return 0;
}