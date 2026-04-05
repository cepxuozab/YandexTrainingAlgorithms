import sys
from collections import defaultdict
from typing import Final


def count_subarrays_with_sum(arr: list[int], target: int) -> int:
    """Возвращает количество подмассивов с суммой, равной target."""
    prefix_count: defaultdict[int, int] = defaultdict(int)
    result = curr_sum = 0

    for num in arr:
        curr_sum += num
        result += (curr_sum == target) + prefix_count[curr_sum - target]
        prefix_count[curr_sum] += 1

    return result


def main() -> None:
    data = sys.stdin.buffer.read().split()
    n: Final = int(data[0])
    k: Final = int(data[1])
    arr = list(map(int, data[2:2 + n]))
    print(count_subarrays_with_sum(arr, k))


if __name__ == "__main__":
    main()
