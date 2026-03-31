def main():
    n = int(input())
    positions = set()
    for _ in range(n):
        a, b = map(int, input().split())
        if a >= 0 and b >= 0 and (a + b) == n - 1:
            positions.add(b + 1)
    print(len(positions))


if __name__ == '__main__':
    main()
