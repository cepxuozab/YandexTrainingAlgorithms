# I. Автоматизированный склад

Склад представляет собой набор одинаковых квадратов, вокруг которых расположены проезды. В углах каждого из квадратов расположены перекрестки, образованные из пересекающихся под прямым углом проездов.

По складу движутся роверы и при проезде перекрестков они руководствуются следующими правилами:

* На перекрестке неравнозначных дорог ровер, движущийся по второстепенной дороге, должен уступить дорогу роверу, приближающимся по главной.
* Если главная дорога на перекрестке меняет направление, роверы, движущиеся по главной дороге, должны руководствоваться между собой правилами проезда перекрестков равнозначных дорог.
* На перекрестке равнозначных дорог ровер обязан уступить дорогу транспортным средствам, приближающимся справа.  

Для тестирования был выбран перекресток, для которого необходимо определить в каком порядке его проедут N роверов, подъезжающих к перекрестку с каждой из четырех сторон в заданные моменты времени. Стороны обозначены номерами 1, 2, 3 и 4, если перечислять по часовой стрелке. Известно, что за единицу времени с каждой из сторон перекрестка приезжает не более одного ровера, а все роверы соблюдают правила и не обгоняют друг-друга. Поскольку это только начало тестирования, все роверы хотят проехать перекресток прямо. Роверы, приближающиеся со сторон
a и b находятся на главной дороге, остальные — на второстепенной. На проезд перекрестка ровер тратит одну единицу времени.

Таким образом, ровер проезжает перекресток только если:

* нет роверов, которые находятся перед этим ровером в очереди к перекрестку,
* нет роверов, которым нужно уступить дорогу   

Если два ровера, стоящие первыми в очереди на проезд перекрестка не должны уступать друг другу дорогу, то они проедут перекресток одновременно.

Определите, в каком порядке роверы проедут перекресток. 

## Формат ввода

Первая строка входного файла содержит одно целое число N (1≤N≤100) — количество роверов. Вторая строка содержит числа a и b — стороны перекрестка, составляющие главную дорогу (1≤a,b≤4, a ≠ b).

Каждая из следующих N строк содержит описание ровера, состоящее из двух целых чисел d<sub>i</sub> и t<sub>i</sub> ( 1 &le; d<sub>i</sub> &le; 4, 1 &le; t<sub>i</sub> &le; 100)
— направление и время приезда i-ого ровера.

## Формат вывода

В выходной файл выведите N целых чисел по одному на строке. i-ая строка должна содержать время, в которое i-ый ровер проедет перекресток.

Роверы занумерованы в порядке появления во входном файле.  

## Пример 1

### Ввод
```c++
4
1 3
1 1
3 1
2 1
2 2
```

### Вывод
```c++
1
1
2
3
```

## Пример 2

### Ввод
```c++
4
1 2
1 1
2 1
3 1
4 1
```

### Вывод
```c++
1
2
3
4
```

## Пример 3

### Ввод
```c++
1
1 4
1 1
```

### Вывод
```c++
1
```