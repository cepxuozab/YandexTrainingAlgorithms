def t_shirt_and_socks(a: int, b: int, c: int, d: int) -> tuple[int, int]:
    ans: list[tuple[int, int]] = []
    if a > 0 and c > 0: ans.append((b + 1, d + 1))
    if b > 0 and d > 0: ans.append((a + 1, c + 1))
    if a > 0 and b > 0: ans.append((max(a, b) + 1, 1))
    if c > 0 and d > 0: ans.append((1, max(c, d) + 1))
    ans.sort(key=sum)
    return ans[0]


def main():
    a = int(input())
    b = int(input())
    c = int(input())
    d = int(input())
    print(*t_shirt_and_socks(a, b, c, d))


if __name__ == "__main__":
    main()
