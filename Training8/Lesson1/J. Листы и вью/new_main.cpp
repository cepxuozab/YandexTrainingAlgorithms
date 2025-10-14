#include <bits/stdc++.h>

using namespace std;

// ---------------- Lexer ----------------
enum class TokenType : char {
    Identifier, Number, Keyword,
    Assign, Dot, Comma,
    LParen, RParen
};

struct Token {
    TokenType type;
    string text;
};

class Lexer {
    string_view input;
    size_t pos = 0;

    [[nodiscard]] auto peek() const -> char { return pos < input.size() ? input[pos] : '\0'; }

    auto get() -> char { return pos < input.size() ? input[pos++] : '\0'; }

    static auto isIdentStart(char c) -> bool { return isalpha(c); }

    static auto isIdent(char c) -> bool { return isalnum(c); }

    static auto isDigit(char c) -> bool { return isdigit(c); }

public:
    explicit Lexer(string_view s) : input(s) {}

    auto tokenize() -> vector<Token> {
        vector<Token> tokens;
        while (pos < input.size()) {
            char c = peek();
            if (isspace(c)) {
                get();
                continue;
            }

            if (c == '=') {
                tokens.push_back({TokenType::Assign, "="});
                get();
            }
            else if (c == '.') {
                tokens.push_back({TokenType::Dot, "."});
                get();
            }
            else if (c == ',') {
                tokens.push_back({TokenType::Comma, ","});
                get();
            }
            else if (c == '(') {
                tokens.push_back({TokenType::LParen, "("});
                get();
            }
            else if (c == ')') {
                tokens.push_back({TokenType::RParen, ")"});
                get();
            }
            else if (isIdentStart(c)) {
                string s;
                while (isIdent(peek())) s.push_back(get());
                if (s == "List" || s == "new" || s == "subList" ||
                    s == "set" || s == "get" || s == "add") {
                    tokens.push_back({TokenType::Keyword, std::move(s)});
                } else {
                    tokens.push_back({TokenType::Identifier, std::move(s)});
                }
            } else if (isDigit(c)) {
                string s;
                while (isDigit(peek())) s.push_back(get());
                tokens.push_back({TokenType::Number, std::move(s)});
            } else {
                throw runtime_error("Unexpected char in lexer");
            }
        }
        return tokens;
    }
};

// ---------------- AST ----------------
enum class Method : char {
    Get, Set, Add
};

struct Command {
    // варианты: new list, sublist, метод вызова
    string lhs;
    string parent;
    Method method;
    vector<int> args;
    bool is_decl = false;
    bool is_sublist = false;
    vector<int> init_values;
};

// ---------------- Parser ----------------
class Parser {
    vector<Token> tokens;
    size_t pos = 0;

    auto peek() -> Token & { return tokens[pos]; }

    auto get() -> Token & { return tokens[pos++]; }

    [[nodiscard]] auto eof() const -> bool { return pos >= tokens.size(); }

    void expect(TokenType t) {
        if (peek().type != t) throw runtime_error("Unexpected token");
    }

public:
    explicit Parser(vector<Token> t) : tokens(std::move(t)) {}

    auto parse() -> Command {
        Command cmd;

        if (tokens[0].type == TokenType::Keyword && tokens[0].text == "List") {
            // List a = new List(1,2,3) | List b = a.subList(1,2)
            pos = 1;
            expect(TokenType::Identifier);
            cmd.lhs = get().text;

            expect(TokenType::Assign);
            get(); // '='

            if (peek().type == TokenType::Keyword && peek().text == "new") {
                get(); // new
                expect(TokenType::Keyword); // List
                get();
                expect(TokenType::LParen);
                get();

                while (!eof() && peek().type != TokenType::RParen) {
                    expect(TokenType::Number);
                    cmd.init_values.push_back(stoi(get().text));
                    if (peek().type == TokenType::Comma) get();
                }
                expect(TokenType::RParen);
                get();

                cmd.is_decl = true;
            } else {
                // sublist: a.subList(1,2)
                expect(TokenType::Identifier);
                cmd.parent = get().text;

                expect(TokenType::Dot);
                get();
                expect(TokenType::Keyword); // subList
                get();

                expect(TokenType::LParen);
                get();
                while (!eof() && peek().type != TokenType::RParen) {
                    expect(TokenType::Number);
                    cmd.args.push_back(stoi(get().text));
                    if (peek().type == TokenType::Comma) get();
                }
                expect(TokenType::RParen);
                get();

                cmd.is_decl = true;
                cmd.is_sublist = true;
            }
        } else {
            // method call: a.get(2) / a.set(1,5) / a.add(7)
            expect(TokenType::Identifier);
            cmd.lhs = get().text;

            expect(TokenType::Dot);
            get();
            expect(TokenType::Keyword);

            string m = get().text;
            if (m == "get") cmd.method = Method::Get;
            else if (m == "set") cmd.method = Method::Set;
            else if (m == "add") cmd.method = Method::Add;
            else throw runtime_error("Unknown method");

            expect(TokenType::LParen);
            get();
            while (!eof() && peek().type != TokenType::RParen) {
                expect(TokenType::Number);
                cmd.args.push_back(stoi(get().text));
                if (peek().type == TokenType::Comma) get();
            }
            expect(TokenType::RParen);
            get();
        }
        return cmd;
    }
};

// ---------------- Interpreter ----------------
struct ListData {
    vector<int> values;
};

struct FigonList {
    shared_ptr<ListData> data;
    size_t offset = 0;
    size_t length = 0;
    bool is_original = true;

    [[nodiscard]] auto get(size_t i) const -> int { return data->values[offset + i]; }

    void set(size_t i, int val) { data->values[offset + i] = val; }

    void add(int val) {
        if (!is_original) throw runtime_error("add not allowed on sublist");
        data->values.push_back(val);
        ++length;
    }
};

class Interpreter {
    unordered_map<string, FigonList> vars;

public:
    void exec(const Command &cmd) {
        if (cmd.is_decl) {
            if (!cmd.is_sublist) {
                // new List
                auto data = make_shared<ListData>();
                data->values = cmd.init_values;
                vars[cmd.lhs] = {.data=data, .offset=0, .length=data->values.size(), .is_original=true};
            } else {
                // subList
                auto &p = vars.at(cmd.parent);
                int from = cmd.args[0];
                int to = cmd.args[1];
                size_t start = p.offset + (from - 1);
                size_t len = to - from + 1;
                vars[cmd.lhs] = {.data=p.data, .offset=start, .length=len, .is_original=false};
            }
        } else {
            // method call
            auto &list = vars.at(cmd.lhs);
            switch (cmd.method) {
                case Method::Get:
                    cout << list.get(cmd.args[0] - 1) << "\n";
                    break;
                case Method::Set:
                    list.set(cmd.args[0] - 1, cmd.args[1]);
                    break;
                case Method::Add:
                    list.add(cmd.args[0]);
                    break;
            }
        }
    }
};

// ---------------- main ----------------
auto main() -> int {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    cin.ignore();

    Interpreter interp;

    while (n--) {
        string line;
        getline(cin, line);
        Lexer lex(line);
        auto tokens = lex.tokenize();
        Parser parser(tokens);
        Command cmd = parser.parse();
        interp.exec(cmd);
    }
}
