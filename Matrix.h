#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;

template <typename Cell = double>
class Matrix;
template <typename Cell>
istream& operator>> (istream& fi, Matrix<Cell>& M);
template <typename Cell>
ostream& operator<< (ostream& fo, const Matrix<Cell>& M);


template <typename Cell>
class Matrix
{
private:
    // rows - строка
    // cols - столбец
	int rows, cols; // матрица размера ROWxCOLUMN
	Cell **cells;
    void AllocateCells(int rows, int cols);    // Выделение памяти
	void FreeCells();               // Очистка
public:
	Matrix() : rows(0), cols(0), cells(nullptr) {}		    // Конструктор по умолчанию
	Matrix(const Matrix&);					                // Конструктор копирования
	explicit Matrix(int rows, int cols);					// Конструктор нулевой матрицы
	explicit Matrix(int rows);					            // Конструктор нулевой квадратной матрицы
	Matrix(int rows, int cols, Cell* list);					// Конструктор матрицы из списка
    Matrix(int rows, Cell* list);                           // Конструктор квадратной матрицы из списка
	~Matrix();								                // Деструктор

	Cell& operator() (int i, int j) { return cells[i-1][j-1]; } // получение элемента матрицы (индексация с 1)
	
	Matrix& operator = (const Matrix&);		// Перегрузка оператора присваивания
	Matrix  operator + (const Matrix&);		// Сложение матриц
	Matrix  operator - (const Matrix&);		// Вычитание матриц
	Matrix  operator * (const Matrix&);		// Умножение матриц

	friend istream& operator >> <Cell> (istream&, Matrix&);			// Перегрузка оператора >> для ввода матрицы
	friend ostream& operator << <Cell> (ostream&, const Matrix&);	// Перегрузка оператора << для вывода матрицы
};

// Конструктор копирования
template <typename Cell>
Matrix<Cell>::Matrix(const Matrix<Cell>& M)
{
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
	{
		for (int i=0; i < rows; i++)
            for (int j=0; j < cols; j++)
                res.cells[i][j] += M.cells[i][j];
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator-(const Matrix& M)
{
    Matrix<Cell> res(*this);
    if (rows == M.rows && cols == M.cols)
    {
        for (int i=0; i < rows; i++)
            for (int j=0; j < cols; j++)
                res.cells[i][j] -= M.cells[i][j];
    }
    return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator*(const Matrix& M)
{
    Matrix<Cell> res(rows, rows);

    if ( rows == M.cols )
        for (int i=0; i < rows; i++)
            for (int j = 0; j < rows; j++)
                for (int k = 0; k < cols; k++)
                    res.cells[i][j] += this->cells[i][k] * M.cells[k][j];
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

#endif MATRIX_H
