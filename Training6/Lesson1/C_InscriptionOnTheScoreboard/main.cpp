#include <algorithm>
#include <utility>
#include <deque>
#include <iostream>
#include <map>
#include <string>

using namespace std::literals;

auto main() -> int {  // NOLINT
    int n;
    std::cin >> n;
    std::deque<std::string> lines(n);
    for (auto& line : lines) {
        std::cin >> line;
    }
    auto it_unique = std::unique(lines.begin(), lines.end());
    lines.erase(it_unique, lines.end());

    int64_t i = 0;
    while (std::cmp_less(i + 1, lines.front().size())) {
        std::string lhs, rhs;
        for (auto& line : lines) {
            lhs += line[i];
            rhs += line[i + 1];
        }

        if (lhs == rhs) {
            for (auto& str : lines) {
                str.erase(str.begin() + i);
            }
        } else {
            i += 1;
        }
    }
    while (!lines.empty() && std::all_of(lines.front().begin(), lines.front().end(), [](char ch) {
        return ch == '.';
    })) {
        lines.pop_front();
    }
    while (!lines.empty() && std::all_of(lines.back().begin(), lines.back().end(), [](char ch) {
        return ch == '.';
    })) {
        lines.pop_back();
    }

    while (!lines.empty() && !lines.front().empty()
           && std::all_of(lines.begin(), lines.end(), [](std::string str) {
                  return str.front() == '.';
              })) {
        for (auto& str : lines) {
            str = str.substr(1);
        }
    }
    while (!lines.empty() && !lines.back().empty()
           && std::all_of(lines.begin(), lines.end(), [](std::string str) {
                  return str.back() == '.';
              })) {
        for (auto& str : lines) {
            str.pop_back();
        }
    }
    std::deque<std::string> I{"#"s};
    std::deque<std::string> O{"###"s, "#.#"s, "###"s};
    std::deque<std::string> C{"##"s, "#."s, "##"s};
    std::deque<std::string> L{"#."s, "##"s};
    std::deque<std::string> H{"#.#"s, "###"s, "#.#"s};
    std::deque<std::string> P{"###"s, "#.#"s, "###"s, "#.."s};
    std::map<std::deque<std::string>, std::string> letters{{I, "I"s}, {O, "O"s}, {C, "C"s},
                                                           {L, "L"s}, {H, "H"s}, {P, "P"s}};
    if (auto it = letters.find(lines); it != letters.end()) {
        std::cout << it->second;
    } else {
        std::cout << "X"s;
    }
}
