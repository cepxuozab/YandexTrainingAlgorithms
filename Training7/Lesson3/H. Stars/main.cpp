#include <iostream>
#include <vector>

class Fenwick3D {
private:
    int size_;
    std::vector<int> data_;

    inline int index(int x, int y, int z) const {
        return x * size_ * size_ + y * size_ + z;
    }

    inline int& at(int x, int y, int z) {
        return data_[index(x, y, z)];
    }

    inline int get(int x, int y, int z) const {
        return data_[index(x, y, z)];
    }

public:
    explicit Fenwick3D(int size)
        : size_(size + 2), data_((size + 2) * (size + 2) * (size + 2), 0) {}

    void add(int x, int y, int z, int value) {
        for (int i = x; i < size_; i += i & -i) {
            for (int j = y; j < size_; j += j & -j) {
                for (int k = z; k < size_; k += k & -k) {
                    at(i, j, k) += value;
                }
            }
        }
    }

    int sumPrefix(int x, int y, int z) const {
        int result = 0;
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                for (int k = z; k > 0; k -= k & -k) {
                    result += get(i, j, k);
                }
            }
        }
        return result;
    }

    int sum(int x1, int y1, int z1, int x2, int y2, int z2) const {
        auto A = sumPrefix(x2, y2, z2);
        auto B = sumPrefix(x1 - 1, y2, z2);
        auto C = sumPrefix(x2, y1 - 1, z2);
        auto D = sumPrefix(x2, y2, z1 - 1);
        auto E = sumPrefix(x1 - 1, y1 - 1, z2);
        auto F = sumPrefix(x1 - 1, y2, z1 - 1);
        auto G = sumPrefix(x2, y1 - 1, z1 - 1);
        auto H = sumPrefix(x1 - 1, y1 - 1, z1 - 1);
        return A - B - C - D + E + F + G - H;
    }
};

int main() {
    int n;
    std::cin >> n;
    Fenwick3D tree(n);

    while (true) {
        int command;
        std::cin >> command;

        if (command == 1) {
            int x, y, z, value;
            std::cin >> x >> y >> z >> value;
            tree.add(x + 1, y + 1, z + 1, value);
        } else if (command == 2) {
            int x1, y1, z1, x2, y2, z2;
            std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            std::cout << tree.sum(x1 + 1, y1 + 1, z1 + 1, x2 + 1, y2 + 1, z2 + 1) << '\n';
        } else if (command == 3) {
            break;
        }
    }

    return 0;
}
