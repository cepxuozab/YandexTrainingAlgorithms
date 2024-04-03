#include <iostream>

auto war(int a, int b, int c, int& count) -> bool {
    int cur = c;
    while (b != 0 && a > 0) {
        if (b > a) {
            b -= a;
            a -= cur;
        } else {
            cur -= (a - b);
            b = 0;
            a -= cur;
        }
        count += 1;
        if (b > 0) {
            cur += c;
        }
    }
    if (b == 0) {
        while (cur > 0 && a > 0) {
            cur -= a;
            if (cur > 0) {
                a -= cur;
            }
            count += 1;
        }
        return a > 0;
    }
    return false;
}

auto Game(int x, int y, int p) -> int {
    if (x >= y) {
        return 1;
    }
    int min_moves = -1, move_count2 = 1;
    y -= x;
    int A = x, B = y, C = p;
    int const add = p;
    while (B > 0 && A > 0) {
       int const move_count = move_count2;
        if (int count{move_count}; war(A, B, C, count)) {
            if (min_moves == -1 || min_moves > count) {
                min_moves = count;
            }
            if (C == A) {
                return min_moves;
            }
        } else if (C == A) {
            return -1;
        }
        if (C > A) {
            C -= A;
            A -= C;
        } else {
            B -= (A - C);
            C = 0;
        }
        if (B > 0) {
            C += add;
        }
        move_count2 += 1;
    }
    return min_moves;
}

auto main() -> int {
    int x, y, p;
    std::cin >> x >> y >> p;
    std::cout << Game(x, y, p);
}
