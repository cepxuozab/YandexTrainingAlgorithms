# D. Максимум на подотрезках с изменением элемента

Реализуйте эффективную структуру данных, позволяющую изменять элементы массива и вычислять максимальное значение из
нескольких подряд идущих элементов.

## Формат ввода

В первой строке вводится одно натуральное число _N (1≤ N ≤ 100 000)_ — количество чисел в массиве.

Во второй строке вводятся _N_ чисел от _1_ до _100 000_ — элементы массива.

В третьей строке вводится одно натуральное число _M (1 ≤ M ≤ 30000)_ — количество запросов.

Каждая из следующих _M_ строк представляет собой описание запроса. Сначала вводится одна буква, кодирующая вид запроса (
_s_ — вычислить максимум, _u_ — обновить значение элемента).

Следом за _s_ вводятся два числа — номера левой и правой границы отрезка.

Следом за _u_ вводятся два числа — номер элемента и его новое значение.

## Формат вывода

Для каждого запроса _s_ выведите результат. Все числа выводите в одну строку через пробел.

## Пример 1

### Ввод

    5
    1 2 3 4 5
    5
    s 1 5
    u 3 10
    s 1 5
    u 2 12
    s 1 3

### Вывод

    5 10 12 


