#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

bool substring_eq(const vector<uint64_t>& p_pow, const vector<uint64_t>& h,
    size_t i1, size_t i2, size_t len)
{
    uint64_t h1 = h[i1 + len - 1];
    if (i1)
        h1 -= h[i1 - 1];
    uint64_t h2 = h[i2 + len - 1];
    if (i2)
        h2 -= h[i2 - 1];

    return (i1 < i2 && (h1 * p_pow[i2 - i1]) == h2) || (i1 > i2 && h1 == (h2 * p_pow[i1 - i2]));
}

void compute_hashes(const string& s, vector<uint64_t>& p_pow, vector<uint64_t>& h)
{
    const int p = 191;
    p_pow[0] = 1;
    for (size_t i = 1; i < p_pow.size(); ++i) {
        p_pow[i] = p_pow[i - 1] * p;
    }

    for (size_t i = 0; i < s.length(); ++i) {
        h[i] = (s[i] - 'A' + 1) * p_pow[i];
        if (i)
            h[i] += h[i - 1];
    }
}

size_t solve(const string& s)
{
    vector<uint64_t> p_pow(s.length()), hashes(s.length());

    compute_hashes(s, p_pow, hashes);

    size_t cycle_len = s.length();
    for (size_t k = 1; k < s.length(); ++k) {
        if (substring_eq(p_pow, hashes, 0, k, s.length() - k)) {
            cycle_len = k;
            break;
        }
    }
    return cycle_len;
}

int main()
{
    // test();

    string input;
    cin >> input;
    cout << solve(input) << std::endl;
    return 0;
}
