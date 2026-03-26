from collections import defaultdict
import sys


def main() -> None:
    goods = defaultdict(lambda: defaultdict(int))

    # Читаем все строки до конца ввода
    for line in sys.stdin:
        line = line.strip()
        if not line:  # Пропускаем пустые строки
            continue
        name, good, cnt = line.split()
        goods[name][good] += int(cnt)

    for name in sorted(goods.keys()):
        print(f'{name}:')
        for good_name in sorted(goods[name].keys()):
            print(f'{good_name} {goods[name][good_name]}')


if __name__ == "__main__":
    main()
