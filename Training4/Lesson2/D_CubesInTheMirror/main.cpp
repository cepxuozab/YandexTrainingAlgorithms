#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
vector<int> Z_function(const vector<int>& s)
{
    size_t n = s.size();
    vector<int> z(s.size());
    for (int i = 1, l = 0, r = 0; i < s.size(); i++) {
        if (r >= i) {
            z[i] = min(z[i - l], r - i + 1);
        }
        while (z[i] + i < n && s[z[i]] == s[z[i] + i]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i, r = i + z[i] - 1;
        }
    }
    return z;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(2 * n + 1, -1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[2 * n - i] = a[i];
    }
    vector<int> z = Z_function(a);
    for (int i = n + 1; i < z.size(); i++) {
        if (z[i] % 2 == 0 && i + z[i] == a.size()) {
            cout << n - z[i] / 2 << " ";
        }
    }
    cout << n;
    return 0;
}
