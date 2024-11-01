n = int(input())
arr = list(map(int, input().strip().split()))
pre = [0 for _ in range(n)]
pre[0] = arr[0]
for i in range(1, n):
    pre[i] = pre[i - 1] + arr[i]

summ = 0
for i in range(1, n - 1):
    summ = (summ + pre[i - 1] * arr[i] * (pre[n - 1] - pre[i])) % 1000000007

print(summ)
