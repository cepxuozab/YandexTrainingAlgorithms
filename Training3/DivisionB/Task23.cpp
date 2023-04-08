#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    freopen("input.txt", "r", stdin);
    int N;
    std::cin >> N;

    std::vector<int> minPathLength(N + 1, 1);
    std::vector<int> prev(N + 1, -1);

    int leastLenInd;
    for (int i = 4; i <= N; i++) {
        if (i % 6 == 0) {
            leastLenInd = std::min({ minPathLength[i / 3], minPathLength[i / 2], minPathLength[i - 1] });
            if (leastLenInd == minPathLength[i / 3]) {
                minPathLength[i] = minPathLength[i / 3] + 1;
                prev[i] = i / 3;
            } else if (leastLenInd == minPathLength[i / 2]) {
                minPathLength[i] = minPathLength[i / 2] + 1;
                prev[i] = i / 2;
            } else {
                minPathLength[i] = minPathLength[i - 1] + 1;
                prev[i] = i - 1;
            }
        } else if (i % 2 == 0) {
            if (minPathLength[i / 2] < minPathLength[i - 1]) {
                minPathLength[i] = minPathLength[i / 2] + 1;
                prev[i] = i / 2;
            } else {
                minPathLength[i] = minPathLength[i - 1] + 1;
                prev[i] = i - 1;
            }
        } else if (i % 3 == 0) {
            if (minPathLength[i / 3] < minPathLength[i - 1]) {
                minPathLength[i] = minPathLength[i / 3] + 1;
                prev[i] = i / 3;
            } else {
                minPathLength[i] = minPathLength[i - 1] + 1;
                prev[i] = i - 1;
            }
        } else {
            minPathLength[i] = minPathLength[i - 1] + 1;
            prev[i] = i - 1;
        }
    }

    if (N == 1) {
        minPathLength[1] = 0;
        std::cout << minPathLength[N] << "\n1 ";
        return 0;
    }

    std::vector<int> pathFromStart(minPathLength[N]);
    int i = N;
    int j = minPathLength[N] - 1;

    do {
        pathFromStart[j--] = i;
        i = prev[i];
    } while (i != -1);
    std::cout << pathFromStart.size() << std::endl;
    std::cout << 1 << ' ';
    for (int num : pathFromStart)
        std::cout << num << ' ';

    return 0;
}
