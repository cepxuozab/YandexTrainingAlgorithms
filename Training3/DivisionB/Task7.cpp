#include <array>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>
#include <string_view>
static const auto FastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr; }();

int TimeInSecond(std::string_view str);

std::string AddSecond(std::string_view str, int delta);

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    std::string request, server, response;
    getline(std::cin, request);
    getline(std::cin, server);
    getline(std::cin, response);
    int requestInSecond = TimeInSecond(request);
    int responseInSecond = TimeInSecond(response);

    int delta = (requestInSecond < responseInSecond)
        ? (int)std::round((double)(responseInSecond - requestInSecond) / 2)
        : (int)std::round((double)(24 * 60 * 60 - requestInSecond + responseInSecond) / 2);

    std::cout << AddSecond(server, delta) << std::endl;
}

std::array<int, 3> StringToNums(std::string_view str)
{
    std::array<int, 3> times {};
    times[0] = (str[0] - '0') * 10 + (str[1] - '0');
    times[1] = (str[3] - '0') * 10 + (str[4] - '0');
    times[2] = (str[6] - '0') * 10 + (str[7] - '0');
    return times;
}
int TimeInSecond(std::string_view str)
{
    auto times = StringToNums(str);
    return 60 * 60 * times[0] + 60 * times[1] + times[2];
}

std::string LeadingZero(int n)
{
    if (n > 9) {
        return std::to_string(n);
    }
    std::string ans(1, '0');
    ans += (n + '0');
    return ans;
}

std::string AddSecond(std::string_view str, int delta)
{
    auto times = StringToNums(str);

    int hours = times[0];
    int minutes = times[1];
    int seconds = times[2];
    seconds += delta;
    if (seconds > 59) {
        minutes += seconds / 60;
        seconds %= 60;
        if (minutes > 59) {
            hours += minutes / 60;
            minutes %= 60;
        }
        if (hours > 23) {
            hours %= 24;
        }
    }
    return LeadingZero(hours) + ":" + LeadingZero(minutes) + ":" + LeadingZero(seconds);
}
