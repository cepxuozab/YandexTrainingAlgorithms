# 16. Очередь с защитой от ошибок

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

Научитесь пользоваться стандартной структурой данных `queue` для целых чисел. Напишите программу, содержащую описание очереди и моделирующую работу очереди, реализовав все указанные здесь методы. 

Программа считывает последовательность команд и в зависимости от команды выполняет ту или иную операцию. После выполнения каждой команды программа должна вывести одну строчку.

Возможные команды для программы:

```
push n
Добавить в очередь число n (значение n задается после команды). Программа должна вывести ok.
```

```
pop
Удалить из очереди первый элемент. Программа должна вывести его значение.
```

```
front
Программа должна вывести значение первого элемента, не удаляя его из очереди.
```

```
size
Программа должна вывести количество элементов в очереди.
```

```
clear
Программа должна очистить очередь и вывести ok.
```

```
exit
Программа должна вывести bye и завершить работу.
```

Перед исполнением операций `front` и `pop` программа должна проверять, содержится ли в очереди хотя бы один элемент. Если во входных данных встречается операция `front` или `pop`, и при этом очередь пуста, то программа должна вместо числового значения вывести строку `error`.

## Формат ввода

Вводятся команды управления очередью, по одной на строке

## Формат вывода

Требуется вывести протокол работы очереди, по одному сообщению на строке

### Пример 1

#### Ввод

```
push 1
front
exit
```

#### Вывод

```
ok
1
bye
```

### Пример 2

#### Ввод

```
size
push 1
size
push 2
size
push 3
size
exit
```

#### Вывод

```
0
ok
1
ok
2
ok
3
bye
```

### Пример 3

#### Ввод

```
push 3
push 14
size
clear
push 1
front
push 2
front
pop
size
pop
size
exit
```

#### Вывод

```
ok
ok
2
ok
ok
1
ok
1
1
1
2
0
bye
```

-------------

# 17. Игра в пьяницу

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

В игре в пьяницу карточная колода раздается поровну двум игрокам. Далее они вскрывают по одной верхней карте, и тот, чья карта старше, забирает себе обе вскрытые карты, которые кладутся под низ его колоды. Тот, кто остается без карт – проигрывает. Для простоты будем считать, что все карты различны по номиналу, а также, что самая младшая карта побеждает самую старшую карту ("шестерка берет туза"). Игрок, который забирает себе карты, сначала кладет под низ своей колоды карту первого игрока, затем карту второго игрока (то есть карта второго игрока оказывается внизу колоды). Напишите программу, которая моделирует игру в пьяницу и определяет, кто выигрывает. В игре участвует 10 карт, имеющих значения от 0 до 9, большая карта побеждает меньшую, карта со значением 0 побеждает карту 9.

## Формат ввода

Программа получает на вход две строки: первая строка содержит 5 чисел, разделенных пробелами — номера карт первого игрока, вторая – аналогично 5 карт второго игрока. Карты перечислены сверху вниз, то есть каждая строка начинается с той карты, которая будет открыта первой.

## Формат вывода

Программа должна определить, кто выигрывает при данной раздаче, и вывести слово `first` или `second`, после чего вывести количество ходов, сделанных до выигрыша. Если на протяжении 10<sup>6</sup> ходов игра не заканчивается, программа должна вывести слово `botva`.

### Пример 1

#### Ввод

```
1 3 5 7 9
2 4 6 8 0
```

#### Вывод

```
second 5
```

### Пример 2

#### Ввод

```
2 4 6 8 0
1 3 5 7 9
```

#### Вывод

```
first 5
```

### Пример 3

#### Ввод

```
1 7 3 9 4
5 8 0 2 6
```

#### Вывод

```
second 23
```

-------------

# 18. Дек с защитой от ошибок

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

Научитесь пользоваться стандартной структурой данных `deque` для целых чисел.  Напишите программу, содержащую описание дека и моделирующую работу дека, реализовав все указанные здесь методы. Программа считывает последовательность команд и в зависимости от команды выполняет ту или иную операцию. После выполнения каждой команды программа должна вывести одну строчку.

Возможные команды для программы:

```
push_front n
Добавить (положить) в начало дека новый элемент. Программа должна вывести ok.
```

```
push_back n
Добавить (положить) в конец дека новый элемент. Программа должна вывести ok.
```

```
pop_front
Извлечь из дека первый элемент. Программа должна вывести его значение.
```

```
pop_back
Извлечь из дека последний элемент. Программа должна вывести его значение.
```

```
front
Узнать значение первого элемента (не удаляя его). Программа должна вывести его значение.
```

```
back
Узнать значение последнего элемента (не удаляя его). Программа должна вывести его значение.
```

```
size
Вывести количество элементов в деке.
```

```
clear
Очистить дек (удалить из него все элементы) и вывести ok.
```

```
exit
Программа должна вывести bye и завершить работу.
```

Гарантируется, что количество элементов в деке в любой момент не превосходит 100. Перед исполнением операций `pop_front`, `pop_back`, `front`, `back` программа должна проверять, содержится ли в деке хотя бы один элемент. Если во входных данных встречается операция `pop_front`, `pop_back`, `front`, `back`, и при этом дек пуст, то программа должна вместо числового значения вывести строку `error`.

## Формат ввода

Вводятся команды управления деком, по одной на строке.

## Формат вывода

Требуется вывести протокол работы дека, по одному сообщению на строке

### Пример 1

#### Ввод

```
push_back 1
back
exit
```

#### Вывод

```
ok
1
bye
```

### Пример 2

#### Ввод

```
size
push_back 1
size
push_back 2
size
push_front 3
size
exit
```

#### Вывод

```
0
ok
1
ok
2
ok
3
bye
```

### Пример 3

#### Ввод

```
push_back 3
push_front 14
size
clear
push_front 1
back
push_back 2
front
pop_back
size
pop_front
size
exit
```

#### Вывод

```
ok
ok
2
ok
ok
1
ok
1
2
1
1
0
bye
```

-------------

# 19. Хипуй

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

В этой задаче вам необходимо самостоятельно (не используя соответствующие классы и функции стандартной библиотеки) организовать структуру данных `Heap` для хранения целых чисел, над которой определены следующие операции:

```a) Insert(k) – добавить в Heap число k ;```

```b) Extract достать из Heap наибольшее число (удалив его при этом).```

## Формат ввода

В первой строке содержится количество команд N (1 ≤ N ≤ 100000), далее следуют N команд, каждая в своей строке. Команда может иметь формат: `“0 <число>”` или `“1”`, обозначающий, соответственно, операции `Insert(<число>)` и `Extract`. Гарантируется, что при выполенении команды `Extract` в структуре находится по крайней мере один элемент.

## Формат вывода

Для каждой команды извлечения необходимо отдельной строкой вывести число, полученное при выполнении команды `Extract`.

### Пример 1

#### Ввод

```
2
0 10000
1
```

#### Вывод

```
10000
```

### Пример 2

#### Ввод

```
14
0 1
0 345
1
0 4346
1
0 2435
1
0 235
0 5
0 365
1
1
1
1
```

#### Вывод

```
345
4346
2435
365
235
5
1
```

-------------

# 20. Пирамидальная сортировка

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

Отсортируйте данный массив. Используйте пирамидальную сортировку.

## Формат ввода

Первая строка входных данных содержит количество элементов в массиве N, N ≤ 10<sup>5</sup>. Далее задаются N целых чисел, не превосходящих по абсолютной величине 10<sup>9</sup>.

## Формат вывода

Выведите эти числа в порядке неубывания.

### Пример 1

#### Ввод

```
1
1
```

#### Вывод

```
1
```

### Пример 2

#### Ввод

```
2
3 1
```

#### Вывод

```
1 3
```

-------------