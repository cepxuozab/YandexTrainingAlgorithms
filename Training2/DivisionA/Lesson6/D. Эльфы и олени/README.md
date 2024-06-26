# D. Эльфы и олени

|                     |                                  |
| ------------------- | -------------------------------- |
| Ограничение времени | 1 секунда                        |
| Ограничение памяти  | 64Mb                             |
| Ввод                | стандартный ввод или input.txt   |
| Вывод               | стандартный вывод или output.txt |

Скоро новый год и Санта-Клаус уже начал готовить свою волшебную оленью упряжку, на которой он развозит подарки детям. Известно, что упряжку везут несколько волшебных оленей, на каждом из которых едут два эльфа.

Но волшебные олени – строптивые животные, поэтому не любые два эльфа могут ехать на любом олене. А именно, каждый олень характеризуется некоторой строптивостью ai, а каждый эльф – темпераментом bi. Два эльфа j и k могут ехать на i-м олене в том и только в том случае, если либо bj < ai < bk, либо bk < ai < bj.

Чтобы его появление было максимально зрелищным, Санта-Клаус хочет, чтобы в его упряжке было как можно больше оленей. Про каждого оленя Санта знает его строптивость, а про каждого эльфа – его темперамент.

Помогите Санте выяснить, какое максимальное количество оленей он сможет включить в упряжку, каких оленей ему следует выбрать, и какие эльфы должны на них ехать.

### Формат ввода
В первой строке вводятся два целых числа m и n – количество оленей и эльфов, соответственно (1 ≤ m, n ≤ 100 000).

Вторая строка содержит m целых чисел ai – строптивость оленей (0 ≤ ai ≤ 10^9). В третьей строке записаны n целых чисел bi – темперамент эльфов (0 ≤ bi ≤ 10^9).

### Формат вывода
В первой строке выведите одно число k – максимальное количество оленей, которое Санта-Клаус может включить в свою упряжку. В следующих k строках выведите по три целых числа: di, ei, 1, ei, 2 – для каждого оленя в упряжке выведите его номер и номера эльфов, которые на нем поедут. Если решений несколько, выведите любое.

И эльфы, и олени пронумерованы, начиная с единицы, в том порядке, в котором они заданы во входных данных.

### Пример 1
### Ввод	
4 6 <br>
2 3 4 5 <br>
1 3 2 2 5 2 <br>

### Вывод
2 <br>
1 1 2 <br>
2 4 5 <br>

