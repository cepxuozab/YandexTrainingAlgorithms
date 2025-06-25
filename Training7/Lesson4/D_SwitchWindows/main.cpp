#include <iostream>
#include <string>
#include <memory>

class Item {
public:
    std::string val;
    Item* next;
    Item* prev;

    Item(const std::string& v) : val(v), next(nullptr), prev(nullptr) {}
};

class Windows {
private:
    Item* head;
    int size;

public:
    Windows() : head(nullptr), size(0) {}

    int length() const {
        return size;
    }

    std::string run(const std::string& val) {
        auto* new_item = new Item(val);
        new_item->next = head;
        if (size > 0 && head != nullptr) {
            head->prev = new_item;
        }
        head = new_item;
        ++size;
        return head->val;
    }

    std::string alt_tab(int k) {
        if (size == 0) return "";
        int n = k % size;
        if (n == 0) return head->val;

        Item* cur = head;
        while (n--) {
            cur = cur->next;
        }

        // Отцепляем cur
        if (cur->prev != nullptr) {
            cur->prev->next = cur->next;
        }
        if (cur->next != nullptr) {
            cur->next->prev = cur->prev;
        }

        // Переносим cur в начало
        cur->prev = nullptr;
        cur->next = head;
        if (head != nullptr) {
            head->prev = cur;
        }
        head = cur;

        return head->val;
    }

    ~Windows() {
        while (head) {
            Item* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    Windows win;
    int n;
    std::cin >> n;
    std::cin.ignore();

    for (int i = 0; i < n; ++i) {
        std::string cmd;
        std::getline(std::cin, cmd);

        if (cmd.starts_with("Run ")) {
            std::string app_name = cmd.substr(4);
            std::cout << win.run(app_name) << '\n';
        } else {
            int k = 0;
            size_t pos = 0;
            while ((pos = cmd.find("+Tab", pos)) != std::string::npos) {
                ++k;
                pos += 4;
            }
            std::cout << win.alt_tab(k) << '\n';
        }
    }

    return 0;
}
