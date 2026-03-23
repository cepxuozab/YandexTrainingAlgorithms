def main() -> None:
    numbers: list[int] = list(map(int, input().split()))

    # Track two largest and two smallest values for O(n) solution
    max1 = max2 = float('-inf')  # largest, second largest
    min1 = min2 = float('inf')  # smallest, second smallest

    for num in numbers:
        # Update two maximums 
        if num > max1:
            max2, max1 = max1, num
        elif num > max2:
            max2 = num

        # Update two minimums
        if num < min1:
            min2, min1 = min1, num
        elif num < min2:
            min2 = num

    # Maximum product is either from two largest positives or two smallest negatives
    if max1 * max2 >= min1 * min2:
        print(max2, max1)  # Already in non-decreasing order: max2 <= max1
    else:
        print(min1, min2)  # Already in non-decreasing order: min1 <= min2


if __name__ == "__main__":
    main()
