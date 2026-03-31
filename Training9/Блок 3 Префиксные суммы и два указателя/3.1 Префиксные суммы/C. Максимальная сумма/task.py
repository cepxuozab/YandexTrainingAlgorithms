def main():
    n = int(input())
    arr = list(map(int, input().split()))
    ans = arr[0]
    summ = 0
    for i in range(n):
        summ += arr[i]
        ans = max(ans, summ)
        summ = max(0, summ)
    print(ans)


if __name__ == '__main__':
    main()
