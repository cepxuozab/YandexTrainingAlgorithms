#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <set>
#include <vector>
using Event = std::pair<double, int>;

enum class EVENT {
    IN,
    OUT
};

double thickness;

using Events = std::tuple<double, EVENT, int>;

std::vector<Events> ReadData(unsigned n);

double CrossingArea(std::vector<Events>& events, unsigned n);

int main()
{
    freopen("input.txt", "r", stdin);
    unsigned n;
    std::cin >> n;
    auto events = ReadData(n);
    if (events.empty()) {
        std::cout << 0 << '\n';
    }
    else {
        std::cout << std::setprecision(9) << std::fixed << CrossingArea(events, n) << '\n';
    }
}

std::vector<Events> ReadData(unsigned n)
{
    double rmin = -1;
    double rmax = 1e7;
    std::vector<Events> events;
    for (int i = 1; i <= n; ++i) {
        double r1, r2, f1, f2;
        std::cin >> r1 >> r2 >> f1 >> f2;
        rmin = rmin > r1 ? rmin : r1;
        rmax = rmax < r2 ? rmax : r2;
        events.emplace_back(f1, EVENT::IN, i);
        events.emplace_back(f2, EVENT::OUT, i);
    }
    if (rmin >= rmax) {
        return {};
    }
    thickness = (std::pow(rmax, 2) - std::pow(rmin, 2)) / 2.0;
    std::sort(events.begin(), events.end());
    return events;
}

double CrossingArea(std::vector<Events>& events, unsigned n)
{
    std::set<int> sets;
    for (auto const& [x, ev, idx] : events) {
        ev == EVENT::IN ? sets.merge(std::set{ idx }) : (void)sets.erase(idx);
    }
    events.emplace_back(2 * std::numbers::pi, EVENT::OUT, -1);
    int cnt = (int)sets.size();
    double phi_sum = 0;
    double last_phi = 0;
    for (auto const& [phi, ev, idx] : events) {
        switch (ev) {
        case EVENT::IN:
            last_phi = phi;
            cnt++;
            break;
        case EVENT::OUT:
            phi_sum += (cnt == n ? phi - last_phi : 0);
            cnt--;
            break;
        default:
            break;
        }
    }
    return phi_sum * thickness;
}
