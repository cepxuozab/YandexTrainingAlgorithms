#include <deque>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

inline void PushFront(std::deque<int>& dq) {
    int n;
    std::cin >> n;
    dq.push_front(n);
    std::cout << "ok";
}

inline void PushBack(std::deque<int>& dq) {
    int n;
    std::cin >> n;
    dq.push_back(n);
    std::cout << "ok";
}

inline void PopFront(std::deque<int>& dq) {
    if (!dq.empty()) {
        int n = dq.front();
        dq.pop_front();
        std::cout << n;
    } else {
        std::cout << "error";
    }
}

inline void PopBack(std::deque<int>& dq) {
    if (!dq.empty()) {
        int n = dq.back();
        dq.pop_back();
        std::cout << n;
    } else {
        std::cout << "error";
    }
}

inline void Front(std::deque<int>& dq) {
    if (!dq.empty()) {
        std::cout << dq.front();
    } else {
        std::cout << "error";
    }
}

inline void Back(std::deque<int>& dq) {
    if (!dq.empty()) {
        std::cout << dq.back();
    } else {
        std::cout << "error";
    }
}

inline void Size(std::deque<int>& dq) {
    std::cout << dq.size();
}

inline void Clear(std::deque<int>& dq) {
    dq.clear();
    std::cout << "ok";
}

inline void Exit(std::deque<int>& ) {
    std::cout << "bye" << '\n';
    exit(0);
}

int main() {
    std::deque<int> dq;
    std::unordered_map<std::string, std::function<void(std::deque<int>&)>> func {
        {"push_front", PushFront},
        {"push_back", PushBack},
        {"pop_front", PopFront},
        {"pop_back", PopBack},
        {"front", Front},
        {"back", Back},
        {"size", Size},
        {"clear", Clear},
        {"exit", Exit}
    };

    while (true) {
        std::string command;
        std::cin >> command;
        func[command](dq);
        std::cout << '\n';
    }

    return 0;
}