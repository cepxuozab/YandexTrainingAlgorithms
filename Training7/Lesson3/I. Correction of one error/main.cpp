#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <unordered_set>
#include <algorithm>

const std::unordered_set<int> POW2 = {
    1, 2, 4, 8, 16, 32, 64, 128,
    256, 512, 1024, 2048, 4096,
    8192, 16384, 32768, 65536, 131072
};

std::string encode(const std::string& s) {
    std::vector<int> encoded = {0};
    int encoded_len = 1;

    for (char c : s) {
        while (POW2.contains(encoded_len)) {
            encoded.push_back(1);
            ++encoded_len;
        }
        encoded.push_back(c - '0');
        ++encoded_len;
    }

    int ctrl_i = 1;
    while (ctrl_i < encoded_len) {
        for (int i = 2; i < static_cast<int>(encoded.size()); ++i) {
            if (i == ctrl_i) continue;
            if (ctrl_i & i) {
                encoded[ctrl_i] ^= encoded[i];
            }
        }
        ctrl_i <<= 1;
    }

    std::string result;
    for (size_t i = 1; i < encoded.size(); ++i) {
        result += static_cast<char>(encoded[i] + '0');
    }
    return result;
}

std::string decode(const std::string& s) {
    std::vector<int> encoded = {0};
    for (char c : s) {
        encoded.push_back(c - '0');
    }

    int forbidden = 0;
    int ctrl_i = 1;
    while (ctrl_i < static_cast<int>(encoded.size())) {
        int ctrl = 0;
        for (int i = 1; i < static_cast<int>(encoded.size()); ++i) {
            if (ctrl_i & i) {
                ctrl ^= encoded[i];
            }
        }
        if (ctrl == 0) {
            forbidden |= ctrl_i;
        }
        ctrl_i <<= 1;
    }

    if (forbidden < static_cast<int>(encoded.size())) {
        encoded[forbidden] ^= 1;
    }

    std::string decoded;
    for (size_t i = 1; i < encoded.size(); ++i) {
        if (POW2.contains(static_cast<int>(i))) continue;
        decoded += static_cast<char>(encoded[i] + '0');
    }

    return decoded;
}

int main() {
    std::string cmd;
    std::cin >> cmd;

    std::string s;
    std::cin >> s;

    if (cmd == "1") {
        std::cout << encode(s) << "\n";
    } else if (cmd == "2") {
        std::cout << decode(s) << "\n";
    }

    return 0;
}
