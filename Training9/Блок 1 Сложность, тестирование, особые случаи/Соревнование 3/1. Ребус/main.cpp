#include <iostream>
#include <string>
#include <ranges>

using namespace std::literals;

auto main() -> int
{
    std::string str;
    getline(std::cin, str);
    auto words = std::views::split(str, " "sv);
    std::string ans;
    for (auto&& s : words)
    {
        std::string_view tmp(s.data(), s.size());
        size_t cnt = 0;

        while (!tmp.empty() && tmp.starts_with('\''))
        {
            tmp.remove_prefix(1);
            cnt++;
        }
        tmp.remove_prefix(cnt);
        cnt = 0;
        while (!tmp.empty() && tmp.ends_with('\''))
        {
            tmp.remove_suffix(1);
            cnt++;
        }
        tmp.remove_suffix(cnt);
        ans += std::string(tmp);
    }
    std::cout << ans;
}
