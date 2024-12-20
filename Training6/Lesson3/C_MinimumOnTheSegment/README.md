# C. Минимум на отрезке

Рассмотрим последовательность целых чисел длины n. По ней с шагом 1 двигается «окно» длины k, то есть сначала в «окне» видны первые
k чисел, на следующем шаге в «окне» уже будут находиться k чисел, начиная со второго, и так далее до конца последовательности. Требуется для каждого положения «окна» определить минимум в нём.

## Формат ввода

В первой строке входных данных содержатся два натуральных числа n и k (n ≤  150000, k ≤ 10000, k ≤ n) – длины последовательности и «окна», соответственно. На следующей строке находятся
n чисел – сама последовательность.

## Формат вывода

Выходные данные должны содержать n - k + 1 строк – минимумы для каждого положения «окна».  

## Пример 1

**Ввод**  
```
7 3
1 3 2 4 5 3 1
```
**Вывод**
```
1
2
2
3
1
```  

## Примечания

Обратите внимание, что решение с непосредственным подсчётом минимума для каждого положения окна не пройдёт по времени.
