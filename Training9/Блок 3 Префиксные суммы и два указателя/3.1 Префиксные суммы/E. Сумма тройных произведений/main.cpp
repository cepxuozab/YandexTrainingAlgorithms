#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;

auto main() -> int {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] %= MOD;
    }

    // Calculate prefix sums of a[i]
    vector<long long> prefix(n);
    prefix[0] = a[0];
    for (int i = 1; i < n; i++) {
        prefix[i] = (prefix[i-1] + a[i]) % MOD;
    }

    // Calculate prefix sums of a[i] * prefix[i-1] (sum of products of pairs ending at i)
    // Actually we need: for each j, sum_{i<j} a[i] * sum_{k>j} a[k]
    // = sum_{i<j} a[i] * (total_sum - prefix[j]) where total_sum is sum of all elements

    long long total_sum = prefix[n-1];

    long long result = 0;
    for (int j = 1; j < n-1; j++) {
        // Sum of elements before j
        long long left_sum = prefix[j-1];

        // Sum of elements after j
        long long right_sum = (total_sum - prefix[j] + MOD) % MOD;

        // Contribution of all triples where j is the middle element
        long long contribution = (a[j] * ((left_sum * right_sum) % MOD)) % MOD;
        result = (result + contribution) % MOD;
    }

    cout << result << '\n';

    return 0;
}