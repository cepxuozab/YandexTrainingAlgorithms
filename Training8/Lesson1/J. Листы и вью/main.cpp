#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <sstream>

struct ListData {
    std::vector<int> values;
};

struct FigonList {
    std::shared_ptr<ListData> data;
    size_t offset;   // 0-based
    size_t length;   // number of elements in this view
    bool is_original;
};

std::unordered_map<std::string, FigonList> vars;

// Простой split по пробелам
std::vector<std::string> split(const std::string& s) {
    std::istringstream iss(s);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Извлечь числа из строки вида "List(1,2,3)" или "subList(1,4)"
std::vector<int> parseArgs(const std::string& expr) {
    size_t open = expr.find('(');
    size_t close = expr.rfind(')');
    std::string inner = expr.substr(open + 1, close - open - 1);

    std::vector<int> res;
    std::istringstream ss(inner);
    std::string num;
    while (std::getline(ss, num, ',')) {
        res.push_back(std::stoi(num));
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::cin.ignore();

    while (n--) {
        std::string line;
        std::getline(std::cin, line);
        auto tokens = split(line);

        if (tokens[0] == "List") {
            // List name = ...
            std::string name = tokens[1];

            if (tokens[3] == "new") {
                // List a = new List(1,2,3)
                auto nums = parseArgs(tokens[4]);
                auto data = std::make_shared<ListData>();
                data->values = std::move(nums);
                vars[name] = {data, 0, data->values.size(), true};
            } else {
                // List b = a.subList(1,4)
                std::string expr = tokens[3]; // "a.subList(1,4)"
                size_t dot = expr.find('.');
                std::string parentName = expr.substr(0, dot);
                auto args = parseArgs(expr.substr(dot + 1)); // "subList(1,4)"

                int from1 = args[0]; // 1-based
                int to1 = args[1];   // 1-based

                const auto& parent = vars[parentName];
                size_t from0 = parent.offset + (from1 - 1);
                size_t len = to1 - from1 + 1;

                vars[name] = {parent.data, from0, len, false};
            }
        } else {
            // x.method(...)
            std::string call = tokens[0];
            size_t dot = call.find('.');
            std::string name = call.substr(0, dot);
            size_t open = call.find('(');
            std::string method = call.substr(dot + 1, open - dot - 1);

            auto& list = vars[name];

            if (method == "get") {
                int i1 = std::stoi(call.substr(open + 1, call.size() - open - 2));
                size_t i0 = list.offset + (i1 - 1);
                std::cout << list.data->values[i0] << '\n';
            }
            else if (method == "set") {
                auto args = parseArgs(call);
                int i1 = args[0];
                int val = args[1];
                size_t i0 = list.offset + (i1 - 1);
                list.data->values[i0] = val;
            }
            else if (method == "add") {
                int val = std::stoi(call.substr(open + 1, call.size() - open - 2));
                // guaranteed: list.is_original == true
                list.data->values.push_back(val);
                list.length++;
            }
        }
    }

    return 0;
}