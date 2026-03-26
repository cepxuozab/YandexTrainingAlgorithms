def main() -> None:
    n = int(input())
    synonyms = dict()
    for _ in range(n):
        a, b = input().split()
        synonyms[b] = a
        synonyms[a] = b
    print(synonyms[input()])


if __name__ == "__main__":
    main()
