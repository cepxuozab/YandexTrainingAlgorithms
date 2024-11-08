#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <vector>

auto my_isdigit(char ch) -> bool;

auto Tokenize(std::string_view str) -> std::vector<std::string>;

auto ToPolishNotation(std::vector<std::string> const& tokens) -> std::vector<std::string>;

auto Calculate(std::vector<std::string> const& notation) -> std::optional<int>;

void Test();

auto main() -> int  // NOLINT
{
    Test();
    std::string expression;
    getline(std::cin, expression);
    auto ans = Calculate(ToPolishNotation(Tokenize(expression)));
    if (ans.has_value()) {
        std::cout << ans.value();
    } else {
        std::cout << "WRONG";
    }
}

auto my_isdigit(char ch) -> bool {
    return std::isdigit(static_cast<unsigned char>(ch));
}

auto Tokenize(std::string_view str) -> std::vector<std::string> {
    std::vector<std::string> tokens;
    if (str.empty()) {
        return {};
    }
    auto not_symbol = [](char ch) {
        return std::string_view{"1234567890+-*() "}.find(ch) == std::string_view::npos;
    };
    auto not_valid_token = [](std::string_view token) {
        return !std::set<std::string_view>{"(", "*", "-", "+"}.contains(token);
    };

    auto is_operation = [](std::string_view token) {
        return std::set<std::string_view>{"*", "-", "+"}.contains(token);
    };

    int brace_balance = 0;
    size_t i = 0;
    while (i < str.size()) {
        char ch = str[i];
        if (not_symbol(ch)) {
            return {};
        }
        switch (ch) {
            case ' ':
                i++;
                break;
            case '(':
                if (!tokens.empty() && not_valid_token(tokens.back())) {
                    return {};
                }
                brace_balance++;
                tokens.emplace_back(1, ch);
                i++;
                break;
            case ')':

                if (--brace_balance < 0) {
                    return {};
                }
                if (!not_valid_token(tokens.back())) {
                    return {};
                }
                tokens.emplace_back(1, ch);
                i++;
                break;
            case '+':
            case '-':
            case '*':
                if (!not_valid_token(tokens.back())) {
                    return {};
                }
                tokens.emplace_back(1, ch);
                i++;
                break;
            default:
                std::string num;
                while (i < str.size() && my_isdigit(str[i])) {
                    num.push_back(str[i]);
                    i++;
                }
                if (!num.empty()) {
                    if (!tokens.empty() && std::ranges::all_of(tokens.back(), my_isdigit)) {
                        return {};
                    }
                    if (!tokens.empty() && not_valid_token(tokens.back())) {
                        return {};
                    }
                    tokens.emplace_back(num);
                }
                break;
        }
    }

    if (brace_balance > 0) {
        return {};
    }

    if (!tokens.empty() && is_operation(tokens.back())) {
        return {};
    }

    return tokens;
}

auto ToPolishNotation(std::vector<std::string> const& tokens) -> std::vector<std::string> {
    if (tokens.empty()) {
        return {};
    }
    std::vector<std::string> stack;
    std::vector<std::string> notation;
    for (auto const& token : tokens) {
        if (std::ranges::all_of(token, my_isdigit)) {
            notation.push_back(token);
        }
        if (std::set<std::string>{"+", "-", "*"}.contains(token)) {
            if (token == "-" || token == "+") {
                while (!stack.empty() && stack.back() != "(") {
                    notation.push_back(stack.back());
                    stack.pop_back();
                }
                stack.push_back(token);
            } else {
                while (!stack.empty() && stack.back() == "*") {
                    notation.push_back(stack.back());
                    stack.pop_back();
                }
                stack.push_back(token);
            }
        }
        if (token == "(") {
            stack.push_back(token);
        }
        if (token == ")") {
            while (!stack.empty() && stack.back() != "(") {
                notation.push_back(stack.back());
                stack.pop_back();
            }

            if (!stack.empty()) stack.pop_back();
        }
    }
    notation.insert(notation.end(), stack.rbegin(), stack.rend());

    return notation;
}

auto Calculate(std::vector<std::string> const& notation) -> std::optional<int> {
    if (notation.empty()) {
        return std::nullopt;
    }
    std::map<std::string, std::function<int(int, int)>> ops{
        {"*", std::multiplies<>()}, {"-", std::minus<>()}, {"+", std::plus<>()}};
    std::vector<int> stack;
    for (std::string const& str : notation) {
        if (std::ranges::all_of(str, my_isdigit)) {
            stack.push_back(std::stoi(str));
        } else {
            auto x1 = stack.back();
            stack.pop_back();
            auto x2 = stack.back();
            stack.pop_back();
            stack.push_back(ops.at(str)(x2, x1));
        }
    }
    return stack.back();
}

void Test() {
    std::string a
        = "(1 + (7 + 8) - (3 - 4 * 5) * (2 * 4) + (9) - (16728) * (123 * 9 + 2) + ((2))) + ((((((0 "
          "- 19283))))))";
    assert(Calculate(ToPolishNotation(Tokenize(a))) == -18570472);
    assert(Calculate(ToPolishNotation(Tokenize("1 1 + 2"))) == std::nullopt);
    assert(Calculate(ToPolishNotation(Tokenize("1+a+1"))) == std::nullopt);
    assert(Calculate(ToPolishNotation(Tokenize("1+(2*2 - 3)"))) == 2);
    assert(Calculate(ToPolishNotation(Tokenize("1*2*3+(*4*5*6*7+8*9)"))) == std::nullopt);
}
