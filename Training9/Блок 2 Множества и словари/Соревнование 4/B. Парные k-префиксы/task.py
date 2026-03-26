from collections import Counter


def check(words: list[str], length: int) -> bool:
    prefixes = (word[:length] for word in words)
    cnt = Counter(prefixes)
    return all(v % 2 == 0 for v in cnt.values())


def searches(words: list[str]) -> int:
    left, right = 0, len(words[0])
    while left < right:
        mid = (left + right + 1) // 2
        if check(words, mid):
            left = mid
        else:
            right = mid - 1
    return left


def main():
    words = [input() for _ in range(int(input()))]
    print(searches(words))


if __name__ == "__main__":
    main()
