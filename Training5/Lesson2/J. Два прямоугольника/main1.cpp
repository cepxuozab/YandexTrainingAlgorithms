#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <utility>
#include <string_view>
#include <algorithm>

auto FindFirstPoint(std::vector<std::string> const &art) -> std::optional<std::pair<int, int>> {
    for (int row = 0; std::cmp_less(row, art.size()); ++row) {
        auto col = art[row].find('#');
        if (col != std::string::npos) {
            return std::pair{row, static_cast<int>(col)};
        }
    }
    return std::nullopt;
}

auto CheckLine(int start, int end, std::string_view line) -> bool {
    bool has_left = line.substr(0, start).find('#') != std::string_view::npos;
    bool has_right = line.substr(end + 1).find('#') != std::string_view::npos;
    line.remove_suffix(line.size() - (end + 1));
    line.remove_prefix(start);
    if (!std::all_of(line.begin(), line.end(), [](char ch) { return ch == '#'; })) {
        return false;
    }

    if (has_right)return !has_left;
    return true;
}

auto FindSecondPoint(std::vector<std::string> const &art, std::pair<int, int> start) {
    auto [row, col] = start;
    int m = static_cast<int>(art.size());
    int n = static_cast<int>(art.front().size());
    while (col < n && art[row][col] == '#') {
        col += 1;
    }
    col -= 1;
    row += 1;
    while (row < m && CheckLine(start.second, col, art[row])) {
        row += 1;
    }
    row -= 1;
    return std::pair{row, col};
}

void Fill(std::vector<std::string> &art, std::pair<int, int> p1, std::pair<int, int> p2, char mark) {
    for (int row = p1.first; row < p2.first + 1; ++row) {
        for (int col = p1.second; col < p2.second + 1; ++col) {
            art[row][col] = mark;
        }
    }
}

auto CheckArt(std::vector<std::string> &art) -> bool {
    auto p1 = FindFirstPoint(art);
    if (!p1.has_value()) {
        return false;
    }
    auto p2 = FindSecondPoint(art, p1.value());
    Fill(art, p1.value(), p2, 'a');
    auto p3 = FindFirstPoint(art);
    if (!p3.has_value()) {
        if (p1.value() == p2) {
            return false;
        }
        auto tmp=std::pair{p1.value().first, p2.second};
        if(p1.value().first == p2.first){
            tmp={p2.first, p1.value().second};
        }
        Fill(art, p1.value(), tmp, 'b');
        return true;
    }
    auto p4 = FindSecondPoint(art, p3.value());
    Fill(art, p3.value(), p4, 'b');
    return !FindFirstPoint(art).has_value();
}

auto main() -> int {
    int m, n;
    std::cin >> m >> n;
    std::vector<std::string> art(m);
    for (auto &line: art)std::cin >> line;
    if (CheckArt(art)) {
        std::cout << "YES" << '\n';
        for (auto &str: art) {
            std::cout << str << '\n';
        }
    } else {
        std::cout << "NO" << '\n';
    }
}