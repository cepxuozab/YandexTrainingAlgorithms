import sys


def numbers_sum(cars: list[int], target: int) -> int:
    ans = 0
    cnt = dict()
    cnt[0] = 1
    for i in range(1, len(cars)):
        cars[i] = cars[i - 1] + cars[i]
    for num in cars:
        if num - target in cnt:
            ans += cnt[num - target]
        cnt[num] = cnt.get(num, 0) + 1
    return ans


if __name__ == "__main__":
    n, k = map(int, input().split())
    arr = [int(num) for num in sys.stdin.readline().rstrip().split()]
    print(numbers_sum(arr, k))
