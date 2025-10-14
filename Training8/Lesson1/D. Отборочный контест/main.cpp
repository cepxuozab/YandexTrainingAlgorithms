#include <iostream>
#include <vector>
#include <unordered_map>

auto main() -> int {
    unsigned n, k;
    std::cin >> n >> k;
    std::unordered_map<int, int> freq;
    for (unsigned i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        freq[x]++;
    }

    std::vector<int> answer;
    answer.reserve(k);

    // Фаза 1: взять по одному каждого уникального (максимум разнообразия)
    for (auto it = freq.begin(); it != freq.end() && answer.size() < k;) {
        answer.push_back(it->first);
        it->second--;
        if (it->second == 0) {
            it = freq.erase(it);
        } else {
            ++it;
        }
    }

    // Фаза 2: если ещё нужно, добираем из оставшихся (любые)
    if (answer.size() < k) {
        for (auto &p: freq) {
            while (p.second > 0 && answer.size() < k) {
                answer.push_back(p.first);
                p.second--;
            }
            if (answer.size() >= k) break;
        }
    }

    for (int a: answer) std::cout << a << ' ';
    return 0;
}