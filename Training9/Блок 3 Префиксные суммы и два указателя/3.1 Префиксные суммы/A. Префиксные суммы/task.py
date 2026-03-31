def prefix_sum(arr: list[int]) -> list[int]:
    answer = [0]
    for i in arr:
        answer.append(answer[-1] + i)
    return answer[1::]


def main():
    _ = input()
    arr = list(map(int, input().split()))
    print(*prefix_sum(arr))


if __name__ == '__main__':
    main()
