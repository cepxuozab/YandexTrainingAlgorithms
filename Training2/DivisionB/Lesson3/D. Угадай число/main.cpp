#include <algorithm>
#include <climits>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
int main()
{
    if (!freopen("input.txt", "r", stdin)) {
        throw std::invalid_argument("can't read");
    }
    int n;
    std::cin >> n;
    std::vector<int> numbers(n + 1);
    std::cin.ignore(INT_MAX, '\n');
    std::vector<int> arr;
    while (true) {
        std::string command;
        getline(std::cin, command);
        if (command == "HELP") {
            break;
        }
        std::istringstream in_a(command);
        for (int i; in_a >> i;) {
            arr.push_back(i);
        }
        std::string answer;
        getline(std::cin, answer);
        if (answer == "YES") {
            for (int i : arr) {
                if (numbers[i] != -1) {
                    numbers[i]++;
                }
            }
        } else {
            for (int i : arr) {
                numbers[i] = -1;
            }
        }
        arr.clear();
    }
    auto maxi = *std::max_element(numbers.begin(), numbers.end());

    for (size_t i = 1; i < numbers.size(); ++i) {
        if (numbers[i] == maxi) {
            std::cout << i << ' ';
        }
    }

    return 0;
}

/// 23 81 83
