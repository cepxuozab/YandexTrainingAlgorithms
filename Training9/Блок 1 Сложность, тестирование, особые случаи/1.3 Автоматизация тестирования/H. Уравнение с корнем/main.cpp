#include <iostream>
#include <string>


auto solve(int a, int b, int c) -> std::string
{
    if (c < 0)
    {
        return "NO SOLUTION\n";
    }
    if (a == 0)
    {
        if (b == c * c)
        {
            return "MANY SOLUTIONS\n";
        }
        else
        {
            return "NO SOLUTION\n";
        }
    }
    else
    {
        if (!((c * c - b) % a))
        {
            return std::to_string((c * c - b) / a);
        }
        else
        {
            return "NO SOLUTION\n";
        }
    }
}

auto main() -> int
{
    int a;
    int b;
    int c;
    std::cin >> a >> b >> c;
    std::cout << solve(a, b, c);
    return 0;
}
