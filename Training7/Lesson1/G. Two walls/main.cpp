#include <iostream>
#include <vector>

void find_lengths(std::vector<int>& brick_indexes, std::vector<int>& brick_lengths, std::vector<int>& lengths) {
    for (const auto& index : brick_indexes) {
        int max_len = lengths.size() - 1;
        const int& brick_len = brick_lengths[index];
        
        for (int i = max_len - brick_len; i >= 0; --i) {
            if (lengths[i] >= 0) {
                if (lengths[i + brick_len] < 0) {
                    lengths[i + brick_len] = index;
                }
            }
        }
    }
}

inline bool wall_exist(std::vector<std::vector<int>>& lengths, size_t length) {
    for (size_t j = 1; j < lengths.size(); ++j) {
        if (lengths[j][length] < 0) {
            return false;
        }
    }

    return true;
}

void print_bricks(std::vector<std::vector<int>>& lengths, std::vector<int>& brick_lengths, size_t length) {
    for (size_t i = 1; i < lengths.size(); ++i) {
        auto row = lengths[i];
        size_t current_length = length;

        while (current_length > 0) {
            int index = row[current_length];
            std::cout << index << '\n';
            current_length -= brick_lengths[index];
        }
    }
}

int main () {
    int n, k;
    std::cin >> n >> k;

    std::vector<std::vector<int>> brick_indexes(k + 1);
    std::vector<int> brick_lengths(n + 1);
    int index = 1;

    for (int i = 0; i < n; ++i) {
        int length, color;
        std::cin >> length >> color;
        brick_indexes[color].push_back(index);
        brick_lengths[index] = length;
        ++index;
    }

    int total_length = 0;
    for (const auto& index : brick_indexes[1]) {
        total_length += brick_lengths[index];
    }

    std::vector<std::vector<int>> lengths(k + 1, std::vector<int>(total_length + 1, -1));
    for (size_t i = 0; i < lengths.size(); ++i) {
        lengths[i][0] = 0;
    }

    for (size_t i = 1; i < brick_indexes.size(); ++i) {
        find_lengths(brick_indexes[i], brick_lengths, lengths[i]);
    }

    int wall_length = 0;

    for (size_t length = total_length - 1; length > 0; --length) {
        if (wall_exist(lengths, length)) {
            wall_length = length;
            break;
        }
    }

    if (wall_length > 0) {
        std::cout << "YES\n";
        print_bricks(lengths, brick_lengths, wall_length);
    } else {
        std::cout << "NO\n";
    }

    return 0;
}