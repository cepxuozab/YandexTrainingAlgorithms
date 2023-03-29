#include <algorithm>
#include <charconv>
#include <iostream>
#include <iterator>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <vector>

using namespace std::string_view_literals;

std::set<int> SplitSVPtr(std::string_view str, std::string_view delims);

int main()
{
    std::string one, two;
    getline(std::cin, one);
    getline(std::cin, two);
    auto const first_set = SplitSVPtr(one, " "sv);
    auto const second_set = SplitSVPtr(two, " "sv);
    std::ranges::copy_if(first_set, std::ostream_iterator<int>(std::cout, " "),
        [&](int i) { return second_set.contains(i); });
    return 0;
}

std::set<int> SplitSVPtr(std::string_view str, std::string_view delims)
{
    std::set<int> answer;
    for (auto first = str.data(), second = str.data(), last = first + str.size();
         second != last && first != last;
         first = second + 1) {
        second = std::find_first_of(first, last, std::cbegin(delims), std::cend(delims));

        if (first != second) {
            int result {};
            [[maybe_unused]] auto [ptr, ec] { std::from_chars(first, first + (second - first), result) };
            answer.insert(result);
        }
    }
    return answer;
}
