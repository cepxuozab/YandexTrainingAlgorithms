#include <iostream>
#include <tuple>

#include <algorithm>

#include <unordered_set>
#include <vector>

struct Date {
    int year;
    short month;
    short day;

    bool operator<(const Date& b) const
    {
        return std::tie(year, month, day) < std::tie(b.year, b.month, b.day);
    }
};

std::istream& operator>>(std::istream& in, Date& date)
{
    return in >> date.day >> date.month >> date.year;
}

struct Event {
    Date date;
    int number;
    enum Type { OUT = 0,
        IN = 1 } type;

    bool operator<(const Event& b) const
    {
        return std::pair(date, type) < std::pair(b.date, b.type);
    }
};

void printAllMaxGroups(const std::vector<Event>& events)
{
    if (events.size() == 0)
        std::cout << 0;
    else {
        std::unordered_set<int> group;

        bool isUpdated = false;
        for (auto& [date, number, eventType] : events) {
            if (eventType == Event::IN) {
                isUpdated = group.insert(number).second;
            } else // eventT == Event::OUT
            {
                if (isUpdated) {
                    for (auto number : group)
                        std::cout << number << ' ';
                    std::cout << std::endl;

                    isUpdated = false;
                }
                group.erase(number);
            }
        }
    }
}

int main()
{
    int N;
    std::cin >> N;

    std::vector<Event> events(2 * N);
    Date lowAge, highAge;
    int pos = 0;
    for (int i = 1; i <= N; i++) {
        std::cin >> lowAge >> highAge;

        lowAge.year += 18;
        if (lowAge < highAge) {
            events[pos++] = { lowAge, i, Event::IN };
            lowAge.year += 62;
            events[pos++] = { std::min(lowAge, highAge), i, Event::OUT };
        }
    }
    events.resize(pos);
    std::sort(events.begin(), events.end());

    printAllMaxGroups(events);

    return 0;
}
