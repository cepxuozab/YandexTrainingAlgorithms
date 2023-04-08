#include <charconv>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

int ToSecond(std::string_view time);

auto const START = ToSecond("09:00:00");
auto const LUNCH = ToSecond("13:00:00");
auto const LUNCH_END = ToSecond("14:00:00");
auto const END = ToSecond("18:00:00");

std::vector<int> ReadInput();

int Nails(std::vector<int> const& times_to_nail);

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }

    std::cout << Nails(ReadInput());
}

int ToSecond(std::string_view time)
{
    auto pos = time.find(':');
    int hour;
    [[maybe_unused]] auto m { std::from_chars(time.data(), time.data() + pos, hour) };
    time.remove_prefix(pos + 1);
    pos = time.find(':');
    int minutes;
    m = { std::from_chars(time.data(), time.data() + pos, minutes) };
    time.remove_prefix(pos + 1);
    int seconds;
    m = std::from_chars(time.data(), time.data() + time.size(), seconds);
    return seconds + 60 * minutes + 3600 * hour;
}

std::vector<int> ReadInput()
{
    struct Schedule {
        int time_s, nail_t;
    };

    int n;
    std::cin >> n;
    std::vector<Schedule> schedule;
    for (int i = 0; i < n; ++i) {
        std::string time;
        int nail_t;
        std::cin >> time >> nail_t;
        int time_s = ToSecond(time);
        schedule.push_back({ time_s, nail_t });
    }
    std::vector<int> times_to_nail(END);
    int j = 0;
    for (int i = 0; i < n; ++i) {
        int time_to_nail = schedule[i].nail_t;
        int show_end = i + 1 < n ? schedule[i + 1].time_s : END;
        while (j < show_end) {
            times_to_nail[j] = time_to_nail;
            j++;
        }
    }
    return times_to_nail;
}

int Nails(std::vector<int> const& times_to_nail)
{
    std::vector<int> dp(END + 1);
    for (int i = START; i != END; ++i) {
        dp[i + 1] = std::max(dp[i], dp[i + 1]);
        if (i >= LUNCH && i < LUNCH_END) {
            continue;
        }
        if (LUNCH > i && LUNCH < i + times_to_nail[i]) {
            continue;
        }
        if (i + times_to_nail[i] > END) {
            continue;
        }
        dp[i + times_to_nail[i]] = std::max(dp[i + times_to_nail[i]], dp[i] + 1);
    }
    return dp.back();
}
