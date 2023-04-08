#include <fstream>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

int main()
{
    std::vector<std::pair<int, int>> cities;

    std::fstream file;
    file.open("input.txt");

    int citiesCount;
    file >> citiesCount;

    for (int i = 0; i != citiesCount; i++) {
        int input;
        file >> input;
        cities.push_back({ input, i });
    }

    std::vector<int> moving;
    std::vector<int> result(citiesCount, -1);

    for (const auto& pair : cities) {
        while (!moving.empty() && (cities[moving.back()].first > pair.first)) {
            result[moving.back()] = pair.second;
            moving.pop_back();
        }
        moving.push_back(pair.second);
    }

    for (auto elem : result) {
        std::cout << elem << " ";
    }

    return 0;
}
