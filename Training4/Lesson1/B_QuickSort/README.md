﻿## B. Быстрая сортировка

Реализуйте быструю сортировку, используя алгоритм из предыдущей задачи.

На каждом шаге выбирайте опорный элемент и выполняйте partition относительно него. Затем рекурсивно запуститесь от двух частей, на которые разбился исходный массив.  
### Формат ввода 

В первой строке входного файла содержится число N — количество элементов массива (0 ≤ N ≤ 10<sup>6</sup>).
Во второй строке содержатся N целых чисел a<sub>i</sub>, разделенных пробелами (-10<sup>9</sup> ≤ ai ≤ 10<sup>9</sup>).

### Формат вывода

Выведите результат сортировки, то есть N целых чисел, разделенных пробелами.  

Пример 1   

### Ввод
```cpp
5
1 5 2 4 3

```
### Вывод
```cpp
1 2 3 4 5 
```

### Примечания  
Используйте функцию, реализованную в предыдущей задаче.