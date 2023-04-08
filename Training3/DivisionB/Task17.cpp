#include <iostream>
#include <queue>

static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

auto main() -> int
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }

    int n = 10;
    // std::cin >> n;
    std::queue<int> first;
    std::queue<int> second;
    int cnt = n / 2;
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
    int const MAXIMUM = 1000000;
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
        printf("second %d\n", count);
    } else if (secondRes) {
        printf("first %d\n", count);
    } else {
        printf("botva\n");
    }
    return 0;
}
