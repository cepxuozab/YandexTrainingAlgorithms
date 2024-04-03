#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator>


auto Split(std::string const &str) -> std::vector<std::string> {
    std::stringstream in(str);
    return {std::istream_iterator<std::string>(in), {}};
}


auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string dict, text;
    getline(std::cin, dict);
    getline(std::cin, text);
    auto dict_arr = Split(dict);
    auto text_arr = Split(text);
    std::ranges::sort(dict_arr);
    std::vector<std::string> answer;
    for (auto &str: text_arr) {
        auto compare = [&str](std::string const &prefix) { return str.starts_with(prefix); };
        auto it = std::find_if(dict_arr.begin(), dict_arr.end(), compare);
        if (it != dict_arr.end()) {
            answer.push_back(*it);
        } else {
            answer.push_back(str);
        }
    }
    for (auto &str: answer) {
        std::cout << str << ' ';
    }
}


