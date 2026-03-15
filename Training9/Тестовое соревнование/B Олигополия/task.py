import sys


def main():
    data = sys.stdin.read().strip().split()
    if not data:
        return

    n = int(data[0])

    a = [int(x) for x in data[1:n + 1]]

    def can_win(idx):
        cur = a[idx]
        for j in range(n):
            if j == idx:
                continue
            if cur > a[j]:
                cur += a[j]
            else:
                return False
        return True


    lo, hi = 0, n
    while lo < hi:
        mid = (lo + hi) // 2
        if can_win(mid):
            hi = mid
        else:
            lo = mid + 1

    ans = [0] * n
    for i in range(lo, n):
        ans[i] = 1

    print('\n'.join(map(str, ans)))


if __name__ == '__main__':
    main()
