import sys
from itertools import accumulate
from typing import Final


def count_triple_products(arr: list[int], mod: int) -> int:
    """
    Вычисляет сумму a[i] * a[j] * a[k] для всех троек индексов, где i < j < k.

    Алгоритм: для каждого j как среднего элемента считаем
    a[j] * (сумма слева от j) * (сумма справа от j).
    Сложность: O(n) по времени, O(n) по памяти.
    """
    n = len(arr)
    if n < 3:
        return 0

    # Префиксные суммы с модульной арифметикой
    prefix: list[int] = list(accumulate(arr, lambda x, y: (x + y) % mod))
    total_sum = prefix[-1]

    result = 0
    for j in range(1, n - 1):
        left_sum = prefix[j - 1]
        # В Python % всегда возвращает неотрицательное число, +MOD не нужен
        right_sum = (total_sum - prefix[j]) % mod
        # Цепочка модулей предотвращает переполнение (хотя в Python это не критично)
        contribution = arr[j] * left_sum % mod * right_sum % mod
        result = (result + contribution) % mod

    return result


def main() -> None:
    MOD: Final = 1_000_000_007

    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    # Нормализуем входные значения по модулю сразу при чтении
    arr = [x % MOD for x in data[1: n + 1]]

    print(count_triple_products(arr, MOD))


if __name__ == "__main__":
    main()