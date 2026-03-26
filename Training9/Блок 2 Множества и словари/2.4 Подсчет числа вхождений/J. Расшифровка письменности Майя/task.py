def symbol_to_index(c: str) -> int:
    return ord(c) - 65 if c < 'a' else ord(c) - 71  # 71 = ord('a') - 26


def main() -> None:
    import sys

    input = sys.stdin.readline

    n, m = map(int, input().split())
    word = input().strip()
    s = input().strip()

    cnt = [0] * 52
    diff = 0

    def update(idx: int, delta: int) -> int:
        nonlocal cnt
        before = cnt[idx]
        cnt[idx] += delta

        if cnt[idx] == 0:
            return 1
        if before == 0:
            return -1
        return 0

    for i in range(n):
        diff += update(symbol_to_index(word[i]), +1)
        diff += update(symbol_to_index(s[i]), -1)

    res = 1 if diff == 0 else 0

    for i in range(n, m):
        diff += update(symbol_to_index(s[i - n]), +1)
        diff += update(symbol_to_index(s[i]), -1)

        if diff == 0:
            res += 1

    print(res)


if __name__ == "__main__":
    main()
