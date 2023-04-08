#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

enum class BINARY_OPERATION {
  XOR,
  END,
  OR
};

enum class UNARY_OPERATION {
  NOT
};

enum class VALUES {
  ZERO,
  ONE
};

enum class BRACKETS {
  OPEN,
  CLOSE
};

using Token = std::variant<BINARY_OPERATION, UNARY_OPERATION, VALUES, BRACKETS>;

int Priority(Token token);

Token ConvertChar(char ch);

std::vector<Token> Tokenize(std::string_view expression);

std::vector<Token> ToPolishNotation(std::vector<Token> const& tokens);

std::optional<int> Calculate(std::vector<Token> const& notation);

namespace utility {
void Print(std::string_view name, std::vector<int> stack);
void Print(std::string_view name, std::vector<Token> const& tokens);
void Print(Token token);
void Print(BRACKETS bracket);
void Print(VALUES value);
void Print(UNARY_OPERATION operation);
void Print(BINARY_OPERATION operation);
}

void Test();

int main()
{
  Test();
  std::string expression;
  getline(std::cin, expression);
  auto ans = Calculate(ToPolishNotation(Tokenize(expression)));
  if (ans.has_value()) {
    std::cout << ans.value() << std::endl;
  } else {
    std::cout << "WRONG" << std::endl;
  }
}

void Test()
{
  assert(Calculate(ToPolishNotation(Tokenize("1|(0&0^1)"))) == 1);
  assert(Calculate(ToPolishNotation(Tokenize("!1"))) == 0);
  assert(Calculate(ToPolishNotation(Tokenize("1|(0&0^1)"))) == 1);
  assert(Calculate(ToPolishNotation(Tokenize("!1 | !(0 & 0 ^ 1)"))) == 0);
}

Token ConvertChar(char ch)
{
  Token token {};
  switch (ch) {
  case '(':
    token = BRACKETS::OPEN;
    break;
  case ')':
    token = BRACKETS::CLOSE;
    break;
  case '!':
    token = UNARY_OPERATION::NOT;
    break;
  case '^':
    token = BINARY_OPERATION::XOR;
    break;
  case '&':
    token = BINARY_OPERATION::END;
    break;
  case '|':
    token = BINARY_OPERATION::OR;
    break;
  case '0':
    token = VALUES::ZERO;
    break;
  case '1':
    token = VALUES::ONE;
    break;
  default:
    break;
  }
  return token;
}

std::vector<Token> Tokenize(std::string_view expression)
{
  std::vector<Token> tokens;
  for (char ch : expression) {
    if (ch != ' ') {
      tokens.push_back(ConvertChar(ch));
    }
  }
  return tokens;
}

int Priority(Token token)
{
  if (std::holds_alternative<BRACKETS>(token)) {
    return -1;
  }
  if (std::holds_alternative<UNARY_OPERATION>(token)) {
    return 2;
  }
  auto binary_operation = std::get<BINARY_OPERATION>(token);
  return binary_operation == BINARY_OPERATION::END ? 1 : 0;
}

std::vector<Token> ToPolishNotation(std::vector<Token> const& tokens)
{
  std::vector<Token> stack, notation;
  for (auto const& token : tokens) {
    if (std::holds_alternative<VALUES>(token)) {
      notation.push_back(token);
    } else if (std::holds_alternative<BRACKETS>(token)) {
      auto bracket = std::get<BRACKETS>(token);
      if (bracket == BRACKETS::OPEN) {
        stack.push_back(token);
      } else {
        while (!stack.empty() && stack.back() != Token { BRACKETS::OPEN }) {
          notation.push_back(stack.back());
          stack.pop_back();
        }
        if (!stack.empty()) {
          stack.pop_back();
        }
      }
    } else {
      while (!stack.empty() && Priority(token) <= Priority(stack.back())) {
        notation.push_back(stack.back());
        stack.pop_back();
      }
      stack.push_back(token);
    }
  }
  notation.insert(notation.end(), stack.rbegin(), stack.rend());
  return notation;
}

std::optional<int> Calculate(std::vector<Token> const& notation)
{
  if (notation.empty()) {
    return std::nullopt;
  }
  std::map<BINARY_OPERATION, std::function<bool(bool, bool)>> operations {
      { BINARY_OPERATION::OR, [](bool lhs, bool rhs) { return lhs | rhs; } },
      { BINARY_OPERATION::XOR, [](bool lhs, bool rhs) { return lhs ^ rhs; } },
      { BINARY_OPERATION::END, [](bool lhs, bool rhs) { return lhs & rhs; } }
  };
  std::vector<int> stack;
  for (auto const& token : notation) {

    if (std::holds_alternative<BINARY_OPERATION>(token)) {
      auto x1 = stack.back();
      stack.pop_back();
      auto x2 = stack.back();
      stack.pop_back();
      auto curr_operation = std::get<BINARY_OPERATION>(token);
      stack.push_back(operations.at(curr_operation)(x1, x2));
    } else if (std::holds_alternative<UNARY_OPERATION>(token)) {
      stack.back() = stack.back() ? 0 : 1;
    } else {
      auto value = std::get<VALUES>(token);
      value == VALUES::ZERO ? stack.push_back(false) : stack.push_back(true);
    }
  }
  return stack.back();
}

namespace utility {
void Print(BINARY_OPERATION operation)
{
  switch (operation) {
  case BINARY_OPERATION::XOR:
    std::cout << "XOR" << std::endl;
    break;
  case BINARY_OPERATION::END:
    std::cout << "END" << std::endl;
    break;
  default:
    std::cout << "OR" << std::endl;
  }
}

void Print(UNARY_OPERATION operation)
{
  std::cout << "NOT" << std::endl;
}

void Print(VALUES value)
{
  switch (value) {
  case VALUES::ZERO:
    std::cout << "ZERO" << std::endl;
    break;
  case VALUES::ONE:
    std::cout << "ONE" << std::endl;
    break;
  default:
    break;
  }
}

void Print(BRACKETS bracket)
{
  switch (bracket) {
  case BRACKETS::OPEN:
    std::cout << "OPEN" << std::endl;
    break;
  case BRACKETS::CLOSE:
    std::cout << "CLOSE" << std::endl;
    break;
  default:
    break;
  }
}

void Print(Token token)
{
  std::visit([](auto&& arg) { Print(arg); }, token);
}

void Print(std::string_view name, std::vector<Token> const& tokens)
{
  std::cout << name << std::endl;
  for (auto&& token : tokens) {
    Print(token);
  }
}

void Print(std::string_view name, std::vector<int> stack)
{
  std::cout << name << std::endl;
  for (bool val : stack) {
    std::cout << std::boolalpha << val << std::endl;
  }
}
}
