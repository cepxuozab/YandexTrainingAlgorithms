import sys


def nums_possible_dating(att_distances: list[int], max_visible: int):
    size = len(att_distances)
    right = 0
    answer = 0
    for left in range(size):
        while right < size and att_distances[right] - att_distances[left] <= max_visible:
            right += 1
        answer += size - right
    return answer


if __name__ == "__main__":
    params = []
    for line in sys.stdin:
        params.append(line)
    max_visible = int(params[0].split()[1])
    att_distances = [int(dist) for dist in params[1].strip().split()]
    print(nums_possible_dating(att_distances, max_visible))
