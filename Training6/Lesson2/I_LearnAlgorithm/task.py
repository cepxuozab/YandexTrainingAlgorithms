import sys


def learning_algorithm(a: list[int], b: list[int], c: list[int]) -> list[int]:
    ans = []
    algo = []
    for i in range(len(a)):
        algo.append((a[i], b[i], i + 1))
    sorted_a = list(sorted(algo, key=lambda x: (x[0], x[1], -x[2]), reverse=True))
    sorted_b = list(sorted(algo, key=lambda x: (x[1], x[0], -x[2]), reverse=True))
    used_id = set()
    pa, pb = 0, 0
    for idx in c:
        if idx == 0 and pa < len(a):
            if not sorted_a[pa][2] in used_id:
                ans.append(sorted_a[pa][2])
                used_id.add(sorted_a[pa][2])
                pa += 1
            else:
                while pa < len(a):
                    if not sorted_a[pa][2] in used_id:
                        ans.append(sorted_a[pa][2])
                        used_id.add(sorted_a[pa][2])
                        pa += 1
                        break
                    pa += 1
        elif idx == 1 and pb < len(b):
            if not sorted_b[pb][2] in used_id:
                ans.append(sorted_b[pb][2])
                used_id.add(sorted_b[pb][2])
                pb += 1
            else:
                while pb < len(b):
                    if not sorted_b[pb][2] in used_id:
                        ans.append(sorted_b[pb][2])
                        used_id.add(sorted_b[pb][2])
                        pb += 1
                        break
                    pb += 1
    return ans


if __name__ == "__main__":
    _ = input()
    interesting_values = [int(s) for s in sys.stdin.readline().rstrip().split()]
    utility_values = [int(s) for s in sys.stdin.readline().rstrip().split()]
    mood_indicators = [int(s) for s in sys.stdin.readline().rstrip().split()]
    print(*learning_algorithm(interesting_values, utility_values, mood_indicators))
