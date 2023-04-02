#include <iostream>
#include <string>

int main()
{
    std::string s;
    std::cin >> s;
    int cnt = 0;
    int const n = s.length();
    for (int i = 0; i < n / 2; i++) {
        cnt += static_cast<int>(s[i] != s[n - i - 1]);
    }
    printf("%d\n", cnt);
    return 0;
}
