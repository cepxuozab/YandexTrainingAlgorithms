#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    if (N == 0) {
        cout << 0 << '\n';
        return 0;
    }

    // Переводим в бинарную строку без ведущих нулей
    string bin = bitset<16>(N).to_string();
    bin = bin.substr(bin.find('1'));  // обрезаем ведущие нули

    int len = bin.size();
    int max_val = 0;

    string rotated = bin;
    for (int i = 0; i < len; ++i) {
        int val = stoi(rotated, nullptr, 2);
        max_val = max(max_val, val);

        // Циклический сдвиг вправо: последний символ в начало
        rotate(rotated.rbegin(), rotated.rbegin() + 1, rotated.rend());
    }

    cout << max_val << '\n';
    return 0;
}
