#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <random>
#include <ctime>
#include <cmath>

using namespace std;

template <typename Cell = double>
class Matrix;

template <typename Cell>
istream& operator>> (istream& fi, Matrix<Cell>& M);
template <typename Cell>
ostream& operator<< (ostream& fo, const Matrix<Cell>& M);

// Индексация с 1
// Класс для работы с квадратными и прямоугольными матрицами
template <typename Cell>
class Matrix
{
    // rows - строка
    // cols - столбец
    int rows, cols; // матрица размера ROWxCOLUMN
    Cell **cells;

    static mt19937 gen; // генератор случайных чисел

    void AllocateCells(int rows, int cols);     // Выделение памяти
    void FreeCells();                           // Очистка

    double randomDouble(int left, int right);   // случайное double число из диапазона

public:
    Matrix() : rows(0), cols(0), cells(nullptr){}		    // Конструктор по умолчанию

    Matrix(const Matrix&);					                // Конструктор копирования
    Matrix(int rows, int cols);					            // Конструктор нулевой матрицы
    explicit Matrix(int rows);					            // Конструктор нулевой квадратной матрицы
    Matrix(int rows, int cols, Cell* list);					// Конструктор матрицы из списка
    Matrix(int rows, Cell* list);                           // Конструктор квадратной матрицы из списка
    ~Matrix();								                // Деструктор

    Cell& operator() (int i); // получение значения из вектора
    inline Cell& operator() (int i, int j) { return cells[i-1][j-1]; }             // получение элемента
    inline void operator() (int i, int j, Cell data) { cells[i-1][j-1] = data; }   // установка элемента

    void randomFill(int left, int right); // заполнение случайными числами
    Matrix<Cell> transpose();   // вернет транспонированную матрицу
    double transposeConst();    // транспонирование матрицы
    double norm();              // норма вектора (sum sqrt(x[i]*x[i]))
    void sigInvert();           // инвертирование знака у всех элементов

    operator double();                      // функция приведения к типу double
    Matrix& operator = (const Matrix&);		// Перегрузка оператора присваивания
    Matrix  operator + (const Matrix&);		// Сложение матриц
    Matrix  operator - (const Matrix&);		// Вычитание матриц
    Matrix  operator - (double num);		// Вычитание числа из матрицы
    Matrix  operator * (const Matrix&);		// Умножение матриц
    Matrix  operator * (double num);        // Умножение матрицы на число

    friend istream& operator >> <Cell> (istream&, Matrix&);			// Перегрузка оператора >> для ввода матрицы
    friend ostream& operator << <Cell> (ostream&, const Matrix&);	// Перегрузка оператора << для вывода матрицы
};




// инициализация случайного генератора
template <typename Cell>
mt19937 Matrix<Cell>::gen(static_cast<unsigned long>(time(nullptr)));

// Конструктор копирования
template <typename Cell>
Matrix<Cell>::Matrix(const Matrix<Cell>& M)
{
    //FreeCells();
    AllocateCells(M.rows, M.cols);
    for (int i=0; i < rows; i++)
        for (int j=0; j < cols; j++)
            cells[i][j] = M.cells[i][j];
}

// Конструктор нулевой матрицы
template <typename Cell>
Matrix<Cell>::Matrix(int rows, int cols)
{
    AllocateCells(rows, cols);
    for (int i=0; i < rows; i++)
        for (int j=0; j < cols; j++)
            cells[i][j] = 0;
}

// Конструктор нулевой квадратной матрицы
template <typename Cell>
Matrix<Cell>::Matrix(int rows)
{
    AllocateCells(rows, rows);
    for (int i=0; i < rows; i++)
        for (int j=0; j < rows; j++)
            cells[i][j] = 0;
}

// Конструктор матрицы из списка
template <typename Cell>
Matrix<Cell>::Matrix(int rows, int cols, Cell* list)
{
    AllocateCells(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            cells[i][j] = list[cols*i + j];
}

// Конструктор квадратной матрицы из списка
template <typename Cell>
Matrix<Cell>::Matrix(int rows, Cell* list)
{
    AllocateCells(rows, rows);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < rows; j++)
            cells[i][j] = list[rows*i + j];
}

// Деструктор
template <typename Cell>
Matrix<Cell>::~Matrix()
{
    FreeCells();
}

template <typename Cell>
Matrix<Cell>& Matrix<Cell>::operator=(const Matrix& M)
{
    if (rows != M.rows || cols != M.cols)
    {
        FreeCells();
        AllocateCells(M.rows, M.cols);
    }
    for (int i=0; i<rows; i++)
        for (int j=0; j<cols; j++)
            cells[i][j] = M.cells[i][j];
    return *this;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator+(const Matrix& M)
{
    Matrix<Cell> res(*this);
    if (rows == M.rows && cols == M.cols)
        for (int i=0; i < rows; i++)
            for (int j=0; j < cols; j++)
                res.cells[i][j] += M.cells[i][j];

    return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator-(const Matrix& M)
{
    Matrix<Cell> res(*this);
    if (rows == M.rows && cols == M.cols)
        for (int i=0; i < rows; i++)
            for (int j=0; j < cols; j++)
                res.cells[i][j] -= M.cells[i][j];
    else
    if (M.cols == 1 && M.rows) // если в другой матрице одна ячейка
        return (*this).operator-(M.cells[0][0]);

    return res;
}

template<typename Cell>
Matrix<Cell> Matrix<Cell>::operator-(double num)
{
    Matrix<Cell> res(*this);
    for (int i=0; i < rows; i++)
        for (int j=0; j < cols; j++)
            res.cells[i][j] -= num;

    return res;
}

// UPD global FIX
template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator*(const Matrix& M)
{
    Matrix<Cell> res(rows, M.cols);

    if ( cols == M.rows ) // число столбцов = числу строк у матриц
        for (int i=0; i < rows; i++)
            for (int j = 0; j < M.cols; j++)
                for (int k = 0; k < cols; k++)
                    res.cells[i][j] += this->cells[i][k] * M.cells[k][j];
    else
        if (M.rows == 1 && M.cols == 1) // если в другой матрице одна ячейка
            return (*this).operator*(M.cells[0][0]);

    return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator*(double num)
{
    Matrix<Cell> res(*this);

    for (int i=0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            res.cells[i][j] *= num;
    return res;
}

// Выделение памяти для матрицы
template <typename Cell>
void Matrix<Cell>::AllocateCells(int rows, int cols)
{
    cells = new Cell*[rows];
    for (int i=0; i < rows; i++)
        cells[i] = new Cell[cols];
    this->rows = rows;
    this->cols = cols;
}

// Освобождение памяти
template <typename Cell>
void Matrix<Cell>::FreeCells()
{
    for (int i=0; i < rows; i++)
        delete cells[i];
    delete[] cells;
    rows = cols = 0;
}

// транспонированная матрица
template<typename Cell>
Matrix<Cell> Matrix<Cell>::transpose()
{
    // выделяем память для новой матрицы
    Matrix<Cell> trans(cols, rows);

    // транспонируем
    for (int i = 0; i < cols; ++i)
        for (int j = 0; j < rows; ++j)
            trans.cells[i][j] = cells[j][i];

    return trans;
}

template<typename Cell>
double Matrix<Cell>::transposeConst()
{
    cells = (this->transpose()).cells;

    int temp = rows;
    rows = cols;
    cols = temp;
}

// норма вектора (sqrt(sum x[i]*x[i]))
template<typename Cell>
double Matrix<Cell>::norm()
{
    double norm = 0;
    if (rows == 1)
        for (int i = 0; i < cols; i++)
            norm += cells[0][i]*cells[0][i];
    else
    if (cols == 1)
        for (int i = 0; i < rows; i++)
            norm += cells[i][0]*cells[i][0];

    return sqrt(norm);
}

// Ввод матрицы
template <typename Cell>
istream& operator>> (istream& fi, Matrix<Cell>& M)
{
    for (int i=0; i < M.rows; i++)
        for (int j=0; j < M.cols; j++)
            fi >> M.cells[i][j];
    return fi;
}

// Вывод матрицы
template <typename Cell>
ostream& operator<< (ostream& fo, const Matrix<Cell>& M)
{
    for (int i=0; i < M.rows; i++)
    {
        fo << "  ";
        for (int j=0; j < M.cols; j++)
            fo << M.cells[i][j] << " \t";
        fo << endl;
    }
    return fo;
}

//генерация случайного вещественного числа
template <typename Cell>
double Matrix<Cell>::randomDouble(int left, int right)
{
    double temp;
    do
    {
        uniform_real_distribution<> urd(left, right);
        temp = urd(gen);
    } while (abs(temp) < 0.5); //пропускаем нули
    return temp;
}

// заполнение матрицы случайными числами
template<typename Cell>
void Matrix<Cell>::randomFill(int left, int right)
{
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            cells[i][j] = randomDouble(left, right);
}

template<typename Cell>
inline Cell &Matrix<Cell>::operator()(int i){
    return (rows == 1) ? cells[1][i-1] : cells[i-1][1];
}

template<typename Cell>
Matrix<Cell>::operator double() {
    return (rows == 1 && cols == 1) ? cells[0][0] : 0;
}

template<typename Cell>
void Matrix<Cell>::sigInvert() {
    for (int i=0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            cells[i][j] = -cells[i][j];
}

#endif // MATRIX_H