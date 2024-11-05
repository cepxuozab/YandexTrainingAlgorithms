import sys


def make_prefix(arr: list[int], needed_reverse=False) -> list[int]:
    prefix = [0 for _ in range(len(arr))]
    if needed_reverse:
        arr.reverse()
    curr = 0
    for i in range(1, len(arr)):
        curr += arr[i - 1]
        prefix[i] = prefix[i - 1] + curr
    if needed_reverse:
        prefix.reverse()
    return prefix


def relocate_to_openspace(rooms: list[int]) -> int:
    left = make_prefix(rooms.copy())
    right = make_prefix(rooms.copy(), True)
    ans = float('inf')
    for i in range(len(rooms)):
        ans = min(ans, left[i] + right[i])
    return int(ans)


if __name__ == "__main__":
    _ = input()
    data = [int(s) for s in sys.stdin.readline().rstrip().split()]
    print(relocate_to_openspace(data))
