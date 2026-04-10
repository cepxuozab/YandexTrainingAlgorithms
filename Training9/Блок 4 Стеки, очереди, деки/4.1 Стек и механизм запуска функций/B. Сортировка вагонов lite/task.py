def sort_wagons_lite(wagons: list[int]) -> str:
    stack = []
    out = 0
    for wagon in wagons:
        stack.append(wagon)
        while stack and stack[-1] == out + 1:
            stack.pop()
            out += 1
    return "NO" if stack else "YES"


def main():
    _ = input()
    wagons = list(map(int, input().split()))
    print(sort_wagons_lite(wagons))


if __name__ == "__main__":
    main()
