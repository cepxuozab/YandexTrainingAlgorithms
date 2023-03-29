#include <iostream>
#include <set>
#include <string>
int main()
{
    std::string a, b;

    for (int i = 0, x; i < 3 && std::cin >> x; ++i) {
        a += x + '0';
    }
    std::cin >> b;
    std::set<char> s(b.begin(), b.end());
    int ans = 0;
    for (char ch : s) {
        ans += static_cast<int>(a.find(ch) == std::string::npos);
    }
    std::cout << ans;
}
