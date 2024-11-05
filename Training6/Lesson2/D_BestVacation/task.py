import sys


def best_vacation(days: list[int], k_: int) -> int:
    days.sort()
    ans = 1
    slow, fast = 0, 0
    while fast < len(days):
        if days[fast] <= days[slow] + k_:
            fast += 1
        else:
            ans = max(ans, fast - slow)
            slow += 1
    return max(ans, fast - slow)


if __name__ == "__main__":
    n, k = map(int, input().split())
    arr = [int(num) for num in sys.stdin.readline().rstrip().split()]
    print(best_vacation(arr, k))
