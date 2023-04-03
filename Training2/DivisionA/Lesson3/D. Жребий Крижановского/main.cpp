#include <iostream>
#include <set>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<short> scores(n), nums(n - 1);
    for (auto& i : scores) {
        std::cin >> i;
    }
    for (auto& i : nums) {
        std::cin >> i;
    }
    std::set<short> used, used_twise;
    for (short num : nums) {
        if (!used.insert(num).second) {
            used_twise.insert(num);
        }
    }
    nums.emplace_back();
    short bestloser = -1;
    short bestnum = -1;
    for (short petyanum = 1; petyanum < 102; ++petyanum) {
        auto newscores(scores);
        auto newused(used);
        auto newusedtwise(used_twise);
        nums.back() = petyanum;
        if (newused.contains(petyanum)) {
            newusedtwise.insert(petyanum);
        }
        newused.insert(petyanum);
        short win = 102;
        for (short now = 101; now >= 0; --now) {
            if (newused.contains(now) && !newusedtwise.contains(now)) {
                win = now;
            }
        }
        for (size_t i = 0; i < nums.size(); ++i) {
            if (nums[i] == win) {
                newscores[i] += win;
            }
        }
        short nowloser = 0;
        for (size_t i = nums.size(); i-- > 0;) {
            if (newscores[i] < newscores.back()) {
                nowloser++;
            }
        }
        if (nowloser > bestloser) {
            bestloser = nowloser;
            bestnum = petyanum;
        }
    }
    std::cout << bestnum << '\n';
}
