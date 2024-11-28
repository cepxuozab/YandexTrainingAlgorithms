# E. Размер поддеревьев

Дано неориентированное дерево, подвешенное за вершину 1. Для каждой вершины подсчитайте, сколько вершин содержится в
поддереве, подвешенном за данную вершину.

## Формат ввода

В первой строке вводится число V — количество вершин (3 ≤ V ≤ 100000)

В следующих V-1 строках записано по два числа: номера соединенных ребром вершин

## Формат вывода

Выведите V чисел — размеры поддеревьев для каждой из вершин

## Пример 1

**Ввод**

```
4
1 2
1 3
1 4
```  

**Вывод**

```
4 1 1 1 
```

## Пример 2

**Ввод**

```
7
1 2
1 3
1 4
5 1
5 6
5 7
```  

**Вывод**

```
7 1 1 1 3 1 1  
```