def prefix_sum(arr: list[int]) -> list[int]:
    answer = [0]
    for i in arr:
        answer.append(answer[-1] + i)
    return answer[1::]


def main():
    n = int(input())
    arr = list(map(int, input().split()))
    prefix = prefix_sum(arr)
    q = int(input())
    x = int(input())
    mod = 1000000007
    ans = 0
    for _ in range(q):
        x0 = x
        x1 = (11173 * x0 + 1) % mod
        left = min(x0 % n, x1 % n)
        right = max(x0 % n, x1 % n)
        range_sum = prefix[right]
        if left != 0:
            range_sum -= prefix[left - 1]
        ans += range_sum
        ans %= mod
        x = (11173 * x1 + 1) % mod
    print(ans)


if __name__ == '__main__':
    main()
