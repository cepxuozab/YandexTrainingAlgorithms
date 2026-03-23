#include <iostream>
#include <string>
#include <algorithm>

auto max_length(std::string_view str) -> int
{
    int max_len = 0;
    int current_len = 0;
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (str[i] == 'a' || str[i] == 'h')
        {
            if (current_len == 0)
            {
                current_len = 1;
            }
            else
            {
                if (str[i] != str[i - 1])
                {
                    current_len++;
                }
                else
                {
                    max_len = std::max(max_len, current_len);
                    current_len = 1;
                }
            }
        }
        else
        {
            max_len = std::max(max_len, current_len);
            current_len = 0;
        }
    }
    return std::max(max_len, current_len);
}

auto main() -> int
{
    int n;
    std::string s;

    std::cin >> n >> s;

    std::cout << max_length(s) << '\n';

    return 0;
}
