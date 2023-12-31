# Matrices

## Описание
Репозиторий состоит из двух частей:
1. Реализация статической библиотеки для работы с матрицами на языке `C++` вместе с покрытием Unit-тестами с помощью `GTest`.

2. Реализация модуля для работы с матрицами на языке `Python` вместе с покрытием Unit-тестами с помощью `Pytest`.

Сборка проекта осуществляется при помощи `Makefile`.


## Выполненные операции

### Реализованные операции над матрицами
| Операция С++   |Операция Python| Описание   | Исключительные ситуации |
| ----------- | ----------- | ----------- |--------- |
| `bool EqMatrix(const Matrix& other)` |`eq_matrix(self, second_matrix: Matrix) -> bool`| Проверяет матрицы на равенство между собой |  |
| `void SumMatrix(const Matrix& other)` |`sum_matrix(self, second_matrix: Matrix) -> None`| Прибавляет вторую матрицы к текущей | различная размерность матриц |
| `void SubMatrix(const Matrix& other)` |`sub_matrix(self, second_matrix: Matrix) -> None`| Вычитает из текущей матрицы другую | различная размерность матриц |
| `void MulNumber(const double num)` |`mul_number(self, number: float) -> None`| Умножает текущую матрицу на число |  |
| `void MulMatrix(const Matrix& other)` |`mul_matrix(self, second_matrix: Matrix) -> None`| Умножает текущую матрицу на вторую | число столбцов первой матрицы не равно числу строк второй матрицы |
| `Matrix Transpose()` |`transpose(self) -> Matrix`| Создает новую транспонированную матрицу из текущей и возвращает ее |  |
| `Matrix CalcComplements()` |`calc_complements(self) -> Matrix`| Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее | матрица не является квадратной |
| `double Determinant()` |`det(self) -> float`| Вычисляет и возвращает определитель текущей матрицы | матрица не является квадратной |
| `Matrix InverseMatrix()` |`inverse_matrix(self) -> Matrix`| Вычисляет и возвращает обратную матрицу | определитель матрицы равен 0 |

### Перегруженные операторы
| Оператор    | Описание   | Исключительные ситуации |
| ----------- | ----------- | ----------- |
| `+`      | Сложение двух матриц  | различная размерность матриц |
| `-`   | Вычитание одной матрицы из другой | различная размерность матриц |
| `*`  | Умножение матриц и умножение матрицы на число | число столбцов первой матрицы не равно числу строк второй матрицы |
| `==`  | Проверка на равенство матриц  | |
| `=`  | Присвоение матрице значений другой матрицы | |
| `+=`  | Присвоение сложения   | различная размерность матриц |
| `-=`  | Присвоение разности  | различная размерность матриц |
| `*=`  | Присвоение умножения  | число столбцов первой матрицы не равно числу строк второй матрицы |
| `(int i, int j) (только для C++)`  | Индексация по элементам матрицы | индекс за пределами матрицы |

### Реализованные конструкторы
| Метод С++   | Метод Python | Описание   |
| ----------- |---------| ----------- |
| `Matrix()` | `__init__(self) -> None` | Базовый конструктор, инициализирующий матрицу [[1]] |  
|`Matrix(int rows, int cols, double** matrix);`|` __init__(self, matrix: List[List[float]]) -> None`| Конструктор, инициализирующий матрицу с готовыми значениями|
| `Matrix(int rows, int cols)` |`__init__(self, rows: int, cols: int) -> None`| Параметризированный конструктор с количеством строк и столбцов, создающий матрицу нулей | 
| `Matrix(const S21Matrix& other)` |`__init__(self, other: Matrix) -> None`| Конструктор копирования |
| `Matrix(S21Matrix&& other)` || Конструктор переноса |


## Build
Программное решение сделано под UNIX-системы. Нужно установить менеджер пакетов pip, python, фреймворк pytest, а также модуль multipledispatch для перегрузки методов. Дополнительно еще нужно установить библиотеку GTest.
```
$ sudo apt -y install python3-pip
$ sudo apt-get install python3-pytest -y
$ pip3 install pytest-cov
$ pip3 install multipledispatch
$ sudo apt install libgtest-dev
```

```
$ git clone https://github.com/Flexxxender/Matrices.git
$ cd Matrices
$ make cpp_build
```

## Tests
Запуск тестов, покрывающих код.
```
$ make coverage        # выполнение всех тестов
$ make python_coverage # отдельное выполнение Python тестов
$ make cpp_coverage    # отдельное выполнение С++ тестов
```

## Report
Отчеты генерируются в папках Matrices_CPP/src/report и Matrices_Python/src/report и имеют назания `index.html`.
```
$ make report        # покрытиe всех тестов в виде html-страницы 
$ make python_report # отчет о покрытии Python с помощью Pytest
$ make cpp_report    # отчет о покрытии C++ с помощью GTest
```

## Time
Запуск отдельных тяжелых тестов с большими вычислениями, чтобы сравнить время выполнения.
```
$ make time        # запуск определенных тестов с таймером
$ make python_time # отдельный подсчет времени для Python тестов
$ make cpp_time    # отдельный подсчет времени для С++ тестов
```

## Clean
Удаление ненужных временных файлов
```
$ make clean      
```