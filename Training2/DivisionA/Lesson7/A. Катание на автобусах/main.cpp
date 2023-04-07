#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct Person {
    // state == 0 -- waiting on the bus stop
    // state == 1 -- riding the bus
    // state == 2 -- getting off the bus
    // state == 3 -- finished
    int state = 0;
    vector<int> plan;
    size_t plan_idx = 0;
    int cur_stop;
    int cur_bus = -1;
    int time = 0;
};

struct Bus {
    vector<int> route;
    size_t route_idx = 0;
};

int main() {
    int n, k;
    cin >> n >> k;
    vector<Bus> buses(k);
    vector<set<int>> bus_stops(n);
    for (size_t i = 0; i < k; ++i) {
        int l;
        cin >> l;
        buses[i].route.resize(l);
        for (size_t j = 0; j < l; ++j) {
            int tmp;
            cin >> tmp;
            --tmp;
            buses[i].route[j] = tmp;
        }
        bus_stops[buses[i].route[0]].insert(i);
    }
    int p;
    cin >> p;
    vector<Person> persons(p);
    for (size_t i = 0; i < p; ++i) {
        int tmp;
        cin >> tmp;
        --tmp;
        persons[i].cur_stop = tmp;
        int m;
        cin >> m;
        persons[i].plan.resize(m);
        for (size_t j = 0; j < m; ++j) {
            cin >> persons[i].plan[j];
        }
    }

    vector<bool> is_dead_bus_stop(n, true);
    for (size_t i = 0; i < k; ++i) {
        auto& bus = buses[i];
        int cur_bus_stop = bus.route[bus.route_idx];
        while (true) {
            is_dead_bus_stop[bus.route[bus.route_idx]] = false;
            bus.route_idx = (bus.route_idx + 1) % bus.route.size();
            if (bus.route_idx == 0) {
                break;
            }
        }
    }

    int cur_time = 0;
    int cnt = 0;
    while (cnt != p) {
        // get on the bus
        for (size_t i = 0; i < p; ++i) {
            if (persons[i].state != 0) {
                continue;
            }
            int bus_stop = persons[i].cur_stop;
            if (is_dead_bus_stop[bus_stop]) {
                // he will never get on bus...
                // press F in the chat
                persons[i].cur_stop = -1;
                persons[i].time = 0;
                persons[i].state = 3;
                ++cnt;
            }
            if (!bus_stops[bus_stop].empty()) {
                int bus = *bus_stops[bus_stop].begin();
                persons[i].cur_bus = bus;
                persons[i].state = 1;
            }
        }
        // change state of persons who got off the bus
        for (size_t i = 0; i < p; ++i) {
            if (persons[i].state == 2) {
                persons[i].state = 0;
            }
        }

        ++cur_time;

        // ride the buses
        for (size_t i = 0; i < k; ++i) {
            auto& bus = buses[i];
            bus_stops[bus.route[bus.route_idx]].erase(i);
            bus.route_idx = (bus.route_idx + 1) % bus.route.size();
            bus_stops[bus.route[bus.route_idx]].insert(i);
        }
        for (size_t i = 0; i < p; ++i) {
            if (persons[i].state != 1) {
                continue;
            }
            auto& person = persons[i];
            --person.plan[person.plan_idx];
            auto& bus = buses[person.cur_bus];
            person.cur_stop = bus.route[bus.route_idx];
            if (person.plan[person.plan_idx] == 0) {
                // get off the bus
                person.state = 2;
                person.time = cur_time;
                ++person.plan_idx;
            }
            if (person.plan_idx >= person.plan.size()) {
                person.state = 3;
                ++cnt;
            }
        }
    }

    for (size_t i = 0; i < p; ++i) {
        auto& person = persons[i];
        cout << person.time << " " << person.cur_stop + 1 << endl;
    }

    return 0;
}