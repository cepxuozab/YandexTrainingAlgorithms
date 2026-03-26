from collections import defaultdict


def main() -> None:
    n = int(input())
    cnt = defaultdict(int)
    for _ in range(n):
        m = int(input())
        for _ in range(m):
            cnt[input()] += 1
    all_lang = [key for key, val in cnt.items() if val == n]
    print(len(all_lang))
    print('\n'.join(all_lang))
    print(len(cnt))
    print('\n'.join(cnt.keys()))


if __name__ == "__main__":
    main()
