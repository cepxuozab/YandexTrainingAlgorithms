﻿## G. Кролик учит геометрию

Кролики очень любопытны. Они любят изучать геометрию, бегая по грядкам. Наш кролик как раз такой. Сегодня он решил изучить новую фигуру — квадрат.

Кролик бегает по грядке — клеточному полю N × M клеток. В некоторых из них посеяны морковки, в некоторых нет.

Помогите кролику найти сторону квадрата наибольшей площади, заполненного морковками полностью.

### Формат ввода
В первой строке даны два натуральных числа N и M (1 <= M, N <= 1000 ). Далее в N строках расположено по M чисел, разделенных пробелами (число равно 0, если в клетке нет морковки или 1, если есть).

### Формат вывода
Выведите одно число — сторону наибольшего квадрата, заполненного морковками..

Пример 1  
### Ввод
```cpp
4 5
0 0 0 1 0
0 1 1 1 0
0 0 1 1 0
1 0 1 0 0
```
### Вывод
```cpp
2
```

Пример 2  
### Ввод
```cpp
10 10
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1
```
### Вывод
```cpp
10
```

Пример 3  
### Ввод
```cpp
10 10
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
```
### Вывод
```cpp
0
```