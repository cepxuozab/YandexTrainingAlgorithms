#include <iostream>
#include <variant>

auto SolveDiofant(int64_t a, int64_t b, int64_t c, int64_t d) -> std::variant<int64_t, const char*>;

auto main() -> int
{
    int64_t a;
    int64_t b;
    int64_t c;
    int64_t d;

    std::cin >> a >> b >> c >> d;

    auto ans = SolveDiofant(a, b, c, d);

    std::visit([](auto&& arg) { std::cout << arg; }, ans);
}

auto SolveDiofant(int64_t a, int64_t b, int64_t c, int64_t d) -> std::variant<int64_t, const char*>
{
    if (a == 0) {
        return b == 0 ? "INF" : "NO";
    }
    if (b % a != 0) {
        return "NO";
    }
    int64_t x = -b / a;
    if (c * x + d == 0) {
        return "NO";
    }
    return x;
}
