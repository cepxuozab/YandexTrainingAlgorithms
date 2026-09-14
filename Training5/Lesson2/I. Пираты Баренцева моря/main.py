def min_moves(n: int, ships: list)->int:
    x = sorted(ship[0] for ship in ships)
    y = sorted(ship[1] for ship in ships)

    median_y = y[n // 2]

    moves_x = sum(abs(x[i] - (i + 1)) for i in range(n))
    moves_y = sum(abs(u - median_y) for u in y)

    return moves_x + moves_y


def main()->None:
    n = int(input())

    ships = []
    for _ in range(n):
        x, y = map(int, input().split())
        ships.append((x, y))

    print(min_moves(n, ships))


if __name__ == "__main__":
    main()
