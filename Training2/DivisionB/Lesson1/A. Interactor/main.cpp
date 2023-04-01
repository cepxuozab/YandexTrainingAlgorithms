#include <iostream>

auto main() -> int
{
    short ExitCode;
    short Interact;
    short Checker;
    std::cin >> ExitCode >> Interact >> Checker;
    switch (Interact) {
    case 0:
        std::cout << (ExitCode != 0 ? 3 : Checker);
        break;
    case 1:
        std::cout << Checker;
        break;
    case 4:
        std::cout << (ExitCode != 0 ? 3 : 4);
        break;
    case 6:
        std::cout << 0;
        break;
    case 7:
        std::cout << 1;
        break;
    default:
        std::cout << Interact;
    }
    return 0;
}
