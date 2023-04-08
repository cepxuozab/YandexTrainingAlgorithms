#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int main()
{
    int N;
    std::cin >> N;
    int arraySize = std::max(N, 3);
    std::vector<int> seqCount(arraySize);
    seqCount[0] = 2;
    seqCount[1] = 4;
    seqCount[2] = 7;

    for (int i = 3; i < arraySize; i++) {
        seqCount[i] = seqCount[i - 1] + seqCount[i - 2] + seqCount[i - 3];
    }

    std::cout << seqCount[N - 1];
    return 0;
}
