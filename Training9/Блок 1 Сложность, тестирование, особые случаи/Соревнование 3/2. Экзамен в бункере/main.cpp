#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdint>

namespace {

    using i64 = std::int64_t;

    auto update_answer(i64 rows, i64 max_row_size, i64& answer) -> void {
        if (max_row_size >= 1) {
            answer = std::min(answer, std::abs(rows - max_row_size));
        }
    }

    auto process_rows(i64 n, i64 rows, i64 offset, i64& answer) -> void {
        // rows * a + offset = n
        i64 a = (n - offset) / rows;
        if (a >= 1 && rows * a + offset == n) {
            update_answer(rows, a + 1, answer);
        }

        // rows * (a + 1) - offset = n
        a = (n + offset) / rows - 1;
        if (a >= 1 && rows * (a + 1) - offset == n) {
            update_answer(rows, a + 1, answer);
        }
    }

    auto min_diff(i64 n) -> i64 {
        i64 answer = n - 1;

        for (i64 rows = 1; rows * rows <= 2 * n; ++rows) {

            // случай без чередования (все ряды одинаковые)
            if (n % rows == 0) {
                const i64 max_row_size = n / rows;
                update_answer(rows, max_row_size, answer);
            }

            const i64 offset = (rows % 2 == 0) ? rows / 2 : (rows - 1) / 2;
            process_rows(n, rows, offset, answer);
        }

        return answer;
    }

} // namespace

auto main() -> int {
    std::int64_t n{};
    std::cin >> n;
    std::cout << min_diff(n) << '\n';
}