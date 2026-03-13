#include <iostream>
#include <string>
using namespace std::string_literals;

auto main() -> int
{
    int troom, tcond;
    std::cin >> troom >> tcond;
    std::string str;
    std::cin >> str;
    int ans = 0;
    if (str == "auto"s)ans = tcond;
    else if (str == "fan"s) ans = troom;
    else if (str == "freeze"s) ans = troom > tcond ? tcond : troom;
    else ans = troom < tcond ? tcond : troom;
    std::cout << ans << '\n';
}
