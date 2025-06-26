#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <ranges>
#include <numeric>

struct Item {
    int i;
    int rating;
    int kicked = 0;
    Item* next = nullptr;
    Item* prev = nullptr;

    Item(int i, int rating) : i(i), rating(rating) {}
};

int main() {
    int n;
    std::cin >> n;

    std::vector<int> ratings(n);
    for (auto& r : ratings) std::cin >> r;

    // Используем unique_ptr для автоматического удаления
    std::vector<std::unique_ptr<Item>> players;
    players.reserve(n);
    for (int i = 0; i < n; ++i) {
        players.emplace_back(std::make_unique<Item>(i, ratings[i]));
    }

    // Формируем кольцевой список
    for (int i = 0; i < n; ++i) {
        players[i]->prev = players[(i - 1 + n) % n].get();
        players[i]->next = players[(i + 1) % n].get();
    }

    int left = n;
    int rnd = 1;
    std::vector<int> out;
    std::vector<int> to_check(n);
    std::iota(to_check.begin(),to_check.end(), 0);

    while (left >= 3) {
        out.clear();

        for (int i : to_check) {
            auto* cur = players[i].get();
            if (cur->kicked == 0 &&
                cur->rating < cur->prev->rating &&
                cur->rating < cur->next->rating) {
                out.push_back(i);
            }
        }

        if (out.empty()) break;

        to_check.clear();

        for (int i : out) {
            auto* player = players[i].get();
            // Удаляем из списка
            player->prev->next = player->next;
            player->next->prev = player->prev;
            player->kicked = rnd;
            to_check.push_back(player->prev->i);
            to_check.push_back(player->next->i);
            --left;
        }

        // Уникализируем to_check, чтобы избежать повторных проверок
        std::ranges::sort(to_check);
        to_check.erase(std::unique(to_check.begin(), to_check.end()), to_check.end());

        ++rnd;
    }

    for (const auto& player : players) {
        std::cout << player->kicked << ' ';
    }
    std::cout << '\n';

    return 0;
}
