#include <cctype>
#include <charconv>
#include <expected>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace {
enum class lexeme_type : char {
    OPENING_PARENTHESIS,
    CLOSING_PARENTHESIS,
    INTEGER,
    MINUS,
    PLUS,
    TIMES
};

struct lexeme {
    lexeme() = default;
    lexeme(long long value, lexeme_type type)
        : value(value)
        , type(type) {
    }

    explicit lexeme(lexeme_type type)
        : type(type) {
    }
    long long value = 0;
    lexeme_type type;
};

enum class parse_error : char {
    invalid_character,
    invalid_number,
    number_out_of_range,
    invalid_unary_position,
    mismatched_parentheses,
    malformed_expression
};

constexpr auto is_binary_operator(lexeme_type t) noexcept -> bool {
    return t == lexeme_type::PLUS || t == lexeme_type::MINUS || t == lexeme_type::TIMES;
}

constexpr auto precedence(lexeme_type t) noexcept -> int {
    switch (t) {
        case lexeme_type::PLUS:
        case lexeme_type::MINUS:
            return 1;
        case lexeme_type::TIMES:
            return 2;
        default:
            return 0;
    }
}

// Сырая токенизация: числа через std::from_chars, операторы и скобки как есть.
// Унарные +/- на этом этапе ещё не различаются от бинарных.
auto tokenize(std::string_view input) -> std::expected<std::vector<lexeme>, parse_error> {
    std::vector<lexeme> tokens;
    const char* it = input.data();
    const char* end = it + input.size();

    while (it != end) {
        char const c = *it;
        switch (c) {
            case ' ':
                ++it;
                continue;
            case '(':
                tokens.emplace_back(lexeme_type::OPENING_PARENTHESIS);
                ++it;
                continue;
            case ')':
                tokens.emplace_back(lexeme_type::CLOSING_PARENTHESIS);
                ++it;
                continue;
            case '+':
                tokens.emplace_back(lexeme_type::PLUS);
                ++it;
                continue;
            case '-':
                tokens.emplace_back(lexeme_type::MINUS);
                ++it;
                continue;
            case '*':
                tokens.emplace_back(lexeme_type::TIMES);
                ++it;
                continue;
            default:
                break;
        }

        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return std::unexpected(parse_error::invalid_character);
        }

        long long value = 0;
        auto const [next, ec] = std::from_chars(it, end, value);
        if (ec == std::errc::result_out_of_range) {
            return std::unexpected(parse_error::number_out_of_range);
        }
        if (ec != std::errc{} || next == it) {
            return std::unexpected(parse_error::invalid_number);
        }
        tokens.emplace_back(value, lexeme_type::INTEGER);
        it = next;
    }
    return tokens;
}

// Логика из normalize_expression: унарный +/- разрешён только в начале
// выражения или сразу после '('; после другого оператора — ошибка.
auto resolve_unary_operators(std::vector<lexeme> const& tokens)
    -> std::expected<std::vector<lexeme>, parse_error> {
    std::vector<lexeme> result;
    result.reserve(tokens.size() + 4);
    std::optional<lexeme_type> previous;

    for (auto const& token : tokens) {
        bool const is_sign = token.type == lexeme_type::PLUS || token.type == lexeme_type::MINUS;
        bool const at_operand_start = !previous.has_value()
            || *previous == lexeme_type::OPENING_PARENTHESIS || is_binary_operator(*previous);

        if (is_sign && at_operand_start) {
            if (previous.has_value() && *previous != lexeme_type::OPENING_PARENTHESIS) {
                return std::unexpected(parse_error::invalid_unary_position);  // напр. "3+-4"
            }
            result.emplace_back(0LL, lexeme_type::INTEGER);
        }
        result.push_back(token);
        previous = token.type;
    }
    return result;
}

// Алгоритм сортировочной станции.
auto infix_to_postfix(std::vector<lexeme> const& tokens)
    -> std::expected<std::vector<lexeme>, parse_error> {
    std::vector<lexeme> postfix;
    std::vector<lexeme> operators;

    for (auto const& token : tokens) {
        switch (token.type) {
            case lexeme_type::INTEGER:
                postfix.push_back(token);
                break;
            case lexeme_type::OPENING_PARENTHESIS:
                operators.push_back(token);
                break;
            case lexeme_type::CLOSING_PARENTHESIS:
                while (!operators.empty()
                       && operators.back().type != lexeme_type::OPENING_PARENTHESIS) {
                    postfix.push_back(operators.back());
                    operators.pop_back();
                }
                if (operators.empty()) {
                    return std::unexpected(parse_error::mismatched_parentheses);
                }
                operators.pop_back();  // выбросить '('
                break;
            default:  // PLUS, MINUS, TIMES
                while (!operators.empty()
                       && operators.back().type != lexeme_type::OPENING_PARENTHESIS
                       && precedence(token.type) <= precedence(operators.back().type)) {
                    postfix.push_back(operators.back());
                    operators.pop_back();
                }
                operators.push_back(token);
        }
    }

    while (!operators.empty()) {
        if (operators.back().type == lexeme_type::OPENING_PARENTHESIS) {
            return std::unexpected(parse_error::mismatched_parentheses);
        }
        postfix.push_back(operators.back());
        operators.pop_back();
    }
    return postfix;
}

auto evaluate_postfix(std::vector<lexeme> const& tokens) -> std::expected<long long, parse_error> {
    std::vector<long long> stack;

    for (auto const& token : tokens) {
        if (token.type == lexeme_type::INTEGER) {
            stack.push_back(token.value);
            continue;
        }
        if (stack.size() < 2) {
            return std::unexpected(parse_error::malformed_expression);
        }
        long long const rhs = stack.back();
        stack.pop_back();
        long long const lhs = stack.back();
        stack.pop_back();

        switch (token.type) {
            case lexeme_type::PLUS:
                stack.push_back(lhs + rhs);
                break;
            case lexeme_type::MINUS:
                stack.push_back(lhs - rhs);
                break;
            case lexeme_type::TIMES:
                stack.push_back(lhs * rhs);
                break;
            default:
                return std::unexpected(parse_error::malformed_expression);
        }
    }
    if (stack.size() != 1) {
        return std::unexpected(parse_error::malformed_expression);
    }
    return stack.front();
}
}  // namespace
auto main() -> int {
    std::string expression;
    std::getline(std::cin, expression);

    auto const result = tokenize(expression)
                            .and_then(resolve_unary_operators)
                            .and_then(infix_to_postfix)
                            .and_then(evaluate_postfix);

    if (result.has_value()) {
        std::cout << *result << '\n';
    } else {
        std::cout << "WRONG" << '\n';
    }
}