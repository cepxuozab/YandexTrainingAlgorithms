#include <iostream>
#include <queue>
#include <string>

int main() {
    std::queue<int> q;
    while ("xdd") {
        std::string command;
        std::cin >> command;
        if (command == "push") {
            int n;
            std::cin >> n;
            q.push(n);
            std::cout << "ok";
        } else if (command == "pop") {
            if (!q.empty()) {
                int n = q.front();
                q.pop();
                std::cout << n;
            } else {
                std::cout << "error";
            }
        } else if (command == "front") {
            if (!q.empty()) {
                std::cout << q.front();
            } else {
                std::cout << "error";
            }
        } else if (command == "size") {
            std::cout << q.size();
        } else if (command == "clear") {
            while (!q.empty()) {
                q.pop();
            }
            std::cout << "ok";
        } else if (command == "exit") {
            break;
        }
        std::cout << '\n';
    }

    std::cout << "bye" << '\n';

    return 0;
}