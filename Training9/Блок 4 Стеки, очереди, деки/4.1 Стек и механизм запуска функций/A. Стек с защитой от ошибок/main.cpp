#include <iostream>
#include <string>
#include <vector>

auto main() -> int
{
    std::vector<int> stack;
    while (true)
    {
        std::string command;
        std::cin >> command;
        if (command == "push")
        {
            int n;
            std::cin >> n;
            stack.push_back(n);
            std::cout << "ok" << '\n';
        }
        else if (command == "pop")
        {
            if (stack.empty())
            {
                std::cout << "error" << '\n';
                continue;
            }
            std::cout << stack.back() << '\n';
            stack.pop_back();
        }
        else if (command == "back")
        {
            if (stack.empty())
            {
                std::cout << "error" << '\n';
                continue;
            }
            std::cout << stack.back() << '\n';
        }
        else if (command == "size")
        {
            std::cout << stack.size() << '\n';
        }
        else if (command == "clear")
        {
            stack.clear();
            std::cout << "ok" << '\n';
        }
        else if (command == "exit")
        {
            std::cout << "bye" << '\n';
            break;
        }
    }
    return 0;
}
