#include <cmath>
#include <cstdio>
#include <vector>

int main()
{
    int numberOfVertices;
    scanf("%d", &numberOfVertices);
    std::vector<std::vector<int>> adjacencyMatrix(numberOfVertices);
    for (int i = 0; i < numberOfVertices; ++i) {
        adjacencyMatrix[i].resize(numberOfVertices);
        for (int j = 0; j < numberOfVertices; ++j) {
            scanf("%d", &adjacencyMatrix[i][j]);
        }
    }
    int maxValue = (int)pow(2, numberOfVertices);
    int maxPermutation = 0;
    int maxLength = 0;
    auto doCut = [&]() {
        for (int i = 1; i < maxValue - 1; i++) {
            int currentLength = 0;
            int mask = 0xFFFFFFFF >> (32 - numberOfVertices);
            if (maxPermutation != (i ^ mask)) {
                for (int j = 0; j < numberOfVertices; j++) {
                    int maskBit = 1 << j;
                    if ((i & maskBit) == 0) {
                        for (int k = 0; k < numberOfVertices; k++) {
                            if (((i >> k) & 1) == 1) {
                                currentLength += adjacencyMatrix[j][k];
                            }
                        }
                    }
                }
            }
            if (currentLength > maxLength) {
                maxLength = currentLength;
                maxPermutation = i;
            }
        }
    };
    doCut();
    printf("%d\n", maxLength);
    for (int i = 0; i < numberOfVertices; i++) {
        int ans = ((maxPermutation >> i) & 1) == 1 ? 2 : 1;
        printf("%d ", ans);
    }
}
