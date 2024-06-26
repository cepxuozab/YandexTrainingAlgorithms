# E. Имена
|  |  |
|--|--|
|Ограничение времени | 1 секунда |
|Ограничение памяти | 256Mb|
|Ввод | стандартный ввод или input.txt|
|Вывод | стандартный вывод или output.txt|

На далекой планете Тау Кита есть непонятные нам обычаи. Например, таукитяне очень необычно для землян выбирают имена своим детям. Родители так выбирают имя ребенку, чтобы оно могло быть получено как удалением некоторого набора букв из имени отца, так и удалением некоторого набора букв из имени матери. Например, если отца зовут «abacaba», а мать — «bbccaa», то их ребенок может носить имена «a», «bba», «bcaa», но не может носить имена «aaa», «ab» или «bbc». Возможно, что имя ребенка совпадает с именем отца и/или матери, если оно может быть получено из имени другого родителя удалением нескольких (возможно, ни одной) букв.

Пусть отец по имени X и мать по имени Y выбирают имя своему новорожденному ребенку. Так как в таукитянских школах учеников часто вызывают к доске в лексикографическом порядке имен учеников, то есть в порядке следования имен в словаре, то они хотят выбрать своему ребенку такое имя, чтобы оно лексикографически следовало как можно позже.

Формально, строка S лексикографически больше строки T, если выполняется одно из двух условий: строка T получается из S удалением одной или более букв с конца строки S; первые (i - 1) символов строк T и S не различаются, а буква в i-й позиции строки T следует в алфавите раньше буквы в i-й позиции строки S. Требуется написать программу, которая по именам отца и матери находит лексикографически наибольшее имя для их ребенка.

### Формат ввода

Выходной файл должен содержать искомое лексикографически наибольшее из возможных имен ребенка. В случае, если подходящего имени для ребенка не существует, выходной файл должен быть пустым.


### Формат вывода

Выведите одно число – периметр выпиленной фигуры (сторона клетки равна единице).

## Пример 1
## Ввод	
abcabca
abcda


## Вывод
ca

## Пример 2
## Ввод	
ccba
accbbaa

## Вывод
ccba




