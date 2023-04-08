#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Goods {
    int cnt = 0;
    std::string name;
};
int main()
{
    freopen("input.txt", "r", stdin);
    std::vector<Goods> goods;
    std::map<std::string, int64_t> quontity;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string command;
        std::cin >> command;
        if (command == "add") {
            int cnt;
            std::string name;
            std::cin >> cnt >> name;
            goods.push_back({ cnt, name });
            quontity[name] += cnt;
        } else if (command == "delete") {
            int cnt;
            std::cin >> cnt;
            while (true) {
                if (goods.empty() || cnt == 0) {
                    break;
                }
                auto& it = goods.back();
                int curr = std::min(it.cnt, cnt);
                it.cnt -= curr;
                cnt -= curr;
                quontity[it.name] -= curr;
                if (quontity[it.name] == 0) {
                    quontity.erase(it.name);
                }
                if (it.cnt == 0) {
                    goods.pop_back();
                } else {
                    break;
                }
            }
        } else {
            std::string name;
            std::cin >> name;
            if (auto it = quontity.find(name); it != quontity.end()) {
                std::cout << it->second << std::endl;
            } else {
                std::cout << "0" << std::endl;
            }
        }
    }
}
