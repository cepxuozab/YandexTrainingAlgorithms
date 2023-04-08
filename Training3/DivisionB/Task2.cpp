#include <iostream>
#include <limits>
#include <string>
int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input file");
        return 1;
    }
    int k;
    std::cin >> k;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string word;
    std::cin >> word;
    int size = static_cast<int>(word.size());
    if (k >= size) {
        std::cout << size << std::endl;
        return 0;
    }
    int result = 0;
    for (char c = 'a'; c <= 'z'; ++c) {
        int cur_beauty = 0;
        int left = 0;
        int cur_k = k;
        for (int right = 0; right != size; ++right) {
            if (word[right] != c) {
                cur_k -= 1;
            }
            if (cur_k >= 0 || word[right] == c) {
                cur_beauty += 1;
            } else {
                if (cur_beauty > result) {
                    result = cur_beauty;
                }
                while (cur_k != 0 && cur_beauty >= 0) {
                    if (word[left] != c) {
                        cur_k += 1;
                    }
                    left += 1;
                    cur_beauty -= 1;
                }
                cur_beauty++;
            }
        }
        if (cur_beauty > result) {
            result = cur_beauty;
        }
    }
    std::cout << result << std::endl;
    return 0;
}
