def min_distance(buildings: list[int]) -> int:
    n = len(buildings)
    ans = 0
    for i in range(n):
        if buildings[i] == 1:
            tmp_min = n
            for j in range(n):
                if buildings[j] == 2:
                    tmp_min = min(tmp_min, abs(i - j))
            ans = max(ans, tmp_min)
    return ans


def main():
    buildings = list(map(int, input().split()))
    print(min_distance(buildings))


if __name__ == "__main__":
    main()
