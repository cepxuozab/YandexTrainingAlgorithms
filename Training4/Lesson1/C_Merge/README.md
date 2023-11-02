﻿## C. Слияние

Базовый алгоритм для сортировки слиянием — алгоритм слияния двух упорядоченных массивов в один упорядоченный массив. Эта операция выполняется за линейное время с линейным потреблением памяти.  
Реализуйте слияние двух массивов в качестве первого шага для написания сортировки слиянием.

### Формат ввода 
В первой строке входного файла содержится число N — количество элементов первого массива (0 ≤ N ≤ 10<sup>6</sup>).
Во второй строке содержатся N целых чисел a<sub>i</sub>, разделенных пробелами, отсортированные по неубыванию (-10<sup>9</sup> ≤ a<sub>i</sub> ≤ 10<sup>9</sup>).
В третьей строке входного файла содержится число M — количество элементов второго массива (0 ≤ M ≤ 10<sup>6</sup>).
В третьей строке содежатся M целых чисел b<sub>i</sub>, разделенных пробелами, отсортированные по неубыванию (-10<sup>9</sup> ≤ b<sub>i</sub> ≤ 10<sup>9</sup>).
### Формат вывода

Выведите результат слияния этих двух массивов, то есть M + N целых чисел, разделенных пробелами, в порядке неубывания.  
Пример 1   

### Ввод
```cpp
5
1 3 5 5 9
3
2 5 6
```
### Вывод
```cpp
1 2 3 5 5 5 6 9 
```
Пример 2   

### Ввод
```cpp
1
0
0

```
### Вывод
```cpp
0
```
Пример 3   

### Ввод
```cpp
0

1
0
```
### Вывод
```cpp
0
```
