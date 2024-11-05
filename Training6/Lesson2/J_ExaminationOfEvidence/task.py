import sys


def stop_numbers(a: list[int], x: list[int], num: int) -> list[int]:
    left = [0 for _ in range(len(a))]
    cnt = 0
    for i in range(1, len(a)):
        if a[i - 1] < a[i]:
            left[i] = left[i - 1]
        elif a[i - 1] > a[i]:
            left[i] = i
            cnt = 0
        else:
            cnt += 1
            left[i] = left[i - 1]
            while cnt > num:
                cnt -= a[left[i]] == a[left[i] + 1]
                left[i] += 1
    ans = []
    for xi in x:
        ans.append(left[xi - 1] + 1)
    return ans


if __name__ == "__main__":
    _ = input()
    weight_of_evidence_values = [int(s) for s in sys.stdin.readline().rstrip().split()]
    m, k = map(int, input().split())
    evidence_numbers = [int(s) for s in sys.stdin.readline().rstrip().split()]
    print(*stop_numbers(weight_of_evidence_values, evidence_numbers, k))
