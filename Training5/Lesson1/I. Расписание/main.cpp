#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Schedule {
public:
    static void MakeSchedule();

private:
    static auto readHolidays(int n, int year) -> std::vector<tm>;
    static auto prepareWeekDayCounts(int year) -> std::map<int, int>;
    static void processHolidays(std::map<int, int>& weekDayCounts, const std::vector<tm>& holidays);
    static auto findMinMax(const std::map<int, int>& weekDayCounts) -> std::pair<int, int>;
};

auto main() -> int {
    Schedule::MakeSchedule();
}

static const std::map<std::string, int> monthStringToInt{
    {"January", 0},   {"February", 1}, {"March", 2},     {"April", 3},
    {"May", 4},       {"June", 5},     {"July", 6},      {"August", 7},
    {"September", 8}, {"October", 9},  {"November", 10}, {"December", 11}};
static const std::map<int, std::string> weekdayIntToString{
    {0, "Sunday"},   {1, "Monday"}, {2, "Tuesday"},  {3, "Wednesday"},
    {4, "Thursday"}, {5, "Friday"}, {6, "Saturday"},
};

auto Schedule::readHolidays(int n, int year) -> std::vector<tm> {
    std::vector<tm> holidays;
    for (int i = 0; i < n; ++i) {
        int day;
        std::string month;
        std::cin >> day >> month;
        tm holiday{};
        holiday.tm_year = year - 1900;
        holiday.tm_mon = monthStringToInt.at(month);
        holiday.tm_mday = day;
        mktime(&holiday);
        holidays.push_back(holiday);
    }
    return holidays;
}

auto Schedule::prepareWeekDayCounts(int year) -> std::map<int, int> {
    std::map<int, int> weekDayCounts;
    tm day{};
    day.tm_year = year - 1900;
    day.tm_mon = 0;
    day.tm_mday = 1;
    mktime(&day);
    while (day.tm_year == year - 1900) {
        weekDayCounts[day.tm_wday]++;
        day.tm_mday++;
        mktime(&day);
    }
    return weekDayCounts;
}

void Schedule::processHolidays(std::map<int, int>& weekDayCounts, const std::vector<tm>& holidays) {
    for (auto const& holyday : holidays) {
        weekDayCounts[holyday.tm_wday]--;
    }
}

auto Schedule::findMinMax(const std::map<int, int>& weekDayCounts) -> std::pair<int, int> {
    int maxIndex = 0;
    int max = weekDayCounts.at(maxIndex);

    int minIndex = 0;
    int min = weekDayCounts.at(minIndex);

    for (int i = 1; i < 7; ++i) {
        int value = weekDayCounts.at(i);
        if (value > max) {
            max = value;
            maxIndex = i;
        }
        if (value < min) {
            min = value;
            minIndex = i;
        }
    }
    return {minIndex, maxIndex};
}

void Schedule::MakeSchedule() {
    int n, year;
    std::cin >> n >> year;
    auto const holidays = readHolidays(n, year);

    std::string dayOfWeek;
    std::cin >> dayOfWeek;

    auto weekDayCounts = prepareWeekDayCounts(year);
    processHolidays(weekDayCounts, holidays);

    auto const [minIndex, maxIndex] = findMinMax(weekDayCounts);

    std::cout << weekdayIntToString.at(maxIndex) << " " << weekdayIntToString.at(minIndex);
}