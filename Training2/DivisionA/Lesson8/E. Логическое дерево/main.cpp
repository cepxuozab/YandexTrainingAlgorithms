#include <iostream>
#include <vector>

using namespace std;

int calculate_vals(vector<int>& ops, vector<int>& vals, size_t i) {
    if (i < ops.size()) {
        int left = calculate_vals(ops, vals, ((i + 1) << 1) - 1);
        int right = calculate_vals(ops, vals, (i + 1) << 1);
        vals[i] = ops[i] == 1 ? left && right : left || right;
    }
    return vals[i];
}

int change(vector<int>& ops, vector<int>& vals, vector<int>& c, size_t i,
    int nu) {
    if (i >= ops.size()) {
        return nu == vals[i] ? 0 : 10000;
    }
    if (nu == vals[i]) {
        return 0;
    }
    if (nu == ops[i] && c[i] == 1) {
        ops[i] = 1 - ops[i];
        calculate_vals(ops, vals, i);
        return 1 + change(ops, vals, c, i, nu);
    }
    return nu == ops[i] ? change(ops, vals, c, ((i + 1) << 1) - 1, nu) +
        change(ops, vals, c, (i + 1) << 1, nu)
        : min(change(ops, vals, c, ((i + 1) << 1) - 1, nu),
            change(ops, vals, c, (i + 1) << 1, nu));
}

int main() {
    int n, nu;
    cin >> n >> nu;
    vector<int> ops((n - 1) / 2);
    vector<int> c((n - 1) / 2);
    vector<int> vals(n, -1);
    for (size_t i = 0; i < n; ++i) {
        if (i < (n - 1) / 2) {
            cin >> ops[i] >> c[i];
        }
        else {
            cin >> vals[i];
        }
    }

    calculate_vals(ops, vals, 0);
    int res = change(ops, vals, c, 0, nu);
    calculate_vals(ops, vals, 0);
    if (vals[0] != nu) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    cout << res << endl;

    return 0;
}