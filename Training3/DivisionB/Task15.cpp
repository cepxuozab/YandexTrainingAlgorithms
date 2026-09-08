#include <iostream>
#include <stack>
#include <vector>


struct City {
    int accommodation_price{};
    int id{};
};

auto main() -> int {
    std::vector<City> cities;
    int city_count{};
    std::cin >> city_count;
    for (int i = 0; i < city_count; ++i) {
        City city;
        std::cin >> city.accommodation_price;
        city.id = i;
        cities.push_back(city);
    }
    std::stack<int> moving;
    std::vector<int> result(cities.size(), -1);
    for (auto const &[price, id] : cities) {
        while (!moving.empty() &&
               cities[moving.top()].accommodation_price > price) {
            result[moving.top()] = id;
            moving.pop();
        }
        moving.push(id);
    }
    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i] << " ";
    }
    return 0;
}