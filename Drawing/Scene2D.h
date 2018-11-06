#ifndef SCENE_2D_H
#define SCENE_2D_H

#define _USE_MATH_DEFINES
#include <math.h>

#include "Camera2D.h"

class Scene2D : public Camera2D
{
private:
	typedef double (*Func)(double);
public:
	Scene2D(double X0, double Y0, double px, double py) : Camera2D(X0, Y0, px, py)
	{ }
	void plot(HDC dc, Func f, COLORREF GColor = RED, int GSolid = 2, bool axes = true)
	{
		// Координатные оси
		if (axes)
			Axes(dc);

		// Построение графика функции f
		HPEN pen = (HPEN)WIN32::SelectObject(dc, WIN32::CreatePen(PS_SOLID, GSolid, GColor)); // устанавливаем цвет из параметра
		MoveTo(L(),f(L())); // устанавливаем начальную точку отрисовки
		for (int p = 1; p < W; p+=8) // пиксель по X
			LineTo(dc, ScreenToWorldX(p), f(ScreenToWorldX(p))); // отрисовываем линию между предыдущей и след точкой
		DeleteObject(SelectObject(dc, pen));
	}

	void polarPlot(HDC dc, Func f, COLORREF GColor = RED, int GSolid = 2, bool axes = true)
	{
		if (axes)
			polarAxes(dc);

		const double step = 1/px; // шаг для phi 0.00390625
		HPEN pen = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, GSolid, GColor)); // устанавливаем цвет из параметра
		MoveTo(f(0)*cos(0), f(0)*sin(0)); // устанавливаем начальную точку отрисовки
		for (double phi = step; phi <= 2*M_PI; phi += step) // задаем phi
			LineTo(dc, f(phi)*cos(phi), f(phi)*sin(phi)); // отрисовываем линию между предыдущей и след точкой
		LineTo(dc, f(2 * M_PI)*cos(2 * M_PI), f(2 * M_PI)*sin(2 * M_PI)); // отрисовываем линию между предыдущей и след точкой
		DeleteObject(SelectObject(dc, pen));
	}
};

#endif // SCENE_2D_H
