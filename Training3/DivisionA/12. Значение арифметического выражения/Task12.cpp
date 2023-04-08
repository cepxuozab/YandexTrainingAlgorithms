#include <algorithm>
#include <cctype>
#include <charconv>
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

enum class lexeme_type { OPENING_PARENTHESIS,
    CLOSING_PARENTHESIS,
    INTEGER,
    MINUS,
    PLUS,
    TIMES,
    DIVIDED_BY };

struct lexeme {
    lexeme() = default;
    lexeme(int value, lexeme_type type)
        : value(value)
        , type(type)
    {
    }
    lexeme(lexeme_type type)
        : type(type)
    {
    }
    int value = 0;
    lexeme_type type;
};

void Print(lexeme const& lex)
{
    switch (lex.type) {
    case lexeme_type::OPENING_PARENTHESIS:
        std::cout << "(" << std::endl;
        break;
    case lexeme_type::CLOSING_PARENTHESIS:
        std::cout << ")" << std::endl;
        break;
    case lexeme_type::INTEGER:
        std::cout << lex.value << std::endl;
        break;

    case lexeme_type::MINUS:
        std::cout << "-" << std::endl;
        break;
    case lexeme_type::PLUS:
        std::cout << "+" << std::endl;
        break;
    case lexeme_type::TIMES:
        std::cout << "*" << std::endl;
        break;
    case lexeme_type::DIVIDED_BY:
        std::cout << "/" << std::endl;
        break;
    default:
        std::cout << "ERROR" << std::endl;
    }
}
auto lexer(std::string_view input)
{
    std::vector<lexeme> lexemes;
    const auto begin = input.data();
    const auto end = begin + input.size();
    for (auto it = begin; it != end;) {
        switch (*it) {
        case ' ':
            ++it;
            break;
        case '(':
            lexemes.emplace_back(lexeme_type::OPENING_PARENTHESIS);
            ++it;
            break;
        case ')':
            lexemes.emplace_back(lexeme_type::CLOSING_PARENTHESIS);
            ++it;
            break;
        case '+':
            lexemes.emplace_back(lexeme_type::PLUS);
            ++it;
            break;
        case '-':
            lexemes.emplace_back(lexeme_type::MINUS);
            ++it;
            break;
        case '*':
            lexemes.emplace_back(lexeme_type::TIMES);
            ++it;
            break;
        case '/':
            lexemes.emplace_back(lexeme_type::DIVIDED_BY);
            ++it;
            break;
        default:
            int result;
            auto [next, error_code] = std::from_chars(it, end, result);
            if (next == it)
                throw std::invalid_argument { "invalid lexeme!" };
            lexemes.emplace_back(result, lexeme_type::INTEGER);
            it = next;
        }
    }
    return lexemes;
}

/*

Grammar:

expression = product | product + product | product - product
product = atomic | atomic * atomic | atomic / atomic
atomic = digits | (expression)

*/

bool check_adjacent_int(std::vector<lexeme> const& lex)
{
    auto compare = [](lexeme const& lhs, lexeme const& rhs) { return lhs.type == lexeme_type::INTEGER
                                                                  && rhs.type == lexeme_type::INTEGER; };
    for (auto it = std::next(lex.begin()); it != lex.end(); ++it) {
        if (compare(*std::prev(it), *it)) {
            return true;
        }
    }
    return false;
}

auto infix_to_postfix(std::vector<lexeme> const& lex)
{
    std::vector<lexeme> postfix, stack;
    for (auto const& elem : lex) {
        if (elem.type == lexeme_type::INTEGER) {
            postfix.push_back(elem);
        } else if (elem.type == lexeme_type::OPENING_PARENTHESIS) {
            stack.push_back(elem);
        } else if (elem.type == lexeme_type::CLOSING_PARENTHESIS) {

            while (!stack.empty() && stack.back().type != lexeme_type::OPENING_PARENTHESIS) {
                postfix.push_back(stack.back());
                stack.pop_back();
            }
            if (stack.empty()) {
                throw std::invalid_argument { "empty expressions have no value" };
            }
            stack.pop_back();
        } else {
            while (!stack.empty() && elem.type <= stack.back().type) {
                postfix.push_back(stack.back());
                stack.pop_back();
            }
            stack.push_back(elem);
        }
    }
    while (!stack.empty()) {
        postfix.push_back(stack.back());
        if (postfix.back().type < lexeme_type::MINUS) {
            throw std::invalid_argument { "wrong  value" };
        }
        stack.pop_back();
    }
    return postfix;
}

int PostfixToInt(std::vector<lexeme> const& tokens)
{
    std::vector<lexeme> stack;
    int res = 0;
    for (auto const& token : tokens) {
        if (token.type == lexeme_type::INTEGER) {
            stack.push_back(token);
            continue;
        }
        if (stack.size() < 2) {
            throw std::invalid_argument{ "wrong  evaluate" };
        }
        lexeme first = stack.back();
        stack.pop_back();
        lexeme second = stack.back();
        stack.pop_back();

        switch (token.type) {
        case lexeme_type::PLUS:
            res = first.value + second.value;
            stack.push_back({ res, lexeme_type::INTEGER });
            break;
        case lexeme_type::MINUS:
            res = -first.value + second.value;
            stack.push_back({ res, lexeme_type::INTEGER });
            break;
        case lexeme_type::TIMES:
            res = first.value * second.value;
            stack.push_back({ res, lexeme_type::INTEGER });
            break;
        default:
            throw std::invalid_argument { "wrong  evaluate" };
        }
    }
    if(stack.size()!=1)            throw std::invalid_argument{ "wrong  evaluate" };

    return stack.back().value;
}
void PrintLexerArray(std::vector<lexeme> const& parser)
{
    for (auto const& lex : parser) {
        Print(lex);
    }
}
int main()
{
    freopen("input.txt", "r", stdin);
    std::string expression;
    getline(std::cin, expression);
    try {
        auto parser = lexer(expression);
        //if (check_adjacent_int(parser)) {
        //    std::cout << "WRONG" << std::endl;
        //    return 1;
        //}
        auto postfix = infix_to_postfix(parser);
       // PrintLexerArray(postfix);
        int ans = PostfixToInt(postfix);
        std::cout << ans << std::endl;
    } catch (std::invalid_argument const& ) {
        std::cout << "WRONG" << std::endl;
    }
}

// This code is contributed by Nikhil jindal.
