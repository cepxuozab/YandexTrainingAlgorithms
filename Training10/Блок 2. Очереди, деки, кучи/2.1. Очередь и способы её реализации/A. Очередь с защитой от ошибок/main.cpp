#include <iostream>
#include <queue>
#include <string>

auto main() -> int {
    std::queue<int> queue;
    while (true) {
        std::string operation;
        std::cin >> operation;
        if (operation == "exit") {
            std::cout << "bye" << '\n';
            return 0;
        }
        if (operation == "push") {
            int x;
            std::cin >> x;
            queue.push(x);
            std::cout << "ok" << '\n';
        } else if (operation == "size") {
            std::cout << queue.size() <<  '\n';
        } else if (operation == "pop" || operation == "front") {
            if (queue.empty()) {
                std::cout << "error" << '\n';
            } else {
                std::cout << queue.front() << '\n';
                if (operation == "pop") {
                    queue.pop();
                }
            }
        } else if (operation == "clear") {
            while (!queue.empty()) {
                queue.pop();
            }
            std::cout << "ok" << '\n';
        }
    }
}