#include <array>
#include <iostream>
#include <string>

#include <cstdint>

uint_least8_t symbolToIndx(char symbol)
{
    return symbol - ((symbol < 'a') ? 'A' : 'a' - 26);
}

int modifyCount(int& count, int_fast8_t modifier)
{
    count += modifier;
    if (count == 0)
        return 1;
    else if (count == modifier)
        return -1;
    else
        return 0;
}

int main()
{
    int n, m;

    std::cin >> n >> m;

    std::string word, sentense;
    std::cin >> word >> sentense;

    std::array<int, 52> counter {};
    int difference = 0;

    for (int i = 0; i < n; i++) {
        difference += modifyCount(counter[symbolToIndx(word[i])], +1);
        difference += modifyCount(counter[symbolToIndx(sentense[i])], -1);
    }

    int result = 0;
    if (difference == 0)
        result += 1;

    for (int i = n; i < m; i++) {
        difference += modifyCount(counter[symbolToIndx(sentense[i - n])], +1);
        difference += modifyCount(counter[symbolToIndx(sentense[i])], -1);

        if (difference == 0)
            result += 1;
    }

    std::cout << result;

    return 0;
}
