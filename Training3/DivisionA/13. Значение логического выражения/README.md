# 13. Значение логического выражения

Задано логическое выражение. Необходимо вычислить его значение. В выражении могут встречаться знаки ! (отрицание), & (
логическое «и»), | (логическое «или»), ̂ (XOR — «исключающее ИЛИ», «ровно одно из двух — истина») и скобки. Самый
высокий приоритет у отрицания, меньше – у &, операции | и ̂ имеют самый низкий приоритет (одинаковый) и вычисляются
слева направо. Все числа в выражении либо 0, либо 1.

## Формат ввода

В первой строке вводится выражение. Его длина не превосходит 100 знаков. После выражения идет переход на новую строчку.

## Формат вывода

Выведите значение этого выражения (0 или 1).

## Пример 1

### Ввод

    1|(0&0^1)

### Вывод

    1