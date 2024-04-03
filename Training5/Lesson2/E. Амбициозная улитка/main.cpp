#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

auto main() -> int {
    int n;
    cin >> n;
    int a, b;
    vector<int> orderPositive;
    orderPositive.reserve(n);
    vector<int> orderNegative;
    orderNegative.reserve(n);
    int maxB{};
    int maxBIndex = -1;
    bool firstPositive = true;
    int maxA{};
    int maxAIndex = -1;
    bool firstNegative = true;
    vector<int> vectorA;
    vector<int> vectorB;
    vectorA.reserve(n);
    vectorB.reserve(n);
    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        vectorA.push_back(a);
        vectorB.push_back(b);
        int delta = a - b;
        if (delta <= 0) {
            if (firstNegative) {
                firstNegative = false;
                maxA = a;
                maxAIndex = i;
            } else {
                if (maxA < a) {
                    maxA = a;
                    maxAIndex = i;
                }
            }
            orderNegative.push_back(i);
        } else {
            if (firstPositive) {
                firstPositive = false;
                maxB = b;
                maxBIndex = i;
            } else {
                if (maxB < b) {
                    maxB = b;
                    maxBIndex = i;
                }
            }
            orderPositive.push_back(i);
        }
    }

    int64_t current = 0;
    int64_t maxValue = 0;

    if (orderPositive.size() > 0) {
        for (auto const& index : orderPositive) {
            if (index == maxBIndex) continue;
            if (maxValue < current + vectorA[index]) {
                maxValue = current + vectorA[index];
            }
            current += vectorA[index] - vectorB[index];
        }

        if (maxValue < current + vectorA[maxBIndex]) {
            maxValue = current + vectorA[maxBIndex];
        }
        current += vectorA[maxBIndex] - vectorB[maxBIndex];
    }

    if (maxValue < current + vectorA[maxAIndex]) {
        maxValue = current + vectorA[maxAIndex];
    }

    cout << maxValue << "\n";
    if (orderPositive.size() > 0) {
        for (auto const& index : orderPositive) {
            if (index == maxBIndex) continue;
            cout << (index + 1) << " ";
        }
        cout << (maxBIndex + 1) << " ";
    }

    if (orderNegative.size() > 0) {
        cout << (maxAIndex + 1) << " ";
        for (auto const& index : orderNegative) {
            if (index == maxAIndex) continue;
            cout << (index + 1) << " ";
        }
    }
}