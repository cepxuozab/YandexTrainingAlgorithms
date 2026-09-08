#include <iostream>
#include <string>

int main() {
    std::string s, t;
    std::cin >> s >> t;

    int need[26] = {0};
    for (char c : t)
        need[c - 'a']++;

    int cur[26] = {0};
    long long ans = 0;
    int l = 0;
    int n = s.size();

    for (int r = 0; r < n; ++r) {
        cur[s[r] - 'a']++;
        while (cur[s[r] - 'a'] > need[s[r] - 'a']) {
            cur[s[l] - 'a']--;
            l++;
        }
        ans += (r - l + 1);
    }

    std::cout << ans;
    return 0;
}