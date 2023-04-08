#include <deque>
#include <iostream>
#include <string>

int main()
{
    std::deque<int> deque;
    while (true) {
        std::string op;
        std::cin >> op;
        if (op == "exit") {
            std::cout << "bye" << std::endl;
            break;
        }
        if (op == "size") {
            std::cout << deque.size() << std::endl;
        } else if (op == "clear") {
            deque.clear();
            std::cout << "ok" << std::endl;
        } else if (op == "push_front") {
            int n;
            std::cin >> n;
            deque.push_front(n);
            std::cout << "ok" << std::endl;
        } else if (op == "push_back") {
            int n;
            std::cin >> n;
            deque.push_back(n);
            std::cout << "ok" << std::endl;
        } else if (op == "front" || op == "back") {
            if (!deque.empty()) {
                int ans = op == "front" ? deque.front() : deque.back();
                std::cout << ans << std::endl;
            } else {
                std::cout << "error" << std::endl;
            }
        } else if (op == "pop_front" || op == "pop_back") {
            if (!deque.empty()) {
                int ans = op == "pop_front" ? deque.front() : deque.back();
                std::cout << ans << std::endl;
                op == "pop_front" ? deque.pop_front() : deque.pop_back();
            } else {
                std::cout << "error" << std::endl;
            }
        }
    }
}
