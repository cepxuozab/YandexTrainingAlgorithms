#include <iostream>
#include <array>
#include <string>
#include <string_view>

auto solve(std::string_view s) -> std::string
{
    std::array<int, 10> cnt{};
    int sum = 0;

    for (char c : s)
    {
        int d = c - '0';
        cnt[d]++;
        sum += d;
    }

    const int mod = sum % 3;

    auto remove_one = [&](int r) -> bool
    {
        for (int d = 1; d <= 9; ++d)
        {
            if (d % 3 == r && cnt[d] > 0)
            {
                cnt[d]--;
                return true;
            }
        }
        return false;
    };

    auto remove_two = [&](int r) -> bool
    {
        int need = 2;
        for (int d = 1; d <= 9 && need > 0; ++d)
        {
            while (cnt[d] > 0 && d % 3 == r && need > 0)
            {
                cnt[d]--;
                need--;
            }
        }
        return need == 0;
    };

    if (mod == 1)
    {
        if (!remove_one(1))
        {
            remove_two(2);
        }
    }
    else if (mod == 2)
    {
        if (!remove_one(2))
        {
            remove_two(1);
        }
    }

    std::string result;
    result.reserve(s.size());

    for (int d = 9; d >= 0; --d)
    {
        for (int i = 0; i < cnt[d]; ++i)
        {
            result.push_back(static_cast<char>('0' + d));
        }
    }

    return result;
}

auto main() -> int
{
    std::string s;
    std::cin >> s;
    std::cout << solve(s);
}
