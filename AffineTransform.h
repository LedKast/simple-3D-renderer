#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H

#include <math.h>
#include "Matrix.h"

enum reftype{MAPX, MAPY, MAP00}; // типы отражений

// В приведённом примере используется конструктор матрицы из списка.
// Приветствуются идеи о других способах создания матриц.
// Например, вызов функции, создающей единичную матрицу,
// с последующим переопределением некоторых её коэффициентов.

// Перенос на вектор
Matrix<> translation(double x, double y)
{
	double T[9] = {
		1, 0, x,
		0, 1, y,
		0, 0, 1};
	return Matrix<>(3, T);
}

// identity() - тождественное АП;
Matrix<> identity()
{
    double T[9] = {
            1, 0, 0,
            0, 1, 0,
            0, 0, 1};
    return Matrix<>(3, T);
}

// rotation(t) - поворот на угол t;
Matrix<> rotation(double t)
{
    double T[9] = {
            cos(t), -sin(t), 0,
            sin(t), cos(t), 0,
            0, 0, 1};
    return Matrix<>(3, T);
}

// rotation(c, s) - поворот на угол, косинус и синус которого пропорциональны величинам c и s;
Matrix<> rotation(double c, double s)
{
//    double T[9] = {
//            cos(t), -sin(t), 0,
//            sin(t), cos(t), 0,
//            0, 0, 1};
//    return Matrix<>(3, T);
}

// scaling(kx, ky) - масштабирование;
Matrix<> scaling(double kx, double ky)
{
    double T[9] = {
            kx, 0, 0,
            0, ky, 0,
            0, 0, 1};
    return Matrix<>(3, T);
}

// mapping (различные виды отражений) - по желанию, для создания матриц отражения можно использовать функцию Scaling.
Matrix<> mapping(reftype type)
{
    double T[9]= {
            1, 0, 0,
            0, 1, 0,
            0, 0, 1};
    switch (type)
    {
        case MAPX:
            T[4] = -1;
            break;
        case MAPY:
            T[0] = -1;
            break;
        case MAP00:
            T[0] = T[4] = -1;
            break;
    }

    return Matrix<>(3, T);
}

#endif AFFINE_TRANSFORM_H
