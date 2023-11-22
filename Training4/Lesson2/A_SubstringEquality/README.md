﻿## A. Равенство подстрок

Дана строка S, состоящая из строчных латинских букв.

Определите, совпадают ли строки одинаковой длины L, начинающиеся с позиций A и B.
### Формат ввода 
В первой строке записана S (1 ≤ |S| ≤ 2 *10<sup>5</sup>), состоящая из строчных латинских букв.

Во второй строке записано число Q (1 ≤ Q ≤ 2 * 10<sup>5</sup>) — количество запросов.

В следющих Q строках записаны запросы: целые числа L, A и B (1 ≤ L ≤ |S|, 0 ≤ A, B ≤ (|S| - L)) — длина подстрок и позиции, с которых они начинаются.
### Формат вывода

Если строки совпадают — выведите "yes", иначе — "no".  

Пример 1   

### Ввод
```cpp
acabaca
3
4 3 2
3 4 0
2 0 1
```
### Вывод
```cpp
no
yes
no
```
Пример 2   

### Ввод
```cpp
caeabaeadedcbdcdccec
10
13 4 3
2 12 15
10 1 3
3 8 15
13 5 6
7 2 6
9 8 8
19 0 0
19 0 0
6 7 13
```
### Вывод
```cpp
no
no
no
no
no
no
yes
yes
yes
no
```