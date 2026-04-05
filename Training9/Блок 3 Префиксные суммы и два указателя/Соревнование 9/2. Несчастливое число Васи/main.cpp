#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>


auto solve(const std::vector<long long>& a, long long K) -> long long {
    int n = static_cast<int>(a.size());

    // Sum of [L..R] = prefix[R+1] - prefix[L].
    // Want max(prefix[j] - prefix[i]), i < j, prefix[j]%K != prefix[i]%K.
    //
    // For each j we need the minimum prefix[i] (i < j) whose remainder != prefix[j]%K.
    // We track the two globally-smallest prefix values seen so far, ensuring they
    // come from DIFFERENT remainder classes, so for any remJ at least one of them
    // has remainder != remJ.

    auto mod = [&](long long x) -> long long {
        return ((x % K) + K) % K;
    };

    // min1: smallest prefix value seen; min1Rem: its remainder class
    // min2: smallest prefix value seen with a DIFFERENT remainder than min1
    long long min1Val = LLONG_MAX, min1Rem = -1;
    long long min2Val = LLONG_MAX; // remainder != min1Rem (when set)

    auto updateMins = [&](long long val, long long rem) -> void {
        if (min1Val == LLONG_MAX) {
            // First entry
            min1Val = val; min1Rem = rem;
            return;
        }
        if (rem == min1Rem) {
            // Same remainder class as current min1
            if (val < min1Val) min1Val = val;
            return;
        }
        // Different remainder class from min1
        if (val <= min1Val) {
            // New global min; old min1 competes for min2
            if (min2Val == LLONG_MAX || min1Val < min2Val)
                min2Val = min1Val;
            min1Val = val; min1Rem = rem;
        } else {
            // val > min1Val, goes into the "other remainder" bucket
            if (min2Val == LLONG_MAX || val < min2Val)
                min2Val = val;
        }
    };

    // Seed with prefix[0] = 0
    long long prefix = 0;
    updateMins(prefix, mod(prefix));

    long long ans = 0;

    for (int idx = 0; idx < n; ++idx) {
        prefix += a[idx];
        long long remJ = mod(prefix);

        // Best (smallest) prior prefix with remainder != remJ
        long long bestPrior = LLONG_MAX;
        if (min1Val != LLONG_MAX && min1Rem != remJ)
            bestPrior = min1Val;
        else if (min2Val != LLONG_MAX)
            bestPrior = min2Val;

        if (bestPrior != LLONG_MAX) {
            long long candidate = prefix - bestPrior;
            if (candidate > 0)
                ans = std::max(ans, candidate);
        }

        updateMins(prefix, remJ);
    }

    return ans;
}

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long N, K;
    std::cin >> N >> K;



    std::vector<long long> a(N);
    for (long long i = 0; i < N; ++i)
        std::cin >> a[i];

    std::cout << solve(a, K) << '\n';
    return 0;
}