#include <cstdint>
#include <iostream>
#include <vector>

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<int> box_ar(n);
    for (int& a : box_ar) {
        std::cin >> a;
    }
    int const POW = 257;
    int const MOD = 1'000'000'007;
    int64_t box_pref = 0;
    std::vector<int64_t> box_hes_ar { 0 }, x_deg { 1 };
    size_t i = 0;
    for (auto& box : box_ar) {
        box_pref = (box_pref * POW + box + MOD) % MOD;
        box_hes_ar.push_back(box_pref);
        x_deg.push_back((x_deg[i] * POW + MOD) % MOD);
        i++;
    }
    std::vector<int> res_box_ar { n };
    int64_t left_box = 0;
    for (int j = 1; j <= n / 2; ++j) {
        left_box = (left_box + box_ar[j - 1] * x_deg[j - 1] + MOD) % MOD;
        if ((left_box + box_hes_ar[j] * x_deg[j]) % MOD == box_hes_ar[j + j] % MOD) {
            res_box_ar.push_back(n - j);
        }
    }
    for (auto it = res_box_ar.rbegin(); it != res_box_ar.rend(); ++it) {
        std::cout << *it << ' ';
    }
}
