#include <iostream>
#include <vector>

using namespace std;
auto main() -> int {
    int n, a, b, k;
    cin >> n;
    int maxValue = 0;
    bool first = true;
    vector<int> values;
    values.reserve(n);
    for (int i = 0; i < n; ++i) {
        int value;
        cin >> value;
        if (first) {
            first = false;
            maxValue = value;
        } else {
            maxValue = max(value, maxValue);
        }
        values.push_back(value);
    }
    cin >> a >> b >> k;

    int startOffset = a / k;
    if (a <= k * startOffset) {
        --startOffset;
    }

    int finishOffset = b / k;
    if (b <= k * finishOffset) {
        --finishOffset;
    }

    if (finishOffset - startOffset >= n) {
        cout << maxValue;
        return 0;
    }

    first = true;
    int startPosition = startOffset % n;
    int steps = 0;
    // direct find
    while (steps < n) {
        int index = (startPosition + steps) % n;

        int reverseIndex = n - (startPosition + steps);
        if (reverseIndex < 0) {
            reverseIndex += n;
        }
        reverseIndex %= n;

        int value = values[index];
        int reverseValue = values[reverseIndex];

        if (first) {
            maxValue = max(value, reverseValue);
            first = false;
        } else {
            maxValue = max(maxValue, max(value, reverseValue));
        }
        ++steps;
        if (steps > finishOffset - startOffset) break;
    }

    cout << maxValue;
}