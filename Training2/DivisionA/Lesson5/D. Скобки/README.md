# D. Скобки

|                     |                                  |
| ------------------- | -------------------------------- |
| Ограничение времени | 1 секунда                        |
| Ограничение памяти  | 64Mb                             |
| Ввод                | стандартный ввод или input.txt   |
| Вывод               | стандартный вывод или output.txt |

Юная программистка Агнесса недавно узнала на уроке информатики об арифметических выражениях. Она заинтересовалась вопросом, что случится, если из арифметического выражения удалить всё, кроме скобок. Введя запрос в своём любимом поисковике, она выяснила, что математики называют последовательности скобок, которые могли бы встречаться в некотором арифметическом выражении, правильными скобочными последовательностями.

Так, последовательность ()(()) является правильной скобочной последовательностью, потому что она может, например, встречаться в выражении (2+2) : (3–(5–2)+4), а последовательности (() и ())( не являются таковыми. Легко видеть, что существует пять правильных скобочных последовательностей, состоящих ровно из шести скобок (по три скобки каждого типа — открывающих и закрывающих): ((())), (()()), (())(), ()(()) и ()()().

Агнесса заинтересовалась простейшими преобразованиями правильных скобочных последовательностей. Для начала Агнесса решила ограничиться добавлением скобок в последовательность. Она очень быстро выяснила, что после добавления одной скобки последовательность перестаёт быть правильной, а вот добавление двух скобок иногда сохраняет свойство правильности. Например, при добавлении двух скобок в различные места последовательности ()() можно получить последовательности (()()), (())(), ()(()) и ()()(). Легко видеть, что при любом способе добавления двух скобок с сохранением свойства правильности одна из новых скобок должна быть открывающей, а другая — закрывающей.

Агнесса хочет подсчитать количество различных способов добавления двух скобок в заданную правильную скобочную последовательность так, чтобы снова получилась правильная скобочная последовательность. К сожалению, выяснилось, что это количество может быть в некоторых случаях очень большим. Агнесса различает способы получения последовательности по позициям добавленных скобок в полученной последовательности. Например, даже при добавлении скобок в простейшую последовательность () можно получить другую правильную скобочную последовательность семью способами: ()(), (()), (()), (()), (()), ()(), ()(). Здесь добавленные скобки выделены жирным шрифтом.

Таким образом, если в полученной последовательности добавленная открывающая скобка стоит в позиции i, а добавленная закрывающая — в позиции j, то два способа, соответствующие парам (i1, j1) и (i2, j2), считаются различными, если i1 = i2 или j1 = j2.

Требуется написать программу, которая по заданной правильной скобочной последовательности определяет количество различных описанных выше способов добавления двух скобок.

### Формат ввода
Входной файл состоит из одной непустой строки, содержащей ровно 2n символов: n открывающих и n закрывающих круглых скобок. Гарантируется, что эта строка является правильной скобочной последовательностью.

### Формат вывода
Выведите в выходной файл количество различных способов добавления в заданную последовательность двух скобок таким образом, чтобы получилась другая правильная скобочная последовательность.

### Пример 1
### Ввод	
() <br>
### Вывод
7 <br>
### Пример 2
### Ввод	
()() <br>
### Вывод
17 <br>
### Пример 3
### Ввод	
(()) <br>
### Вывод
21 <br>