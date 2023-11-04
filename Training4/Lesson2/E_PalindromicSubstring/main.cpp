#include <iostream>
#include <string>
#include <string_view>

size_t countSubstrings(std::string_view s)
{
    size_t ans = 0;
    for (int center = 0; center <= s.size() * 2 - 1; ++center) {
        int left = center / 2;
        int right = left + center % 2;
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            ++ans;
            --left;
            ++right;
        }
    }
    return ans;
}

int main()
{
    std::string str;
    std::cin >> str;
    std::cout << countSubstrings(str);
}
