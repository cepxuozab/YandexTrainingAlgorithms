# 21. Три единицы подряд

<table>
  <tr>
    <td>Ограничение времени</td>
    <td>1 секунда</td>
  </tr>
  <tr>
    <td>Ограничение памяти</td>
    <td>64Mb</td>
  </tr>
  <tr>
    <td>Ввод</td>
    <td>стандартный ввод или input.txt</td>
  </tr>
  <tr>
    <td>Вывод</td>
    <td>стандартный вывод или output.txt</td>
  </tr>
</table>

По данному числу N определите количество последовательностей из нулей и единиц длины N, в которых никакие три единицы не стоят рядом.

## Формат ввода

Во входном файле написано натуральное число N, не превосходящее 35.

## Формат вывода

Выведите количество искомых последовательностей. Гарантируется, что ответ не превосходит 2<sup>31</sup>-1.

### Пример 1

#### Ввод

```
1
```

#### Вывод

```
2
```

-------------

# 22. Кузнечик

<table>
  <tr>
    <td>Ограничение времени</td>
    <td>1 секунда</td>
  </tr>
  <tr>
    <td>Ограничение памяти</td>
    <td>64Mb</td>
  </tr>
  <tr>
    <td>Ввод</td>
    <td>стандартный ввод или input.txt</td>
  </tr>
  <tr>
    <td>Вывод</td>
    <td>стандартный вывод или output.txt</td>
  </tr>
</table>

У одного из студентов в комнате живёт кузнечик, который очень любит прыгать по клетчатой одномерной доске. Длина доски — N клеток. К его сожалению, он умеет прыгать только на 1, 2, …, k клеток вперёд.

Однажды студентам стало интересно, сколькими способами кузнечик может допрыгать из первой клетки до последней. Помогите им ответить на этот вопрос.

## Формат ввода

В первой и единственной строке входного файла записано два целых числа — N и k (1 ≤ N ≤ 30, 1 ≤ k ≤ 10).

## Формат вывода

Выведите одно число — количество способов, которыми кузнечик может допрыгать из первой клетки до последней.

### Пример 1

#### Ввод

```
8 2
```

#### Вывод

```
21
```

-------------

# 23. Калькулятор

<table>
  <tr>
    <td>Ограничение времени</td>
    <td>2 секунда</td>
  </tr>
  <tr>
    <td>Ограничение памяти</td>
    <td>64Mb</td>
  </tr>
  <tr>
    <td>Ввод</td>
    <td>стандартный ввод или input.txt</td>
  </tr>
  <tr>
    <td>Вывод</td>
    <td>стандартный вывод или output.txt</td>
  </tr>
</table>

Имеется калькулятор, который выполняет следующие операции:

- умножить число X на 2;
- умножить число X на 3;
- прибавить к числу X единицу.

Определите, какое наименьшее количество операций требуется, чтобы получить из числа 1 число N.

## Формат ввода

Во входном файле написано натуральное число N, не превосходящее 10<sup>6</sup>.

## Формат вывода

В первой строке выходного файла выведите минимальное количество операций. Во второй строке выведите числа, последовательно получающиеся при выполнении операций. Первое из них должно быть равно 1, а последнее N. Если решений несколько, выведите любое.

### Пример 1

#### Ввод

```
1
```

#### Вывод

```
0
1
```

### Пример 2

#### Ввод

```
5
```

#### Вывод

```
3
1 3 4 5
```

-------------

# 24. Покупка билетов

<table>
  <tr>
    <td>Ограничение времени</td>
    <td>1 секунда</td>
  </tr>
  <tr>
    <td>Ограничение памяти</td>
    <td>64Mb</td>
  </tr>
  <tr>
    <td>Ввод</td>
    <td>стандартный ввод или input.txt</td>
  </tr>
  <tr>
    <td>Вывод</td>
    <td>стандартный вывод или output.txt</td>
  </tr>
</table>

За билетами на премьеру нового мюзикла выстроилась очередь из N человек, каждый из которых хочет купить 1 билет. На всю очередь работала только одна касса, поэтому продажа билетов шла очень медленно, приводя «постояльцев» очереди в отчаяние. Самые сообразительные быстро заметили, что, как правило, несколько билетов в одни руки кассир продаёт быстрее, чем когда эти же билеты продаются по одному. Поэтому они предложили нескольким подряд стоящим людям отдавать деньги первому из них, чтобы он купил билеты на всех.

Однако для борьбы со спекулянтами кассир продавала не более 3-х билетов в одни руки, поэтому договориться таким образом между собой могли лишь 2 или 3 подряд стоящих человека.

Известно, что на продажу i-му человеку из очереди одного билета кассир тратит A<sub>i</sub> секунд, на продажу двух билетов — B<sub>i</sub> секунд, трех билетов — C<sub>i</sub> секунд. Напишите программу, которая подсчитает минимальное время, за которое могли быть обслужены все покупатели.

Обратите внимание, что билеты на группу объединившихся людей всегда покупает первый из них. Также никто в целях ускорения не покупает лишних билетов (то есть билетов, которые никому не нужны).

## Формат ввода

На вход программы поступает сначала число N — количество покупателей в очереди (1 ≤ N ≤ 5000). Далее идет N троек натуральных чисел A<sub>i</sub>, B<sub>i</sub>, C<sub>i</sub>. Каждое из этих чисел не превышает 3600. Люди в очереди нумеруются, начиная от кассы.

## Формат вывода

Требуется вывести одно число — минимальное время в секундах, за которое могли быть обслужены все покупатели.

### Пример 1

#### Ввод

```
5
5 10 15
2 10 15
5 5 5
20 20 1
20 1 1
```

#### Вывод

```
12
```

-------------

# 25. Гвоздики

<table>
  <tr>
    <td>Ограничение времени</td>
    <td>1 секунда</td>
  </tr>
  <tr>
    <td>Ограничение памяти</td>
    <td>64Mb</td>
  </tr>
  <tr>
    <td>Ввод</td>
    <td>стандартный ввод или input.txt</td>
  </tr>
  <tr>
    <td>Вывод</td>
    <td>стандартный вывод или output.txt</td>
  </tr>
</table>

В дощечке в один ряд вбиты гвоздики. Любые два гвоздика можно соединить ниточкой. Требуется соединить некоторые пары гвоздиков ниточками так, чтобы к каждому гвоздику была привязана хотя бы одна ниточка, а суммарная длина всех ниточек была минимальна.

## Формат ввода

В первой строке входных данных записано число N — количество гвоздиков (2 ≤ N ≤ 100). В следующей строке заданы N чисел — координаты всех гвоздиков (неотрицательные целые числа, не превосходящие 10000).

## Формат вывода

Выведите единственное число — минимальную суммарную длину всех ниточек.

### Пример 1

#### Ввод

```
6
3 13 12 4 14 6
```

#### Вывод

```
5
```

-------------