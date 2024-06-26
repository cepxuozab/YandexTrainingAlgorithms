# D. Слоны и ладьи

На шахматной доске стоят слоны и ладьи, необходимо посчитать, сколько клеток не бьется ни одной из фигур.

Ладья бьет все клетки горизонтали и вертикали, проходящих через клетку, где она стоит, до первой встретившейся фигуры.
Слон бьет все клетки обеих диагоналей, проходящих через клетку, где он стоит, до первой встретившейся фигуры.

Шахматная доска имеет размеры 8 на 8. 

## Input  
В первых восьми строках ввода описывается шахматная доска. Первые восемь символов каждой из этих строк описывают состояние соответствующей горизонтали: символ B (заглавная латинская буква) означает, что в клетке стоит слон, символ R — ладья, символ * — что клетка пуста. После описания горизонтали в строке могут идти пробелы, однако длина каждой строки не превышает 250 символов. После описания доски в файле могут быть пустые строки.
 
## Output
Выведите количество пустых клеток, которые не бьются ни одной из фигур.

## Example1
<font color="blue">**Ввод:**</font>
```c++
********
********
*R******
********
********
********
********
********
```
<font color="blue">**Вывод:**</font>
```c++
49
``` 

## Example2
<font color="blue">**Ввод:**</font> 
```c++
********
********
******B*
********
********
********
********
********
```
<font color="blue">**Вывод:**</font>
```c++
54
```  

## Example3
<font color="blue">**Ввод:**</font>
```c++
********
*R******
********
*****B**
********
********
********
********
```
<font color="blue">**Вывод:**</font>
```c++
40
```   
