#include <iostream>
#include <string>
#include <list>

class Windows {
private:
    std::list<std::string> windows;

public:
    std::string run(const std::string& val) {
        windows.push_front(val);
        return windows.front();
    }

    std::string alt_tab(int k) {
        if (windows.empty()) return "";

        int n = k % windows.size();
        if (n == 0) return windows.front();

        auto it = windows.begin();
        std::advance(it, n); // перемещаем итератор на n-ое окно

        // Перемещаем это окно в начало
        windows.splice(windows.begin(), windows, it);

        return windows.front();
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
