#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

auto main() -> int {
    int n;
    std::cin >> n;
    int k;
    std::cin >> k;
    std::vector<std::string> songs(k);
    for (auto &song: songs) {
        std::cin >> song;
    }
    std::ranges::sort(songs);
    for (int i = 1; i < n; ++i) {
        int m;
        std::cin >> m;
        std::set<std::string> curr;
        for (int j = 0; j < m; ++j) {
            std::string str;
            std::cin >> str;
            curr.insert(str);
        }
        std::vector<std::string> tmp;
        std::ranges::set_intersection(songs, curr, std::back_inserter(tmp));
        songs.swap(tmp);
    }
    std::cout << songs.size() << '\n';
    for (auto const &song: songs) {
        std::cout << song << ' ';
    }
}