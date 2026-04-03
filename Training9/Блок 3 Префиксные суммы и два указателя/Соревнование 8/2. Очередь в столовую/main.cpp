#include <iostream>
#include <cstdint>

auto main() -> int{

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int test_cases{};
    if (!(std::cin >> test_cases)) return 0;

    while (test_cases--)
    {
        int n{};
        std::int64_t d{};
        std::cin >> n >> d;

        std::int64_t current_wait{}; // Префиксная сумма времён заказов
        int max_bad_index{};         // Индекс последнего человека, которому не хватит терпения

        for (int i = 1; i <= n; ++i)
        {
            std::int64_t t{}, k{};
            std::cin >> t >> k;

            // Время ожидания i-го человека = sum(k_1..k_{i-1}) = current_wait
            // Если Женя встанет на позицию <= i, к ожиданию i-го добавится d.
            // Проверяем условие: current_wait + d <= t_i
            if (current_wait + d > t)
            {
                max_bad_index = i;
            }

            // Обновляем префиксную сумму для следующего человека
            current_wait += k;
        }

        // Женя должен встать строго после самого "далёкого" проблемного человека.
        // Если проблемных нет (max_bad_index == 0), он встаёт первым (позиция 1).
        std::cout << max_bad_index + 1 << '\n';
    }

    return 0;
}