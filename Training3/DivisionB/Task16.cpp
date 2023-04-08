#include <iostream>
#include <queue>
#include <string>
int main()
{
    std::queue<int> queue;
    while (true) {
        std::string operation;
        std::cin >> operation;
        if (operation == "exit") {
            std::cout << "bye" << std::endl;
            return 0;
        }
        if (operation == "push") {
            int x;
            std::cin >> x;
            queue.push(x);
            std::cout << "ok" << std::endl;
        } else if (operation == "size") {
            std::cout << queue.size() << std::endl;
        } else if (operation == "pop" || operation == "front") {
            if (queue.empty()) {
                std::cout << "error" << std::endl;
            } else {
                std::cout << queue.front() << std::endl;
                if (operation == "pop") {
                    queue.pop();
                }
            }
        } else if (operation == "clear") {
            while (!queue.empty()) {
                queue.pop();
            }
            std::cout << "ok" << std::endl;
        }
    }
}
