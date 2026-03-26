from collections import Counter


def main() -> None:
    import sys

    input = sys.stdin.readline

    _ = int(input())
    s = input().strip()

    cnt = Counter(s)

    left = []
    mid = ""

    for ch in map(chr, range(65, 91)):  # A-Z
        if cnt[ch] % 2 == 1 and not mid:
            mid = ch
        left.append(ch * (cnt[ch] // 2))

    left_part = "".join(left)
    right_part = left_part[::-1]

    print(left_part + mid + right_part)


if __name__ == "__main__":
    main()