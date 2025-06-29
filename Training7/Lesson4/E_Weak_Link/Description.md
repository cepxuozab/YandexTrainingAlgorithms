# E. Слабое звено

В Берляндии по воскресеньям проходит известное шоу — игра «Слабое звено».

В игре принимают участие _n_ игроков, которые выстраиваются в круг. Каждому игроку сопоставлен рейтинг — некоторое целое
число _a<sub>i</sub>_.

Игра проходит в несколько раундов, каждый из которых выглядит следующим образом:

* В очередном раунде принимают участие все ещё не выбывшие игроки.
* Все игроки, которые по рейтингу строго слабее обоих своих соседей по кругу, объявляются слабым звеном и выбывают из
  игры.
* Все оставшиеся участники сдвигаются чуть плотнее, чтобы снова образовывать круг.
* Игра заканчивается, если после очередного раунда осталось ровно два человека или если после очередного раунда не выбыл
  ни один человек.
* Иначе начинается новый раунд.
  Можно показать, что если до очередного раунда в игре оставалось хотя бы три участника, то после одного раунда
  гарантированно останется не менее двух участников.

Вам нужно выяснить для каждого участника, останется ли он до конца, или номер раунда, в котором он покинет игру.

## Формат ввода

В первой строке дано одно целое число _n (2 ≤ n ≤ 200 000)_ — количество участников в игре.

Вторая строка содержит _n_ целых чисел _a<sub>i</sub> (1 ≤ a<sub>i</sub> ≤ 200 000)_ — рейтинги всех участников игры в
том порядке, в котором они стоят, при этом участник с номером _n_ является соседом участника с номером _1_.

## Формат вывода

Выведите _n_ целых чисел — номер раунда, в котором участник игры с номером _i_ покинет игру, или _0_, если этот игрок
останется до конца игры.

Раунды нумеруются последовательными целыми числами, начиная с _1_.

## Пример 1

### Ввод

5
4 5 5 2 3

### Вывод

    3 0 0 1 2 

## Пример 2

### Ввод

5
5 1 3 1 5

### Вывод

    0 1 2 1 0 

## Пример 3

### Ввод

3
6 6 6

### Вывод

    0 0 0 

## Пример 4

### Ввод

4
6 5 5 6

### Вывод

    0 0 0 0 

## Примечания

В первом примере игра проходит следующим образом (при помощи _ обозначаются выбывшие участники):  
`[4;5;5;2;3]→[4;5;5;_;3]→[4;5;5;_;_]→[_;5;5;_;_]`

После этого игра заканчивается, так как осталось ровно два человека.

Во втором примере игра проходит следующим образом:  
`[5;1;3;1;5]→[5;_;3;_;5]→[5;_;_;_;5]`

В третьем и четвертом примере нет ни одного игрока, который был бы одновременно слабее обоих своих соседей, поэтому игра
заканчивается, не успев начаться.