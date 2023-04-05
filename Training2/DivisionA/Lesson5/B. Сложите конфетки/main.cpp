#include <algorithm>
#include <deque>
#include <iostream>

struct Candy {
    int64_t quantity = 0;
    int num = 0;
};

auto main() -> int
{
    // freopen("input.txt", "r", stdin);
    int k;
    std::cin >> k;
    std::deque<Candy> sweeties;

    for (int i = 0; i < k; ++i) {
        int64_t quantity;
        int num;
        std::cin >> quantity >> num;
        sweeties.push_back({ quantity, num });
        if (k == 1 && num == 1) {
            std::cout << k + 1 << '\n'
                << quantity;
            return 0;
        }
    }

    int left_pointer = 0;
    int right_pointer = k - 1;
    int64_t A = sweeties[left_pointer].quantity;
    sweeties[left_pointer].num -= 1;
    int64_t B = 0;
    if (sweeties[left_pointer].num > 0) {
        B = A;
        sweeties[left_pointer].num -= 1;
    }
    else {
        if (left_pointer < right_pointer) {
            left_pointer += 1;
            B = sweeties[left_pointer].quantity;
            sweeties[left_pointer].num -= 1;
        }
        else {
            B = A;
            A = 0;
        }
    }

    if (sweeties[left_pointer].num == 0 and left_pointer < right_pointer) {
        left_pointer += 1;
    }
    int64_t D = sweeties[right_pointer].quantity;
    sweeties[right_pointer].num -= 1;
    int64_t C = 0;
    if (sweeties[right_pointer].num > 0) {
        C = D;
        sweeties[right_pointer].num -= 1;
    }
    else {
        if (left_pointer < right_pointer) {
            right_pointer -= 1;
            C = sweeties[right_pointer].quantity;
            sweeties[right_pointer].num -= 1;
        }
        else {
            C = D;
            D = 0;
        }
    }
    if (sweeties[right_pointer].num == 0 and left_pointer < right_pointer) {
        right_pointer -= 1;
    }
    while (true) {
        if (A != 0 and B != 0 and C != 0 and D != 0) {
            int64_t count = std::min(A, D);
            A -= count;
            B += count;
            C += count;
            D -= count;
            if (A == 0) {
                if (sweeties[left_pointer].num > 0) {
                    sweeties[left_pointer].num -= 1;
                    A = B;
                    B = sweeties[left_pointer].quantity;
                    if (sweeties[left_pointer].num == 0 and left_pointer < right_pointer) {
                        left_pointer += 1;
                    }
                }
                else {
                    if (left_pointer < right_pointer) {
                        left_pointer += 1;
                        sweeties[left_pointer].num -= 1;
                        A = B;
                        B = sweeties[left_pointer].quantity;
                        if (sweeties[left_pointer].num == 0 and left_pointer < right_pointer) {
                            left_pointer += 1;
                        }
                    }
                }
            }
            if (D == 0) {
                if (sweeties[right_pointer].num > 0) {
                    sweeties[right_pointer].num -= 1;
                    D = C;
                    C = sweeties[right_pointer].quantity;
                    if (sweeties[right_pointer].num == 0 and left_pointer < right_pointer) {
                        right_pointer -= 1;
                    }
                }
                else {
                    if (left_pointer < right_pointer) {
                        right_pointer -= 1;
                        sweeties[right_pointer].num -= 1;
                        D = C;
                        C = sweeties[right_pointer].quantity;
                        if (sweeties[right_pointer].num == 0 and left_pointer < right_pointer) {
                            right_pointer -= 1;
                        }
                    }
                }
            }

        }
        else if (A == 0 and D == 0) {
            std::cout << 2 << '\n'
                << B << ' ' << C;
            return 0;
        }
        else if (A == 0) {
            int64_t count = std::min(B, D);
            B -= count;
            C += count * 2;
            D -= count;
            if (B == 0 && D == 0) {
                std::cout << 1 << '\n'
                    << C;
                return 0;
            }
            if (B == 0) {
                std::cout << 2 << '\n'
                    << C << ' ' << D;
                return 0;
            }
            else {
                std::cout << 2 << '\n'
                    << B << ' ' << C;
                return 0;
            }
        }
        else if (D == 0) {
            int64_t count = std::min(A, C);
            A -= count;
            B += count * 2;
            C -= count;
            if (A == 0 and C == 0) {
                std::cout << 1 << '\n'
                    << B;
                return 0;
            }
            if (A == 0) {
                std::cout << 2 << '\n'
                    << B << ' ' << C;
                return 0;

            }
            else {
                std::cout << 2 << '\n'
                    << A << ' ' << B;
                return 0;
            }
        }
        else if (B == 0) {
            std::cout << 1 << '\n'
                << C;
            return 0;
        }
        else if (C == 0) {
            std::cout << 1 << '\n'
                << B;
            return 0;
        }
    }
}
