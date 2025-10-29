#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <cctype>
#include <algorithm>

struct Node {
    std::string value;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    explicit Node(std::string v,
                  std::unique_ptr<Node> l = nullptr,
                  std::unique_ptr<Node> r = nullptr)
            : value(std::move(v)), left(std::move(l)), right(std::move(r)) {}
};

struct RenderResult {
    std::vector<std::string> lines;
    int root_col;
};

class Parser {
    std::string expr;
    size_t pos = 0;

    char peek() const {
        return pos < expr.size() ? expr[pos] : '\0';
    }

    char consume() {
        return pos < expr.size() ? expr[pos++] : '\0';
    }

    void skip_whitespace() {
        while (peek() == ' ') consume();
    }

public:
    explicit Parser(std::string s) : expr(std::move(s)) {}

    std::unique_ptr<Node> parse_expression();
    std::unique_ptr<Node> parse_term();
    std::unique_ptr<Node> parse_factor();
    std::unique_ptr<Node> parse_primary();
};

std::unique_ptr<Node> Parser::parse_expression() {
    auto left = parse_term();
    while (true) {
        skip_whitespace();
        char op = peek();
        if (op == '+' || op == '-') {
            consume();
            auto right = parse_term();
            left = std::make_unique<Node>(std::string(1, op), std::move(left), std::move(right));
        } else {
            break;
        }
    }
    return left;
}

std::unique_ptr<Node> Parser::parse_term() {
    auto left = parse_factor();
    while (true) {
        skip_whitespace();
        char op = peek();
        if (op == '*' || op == '/') {
            consume();
            auto right = parse_factor();
            left = std::make_unique<Node>(std::string(1, op), std::move(left), std::move(right));
        } else {
            break;
        }
    }
    return left;
}

std::unique_ptr<Node> Parser::parse_factor() {
    auto left = parse_primary();
    skip_whitespace();
    if (peek() == '^') {
        consume();
        auto right = parse_factor();
        left = std::make_unique<Node>("^", std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<Node> Parser::parse_primary() {
    skip_whitespace();
    char c = peek();
    if (c >= 'a' && c <= 'z') {
        consume();
        return std::make_unique<Node>(std::string(1, c));
    } else if (c == '(') {
        consume();
        auto node = parse_expression();
        skip_whitespace();
        if (peek() == ')') {
            consume();
        }
        return node;
    }
    throw std::runtime_error("Parse error");
}
RenderResult render(const Node& node) {
    if (!node.left && !node.right) {
        return {{node.value}, 0};
    }

    auto left_res = render(*node.left);
    auto right_res = render(*node.right);

    int h1 = static_cast<int>(left_res.lines.size());
    int w1 = h1 ? static_cast<int>(left_res.lines[0].size()) : 0;
    int h2 = static_cast<int>(right_res.lines.size());
    int w2 = h2 ? static_cast<int>(right_res.lines[0].size()) : 0;

    int h = std::max(h1, h2);
    int total_width = w1 + w2 + 5;
    int op_pos = w1 + 2; // position of the operator character
    int L = left_res.root_col;
    int R = w1 + 5 + right_res.root_col;

    std::string top_line(total_width, ' ');

    // Left arm
    if (w1 > 0) {
        top_line[L] = '.';
        for (int i = L + 1; i < w1 + 1; ++i) { // up to left bracket (w1+1) exclusive
            top_line[i] = '-';
        }
    }

    // Operator
    top_line[w1 + 1] = '[';
    top_line[op_pos] = node.value[0];
    top_line[w1 + 3] = ']';

    // Right arm
    if (w2 > 0) {
        for (int i = w1 + 4; i < R; ++i) { // from right after ']' to R exclusive
            top_line[i] = '-';
        }
        top_line[R] = '.';
    }

    // Stem line
    std::string stem_line(total_width, ' ');
    if (w1 > 0) stem_line[L] = '|';
    if (w2 > 0) stem_line[R] = '|';

    // Child lines
    std::vector<std::string> child_lines(h);
    for (int i = 0; i < h; ++i) {
        std::string l = (i < h1) ? left_res.lines[i] : std::string(w1, ' ');
        std::string r = (i < h2) ? right_res.lines[i] : std::string(w2, ' ');
        child_lines[i] = l + std::string(5, ' ') + r;
    }

    std::vector<std::string> lines;
    lines.push_back(top_line);
    lines.push_back(stem_line);
    lines.insert(lines.end(), child_lines.begin(), child_lines.end());

    return {lines, op_pos};
}
int main() {
    std::string input;
    std::getline(std::cin, input);

    Parser parser{input};
    auto tree = parser.parse_expression();

    auto result = render(*tree);
    for (const auto& line : result.lines) {
        std::cout << line << '\n';
    }
}