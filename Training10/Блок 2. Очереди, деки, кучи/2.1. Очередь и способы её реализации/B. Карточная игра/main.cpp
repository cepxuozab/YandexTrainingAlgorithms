#include <iostream>
#include <print>
#include <queue>



auto main() -> int
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    FILE *stream;
    if (freopen_s(&stream, "input.txt", "r", stdin) != 0) {
        std::cerr << "Не удалось открыть input.txt\n";
        return 1;
    }

    constexpr int n = 10;
    std::queue<int> first;
    std::queue<int> second;
    constexpr int cnt = n / 2;
    int t;
    for (int i = 0; i < cnt; ++i) {
        std::cin >> t;
        first.push(t);
    }
    for (int i = 0; i < cnt; ++i) {
        std::cin >> t;
        second.push(t);
    }
    bool firstRes = false;
    bool secondRes = false;
    int count;
    constexpr int MAXIMUM = 1000000;
    for (count = 0; (!firstRes) && (!secondRes) && (count <= MAXIMUM); ++count) {
        int a = first.front();
        int b = second.front();
        first.pop();
        second.pop();
        std::queue<int>* ptr_queue;
        if (((a == 0) && (b == n - 1)) || (!((a == n - 1) && (b == 0)) && (a > b))) {
            ptr_queue = &first;
        } else {
            ptr_queue = &second;
        }
        ptr_queue->push(a);
        ptr_queue->push(b);
        firstRes = first.empty();
        secondRes = second.empty();
    }
    if (firstRes) {
        std::println("second {}", count);
    } else if (secondRes) {
        std::println("first {}", count);
    } else {
        std::println("botva");
    }
    return 0;
}