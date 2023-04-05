#include <algorithm>
#include <array>
#include <iostream>
#include <string>

int main()
{
    if (!freopen("input.txt", "r", stdin)) {
        throw std::invalid_argument("can't read");
    }
    std::string a, b;
    std::cin >> a >> b;
    std::array<int, 10> a_arr{}, b_arr{};
    for (char ch : a) {
        a_arr[ch - '0']++;
    }
    for (char ch : b) {
        b_arr[ch - '0']++;
    }
    std::string num{ "9876543210" };
    std::string ans;
    for (char ch : num) {
        int mini = std::min(a_arr[ch - '0'], b_arr[ch - '0']);
        if (mini != 0) {
            ans += std::string(mini, ch);
        }
    }

    if (ans.empty()) {
        std::cout << "-1\n";
    }
    else if (ans.front() == '0') {
        std::cout << "0\n";
    }
    else {
        std::cout << ans << '\n';
    }
    return 0;
}
