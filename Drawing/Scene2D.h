#ifndef SCENE_2D_H
#define SCENE_2D_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <string>

#include "Camera2D.h"
#include "Model2D.h"

class Scene2D : public Camera2D
{

public:
    Model2D *model;
    // int modelcount;
    // int currmodel;
    // TODO массив моделей. отрисовывать в цикле. переопределять массив с моделями. устанавливать текущую модель selectModel()

	Scene2D(double X0, double Y0, double px, double py) : Camera2D(X0, Y0, px, py)
	{ model = nullptr; }

	void render(HDC dc)
    {
        HPEN pen = (HPEN)WIN32::SelectObject(dc, WIN32::CreatePen(PS_SOLID, 2, ORANGE)); // устанавливаем цвет

        // рассматриваем только верхний треугольник матрицы
        for (int i = 1; i < model->getEdges().getRows(); ++i)
            for (int j = i + 1; j <= model->getEdges().getCols(); ++j)
                if (model->getEdges()(i, j)) // если в верхнетреугольной матрице стоит 1, значит проводим линию
                {
                    MoveTo(model->getVertexX(i), model->getVertexY(i));
                    LineTo(dc, model->getVertexX(j), model->getVertexY(j));
                }

        DeleteObject(SelectObject(dc, pen));
    }

    void setModel(Matrix<> &vert, Matrix<int> &edg) // задать модель/модели из матрицы
    {
	    model = new Model2D(vert, edg);
    }
    void setModel(string vert, string edg) // задать модель/модели из файла
    {
        model = new Model2D(vert, edg);
    }

//	void plot(HDC dc, Func f, COLORREF GColor = RED, int GSolid = 2, bool axes = true)
//	{
//		// Координатные оси
//		if (axes)
//			Axes(dc);
//
//		// Построение графика функции f
//		HPEN pen = (HPEN)WIN32::SelectObject(dc, WIN32::CreatePen(PS_SOLID, GSolid, GColor)); // устанавливаем цвет из параметра
//		MoveTo(L(),f(L())); // устанавливаем начальную точку отрисовки
//		for (int p = 1; p < W; p+=8) // пиксель по X
//			LineTo(dc, ScreenToWorldX(p), f(ScreenToWorldX(p))); // отрисовываем линию между предыдущей и след точкой
//		DeleteObject(SelectObject(dc, pen));
//	}

};

#endif // SCENE_2D_H
