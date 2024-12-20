# H. Переезд в опенспейс

Сотрудники компании работают в старом советском здании, состоящем из n больших кабинетов, расположенных в один ряд, один за другим. В зале
 i работает ровно a<sub>i</sub> сотрудников.

HR-менеджеры компании выяснили, что сотрудникам грустно и одиноко в отдельных кабинетах и, чтобы им стало веселее, необходимо переоборудовать один из кабинетов в модный опенспейс и переселить всех сотрудников в него.

Переезд сотрудника в другой кабинет сопровождается переносом его рабочего стола, что довольно тяжело и времязатратно. При переезде сотрудник перемещает свой стол по всем кабинетам от своего начального положения до кабинета с опенсейсом. Таким образом, количество переходов сотрудника определяется как модуль разности номеров исходного кабинета и кабинета с оборудованным опенспейсом. HR-менеджеры хотят сделать переезд как можно проще и выбрать такой кабинет для оборудования опенспейса, чтобы минимизировать суммарное количество переходов сотрудников (и их рабочих столов). Помогите им определить это количество переходов.



## Формат ввода
В первой строке дано одно натуральное число n — количество кабинетов в офисе (1 &le; n &le; 2 * 10<sup>5</sup>).
Во второй строке содержатся n натуральных чисел a<sub>i</sub> - количество сотрудников в кабинете i (2 &le; a<sub>i</sub> &le; 10<sup>9</sup>).

## Формат вывода

Выведите одно число — минимальное суммарное количество переходов.

## Пример 1

**Ввод**  
```
4
5 2 3 1
```
**Вывод**
```
10
```  

## Пример 2

**Ввод**
```
5
5 4 3 2 1
```
**Вывод**
```
15
```  

