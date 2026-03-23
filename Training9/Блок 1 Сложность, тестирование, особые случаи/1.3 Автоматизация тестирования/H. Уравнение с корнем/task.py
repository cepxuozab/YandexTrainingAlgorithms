def root_eq(a: int, b: int, c: int) -> int | str:
    if c < 0: return "NO SOLUTION"
    if a == 0: return "MANY SOLUTIONS" if b == c * c else "NO SOLUTION"
    if not (c * c - b) % a:
        return (c * c - b) // a
    else:
        return "NO SOLUTION"


def main():
    a = int(input())
    b = int(input())
    c = int(input())
    print(root_eq(a, b, c))


if __name__ == "__main__":
    main()
