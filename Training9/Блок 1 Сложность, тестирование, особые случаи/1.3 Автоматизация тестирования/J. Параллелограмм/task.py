from dataclasses import dataclass


@dataclass(order=True)
class Point:
    x: int = 0
    y: int = 0


def check(points: list[Point]) -> bool:
    is_flag = (points[1].x - points[0].x) == (points[3].x - points[2].x)
    is_flag = is_flag and (points[1].y - points[0].y) == (points[3].y - points[2].y)
    return is_flag


def main() -> None:
    n = int(input())
    for _ in range(n):
        coords = list(map(int, input().split()))
        points = [Point(coords[i], coords[i + 1]) for i in range(0, 8, 2)]
        points.sort()
        print("YES" if check(points) else "NO")


if __name__ == "__main__":
    main()
