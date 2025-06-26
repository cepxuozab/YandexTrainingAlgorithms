#include <iostream>
#include <list>
#include <cstdint>

enum class FactoryEvent { Bankrupt = 1, Split = 2 };

class FactorySystem {
    std::list<int64_t> factories;
    int64_t sum_squares = 0;

public:
    void initialize() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);

        size_t n;
        std::cin >> n;

        factories.clear();
        sum_squares = 0;

        for (size_t i = 0; i < n; ++i) {
            int64_t val;
            std::cin >> val;
            factories.push_back(val);
            sum_squares += val * val;
        }

        std::cout << sum_squares << '\n';
    }

    void process_events() {
        size_t k;
        std::cin >> k;

        auto current = factories.begin();
        size_t current_index = 0;

        for (size_t i = 0; i < k; ++i) {
            int event_num;
            size_t factory_pos;
            std::cin >> event_num >> factory_pos;
            --factory_pos; // Convert to zero-based index

            move_to(current, current_index, factory_pos);

            if (static_cast<FactoryEvent>(event_num) == FactoryEvent::Bankrupt) {
                process_bankruptcy(current, current_index);
            } else {
                process_split(current);
            }

            std::cout << sum_squares << '\n';
        }
    }

private:
    // Перемещаем итератор current к позиции target_index
    void move_to(std::list<int64_t>::iterator& current, size_t& current_index, size_t target_index) {
        while (current_index < target_index && current != factories.end()) {
            ++current;
            ++current_index;
        }
        while (current_index > target_index && current != factories.begin()) {
            --current;
            --current_index;
        }
    }

    void process_bankruptcy(std::list<int64_t>::iterator& current, size_t& current_index) {
        if (factories.size() <= 1) return; // Нечего удалять

        auto next_it = std::next(current);
        bool is_first = (current == factories.begin());
        bool is_last = (next_it == factories.end());

        if (is_first) {
            // Удаление первого элемента: сливаем с следующим
            int64_t product = 2 * (*current) * (*next_it);
            sum_squares += product;

            *next_it += *current;

            // Удаляем current, current теперь указывает на next_it
            current = factories.erase(current);
            // current_index не меняется, т.к. current сдвинулся вперёд
        }
        else if (is_last) {
            // Удаление последнего элемента: сливаем с предыдущим
            auto prev_it = std::prev(current);

            int64_t product = 2 * (*current) * (*prev_it);
            sum_squares += product;

            *prev_it += *current;

            // Удаляем current, current теперь указывает на prev_it
            current = factories.erase(current);
            --current_index;
            current = prev_it;
        }
        else {
            // Удаление в середине: делим current на две части и добавляем к соседям
            auto prev_it = std::prev(current);

            int64_t left = *current / 2;
            int64_t right = *current - left;

            // Убираем вклад удаляемой фабрики
            sum_squares -= (*current) * (*current);

            // Убираем вклад соседей перед изменением
            sum_squares -= (*prev_it) * (*prev_it);
            sum_squares -= (*next_it) * (*next_it);

            *prev_it += left;
            *next_it += right;

            // Добавляем обновлённый вклад соседей
            sum_squares += (*prev_it) * (*prev_it);
            sum_squares += (*next_it) * (*next_it);

            current = factories.erase(current);
            // current указывает на next_it после erase
            // current_index не меняется, т.к. current сдвинулся вперёд
        }
    }

    void process_split(std::list<int64_t>::iterator& current) {
        int64_t left = *current / 2;
        int64_t right = *current - left;

        // Убираем вклад исходной фабрики
        sum_squares -= (*current) * (*current);

        // Добавляем вклад двух новых фабрик
        sum_squares += left * left + right * right;

        // Обновляем текущую фабрику и вставляем новую справа
        *current = left;
        factories.insert(std::next(current), right);
    }
};

int main() {
    FactorySystem system;
    system.initialize();
    system.process_events();
    return 0;
}
