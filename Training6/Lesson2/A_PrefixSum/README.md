# A. Префиксные суммы

По данной последовательности a<sub>1</sub>, a<sub>2</sub>,,,, a<sub>n</sub> вычислите последовательность ее префиксных сумм
b<sub>1</sub>, b<sub>2</sub>,,,, b<sub>n</sub>, где b<sub>j</sub> = a<sub>1</sub> +  a<sub>2</sub> + ,,, + a<sub>j</sub>.


## Формат ввода

В первой строке дано одно целое число n (1 &le; n &le; 10<sup>3</sup>).
Во второй строке даны n целых чисел a<sub>i</sub> (-10<sup>6</sup> &le; a<sub>i</sub> &le; 10<sup>6</sup>).  

## Формат вывода

Выведите n целых чисел b<sub>1</sub>, b<sub>2</sub>,,,, b<sub>n</sub>— последовательность префиксных сумм для последовательности a.

## Пример 1

**Ввод**  
```c++
5
10 -4 5 0 2
```
**Вывод**  
```c++
10 6 11 11 13
```