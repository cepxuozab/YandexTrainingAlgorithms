#include <iostream>
#include <string>
#include <vector>

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input file");
        return 1;
    }
    std::vector<int> stack;
    while (true) {
        std::string command;
        std::cin >> command;
        if (command == "push") {
            int n;
            std::cin >> n;
            stack.push_back(n);
            std::cout << "ok" << std::endl;
        }
        else if (command == "pop") {
            if (stack.empty()) {
                std::cout << "error" << std::endl;
                continue;
            }
            std::cout << stack.back() << std::endl;
            stack.pop_back();
        }
        else if (command == "back") {
            if (stack.empty()) {
                std::cout << "error" << std::endl;
                continue;
            }
            std::cout << stack.back() << std::endl;
        }
        else if (command == "size") {
            std::cout << stack.size() << std::endl;
        }
        else if (command == "clear") {
            stack.clear();
            std::cout << "ok" << std::endl;
        }
        else if (command == "exit") {
            std::cout << "bye" << std::endl;
            break;
        }
    }
    return 0;
}
/*
Возможные команды для программы:

push n
Добавить в стек число n (значение n задается после команды). Программа должна вывести ok.

pop
Удалить из стека последний элемент. Программа должна вывести его значение.

back
Программа должна вывести значение последнего элемента, не удаляя его из стека.

size
Программа должна вывести количество элементов в стеке.

clear
Программа должна очистить стек и вывести ok.

exit
Программа должна вывести bye и завершить работу.
*/
