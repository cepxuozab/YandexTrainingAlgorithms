#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

enum class DIRECTION {
    N,
    S,
    W,
    E,
    U,
    D,
    LAST
};

DIRECTION char_to_cmd(char ch)
{
    switch (ch) {
    case 'N':
        return DIRECTION::N;
    case 'S':
        return DIRECTION::S;
    case 'W':
        return DIRECTION::W;
    case 'E':
        return DIRECTION::E;
    case 'U':
        return DIRECTION::U;
    default:
        return DIRECTION::D;
    }
}
int cmd_to_index(DIRECTION dir)
{
    return static_cast<int>(dir);
}

DIRECTION index_to_cmd(int idx)
{
    return static_cast<DIRECTION>(idx);
}

auto main() -> int
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    std::map<DIRECTION, std::string> commands;
    int nums = static_cast<int>(DIRECTION::LAST);
    for (int idx = 0; idx < nums; ++idx) {
        std::string command;
        getline(std::cin, command);
        commands[index_to_cmd(idx)] = command;
    }
    char command;
    int param;
    std::cin >> command >> param;
    std::vector<std::vector<int>> dp(nums, std::vector<int>(param + 1));
    for (auto& line : dp) {
        line[1] = 1;
    }
    for (int j = 2; j < param + 1; ++j) {
        for (int i = 0; i < nums; ++i) {
            dp[i][j] = 1;
            for (char cmd : commands[index_to_cmd(i)]) {
                dp[i][j] += dp[cmd_to_index(char_to_cmd(cmd))][j - 1];
            }
        }
    }
    std::cout << dp[cmd_to_index(char_to_cmd(command))][param];
    return 0;
}
