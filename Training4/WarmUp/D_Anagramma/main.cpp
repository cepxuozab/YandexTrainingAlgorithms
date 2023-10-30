#include <array>
#include <iostream>
#include <string>

int main()
{
    std::string s, s1;
    std::cin >> s >> s1;
    std::array<int, 26> arr {};
    for (char ch : s) {
        arr[ch - 'a']++;
    }
    for (char ch : s1) {
        arr[ch - 'a']--;
    }
    for (int i : arr) {
        if (i != 0) {
            puts("NO");
            return 0;
        }
    }
    puts("YES");
    return 0;
}
