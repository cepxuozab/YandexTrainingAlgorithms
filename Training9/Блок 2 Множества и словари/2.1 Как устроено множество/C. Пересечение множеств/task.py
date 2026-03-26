def main() -> None:
    with open("input.txt") as fin:
        lines = fin.readlines()

    a = set(map(int, lines[0].split()))
    b = set(map(int, lines[1].split()))

    result = sorted(a & b)

    with open("output.txt", "w") as fout:
        print(*result, file=fout)


if __name__ == "__main__":
    main()
