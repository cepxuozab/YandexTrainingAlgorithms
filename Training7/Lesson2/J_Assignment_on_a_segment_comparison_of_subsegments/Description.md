# J. Присваивание на отрезке, сравнение подотрезков*

Реализуйте структуру данных, которая позволяет выполнять две операции:

* Присвоить всем элементам на отрезке от _L_ до _R_ значение _K_
* Поэлементно сравнить все числа на отрезках длины _K_, начинающихся с позиций _L_ и _R_

## Формат ввода

В первой строке записано число _N_ — количество элементов в последовательности _(1 ≤ N ≤ 100 000)_. Во второй строке
записано _N_ целых чисел — начальные значения последовательности, все числа имеют значения от _1_ до _100000_.

В третьей строке записано число _Q_ — количество операций сравнения и присваивания _(1 ≤ Q ≤ 100 000)_. Следующие _Q_
строк содержат описания операций: четыре числа _T, L, R_ и _K_.

Если _T = 0_, то необходимо всем числам с индексами с _L_ до _R_ включительно присвоить значение _K (1 ≤ L ≤ R ≤ N, 1 ≤
K ≤ 100 000)_.

Если _T = 1_, то необходимо сравнить подотрезки, начинающиеся с позиций _L_ и _R_ и имеющие длину _K (1 ≤ L, R ≤ N−K+1,
K > 0)_.

## Формат вывода

Для каждого запроса сравнения подстрок выведите ’+’, если подотрезки совпадают и ’-’ в противном случае в одну строку
без пробелов.

## Пример 1

### Ввод

    5
    1 2 1 2 1
    4
    1 2 4 2
    0 3 5 2
    1 1 3 2
    1 2 3 3

### Вывод

    +-+





