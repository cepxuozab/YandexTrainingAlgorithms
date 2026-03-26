from collections import defaultdict


def main() -> None:
    n = int(input())

    # Игнорируем предыдущие записи
    for _ in range(n):
        _ = input()

    scores = defaultdict(int)
    prev_score_a, prev_score_b = 0, 0

    m = int(input())
    for _ in range(m):
        score_str, player = input().split()
        score_a, score_b = map(int, score_str.split(':'))

        # Сколько добавилось с прошлого шага
        delta = (score_a - prev_score_a) + (score_b - prev_score_b)
        scores[player] += delta

        prev_score_a, prev_score_b = score_a, score_b

    if scores:
        best_player = max(scores, key=scores.get)
        print(best_player, scores[best_player])
    else:
        print()


if __name__ == '__main__':
    main()
