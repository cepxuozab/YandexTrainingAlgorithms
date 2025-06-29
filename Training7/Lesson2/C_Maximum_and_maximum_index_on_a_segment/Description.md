# C. Максимум и индекс максимума на отрезке

Реализуйте структуру данных, которая на данном массиве из _N_ целых чисел позволяет узнать максимальное значение на этом
массиве и индекс элемента, на котором достигается это максимальное значение.

## Формат ввода

В первой строке вводится натуральное число _N (1 ≤ N ≤ 10<sup>5</sup>)_ — количество элементов в массиве. В следующей
строке содержатся _N_ целых чисел, не превосходящих по модулю 10<sup>9</sup>
— элементы массива. Гарантируется, что в массиве нет одинаковых элементов. Далее идет число _K (0 ≤ K ≤ 10<sup>
5</sup>)_ — количество запросов к структуре данных. Каждая из следующих _K_ строк содержит два целых числа _l и r (1 ≤
l ≤ r ≤ N)_ — левую и правую границы отрезка в массиве для данного запроса.

## Формат вывода

Для каждого из запросов выведите два числа: наибольшее значение среди элементов массива на отрезке от _l_ до _r_ и
индекс одного из элементов массива, принадлежащий отрезку от _l_ до _r_, на котором достигается этот максимум.

## Пример 1

### Ввод

    5
    7 3 1 6 4
    3
    1 5
    2 4
    3 3

### Вывод

    7 1
    6 4
    1 3


