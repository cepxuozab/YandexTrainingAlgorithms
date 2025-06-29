# G. Острова

Одно разбросанное на островах Океании государство решило создать сеть автомобильных дорог (вернее, мостов). По каждому
мосту можно перемещаться в обе стороны. Был разработан план очередности строительства мостов, и известно, что после
постройки всех мостов можно будет проехать по ним с каждого острова на каждый (возможно, через некоторые промежуточные
острова).

Однако этот момент может наступить до того, как будут построены все мосты. Вам необходимо определить такое минимальное
количество мостов, после строительства которых (в порядке, определенном планом) можно будет попасть с любого острова на
любой другой..

## Формат ввода

Первая строка содержит два числа: число островов _N (1 ≤ N ≤ 10000)_ и количество мостов в плане _M (1 ≤ M ≤ 50000)_.
Далее идёт _M_ строк, каждая содержит два числа _x_ и _y (1 ≤ x,y ≤ N)_ — номера островов, которые соединяет очередной
мост в плане.

## Формат вывода

Программа должна вывести единственное число — минимальное количество построенных мостов, после которого можно будет
попасть с любого острова на любой другой.

## Пример 1

### Ввод

    4 5
    1 2
    1 3
    2 3
    3 4
    4 1

### Вывод

    4