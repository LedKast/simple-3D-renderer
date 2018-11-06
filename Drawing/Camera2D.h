#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>
#include <windowsx.h>

#define RED RGB(215, 0, 0)
#define BLUE RGB(0, 215, 215)
#define ORANGE RGB(255, 200, 0)
#define GREEN RGB(0, 215, 72)

class Camera2D
{
private:
	double posX, posY;					// Позиция графического курсора в мировых координатах (для функций MoveTo и LineTo)
	
protected:
	double X0, Y0;						// Экранные координаты начала мировой системы координат (в пикселях)
	double prevX0, prevY0;
	double px, py;						// Единицы масштаба мировой системы координат (в пикселях)
	int W, H;							// Разрешение рабочей области окна

	int WorldToScreenX(double X)		// Переход от мировых координат к экранным (для абсциссы)
	{
		return X0 + px * X;
	}
	int WorldToScreenY(double Y)		// Переход от мировых координат к экранным (для ординаты)
	{
		return Y0 - py * Y;
	}
	double ScreenToWorldX(int X)		// Переход от экранных координат к мировым (для абсциссы)
	{
		return ((double)X - X0 + 0.5) / px;
	}
	double ScreenToWorldY(int Y)		// Переход от экранных координат к мировым (для ординаты)
	{
		return -((double)Y - Y0 + 0.5) / py;
	}
	double L()							// Абсцисса левой границы рабочей области окна (в мировых координатах)
	{
		return ScreenToWorldX(0);
	}
	double R()							// Абсцисса правой границы рабочей области окна (в мировых координатах)
	{
		return ScreenToWorldX(W);
	}
	
public:
	bool isDragging;

	Camera2D(double X0, double Y0, double px, double py) : X0(X0), Y0(Y0), px(px), py(py)
	{
		W = H = 0;
	}

	// Очистка рабочей области окна
	void Clear(HDC dc)
	{
		HPEN pen = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, RGB(0, 0, 0)));
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		SelectObject(dc, GetStockObject(DKGRAY_BRUSH)); // заливка фона
		Rectangle(dc, 0, 0, r.right, r.bottom); //clear
	}

	// Данная процедура вызывается при изменении размеров окна
	// В ней задаются значения величин W, H, а также настраиваются значения параметров 
	// X0, Y0, px, py таким образом, чтобы обеспечить одинаковые масштабы по координатным осям
	void SetResolution(HDC dc)
	{
		if (!W && !H)
		{
			RECT r;
			GetClientRect(WindowFromDC(dc), &r);
			W = r.right;
			H = r.bottom;
		}

		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		double W1 = double(r.right) / W;
		double H1 = double(r.bottom) / H;
		double px1 = px;

		X0 *= W1;
		Y0 = W1 * (px / py) * Y0 + (H / 2) * (H1 - W1 * (px / py));
		px *= W1;
		py = px1 * W1;

		W = r.right;
		H = r.bottom;
	}

	// масштабирование графика по колесику мыши
	void scale(int X, int Y, bool inc)
	{
		double
			k = inc ? 0.1 : -0.1,
			XW = ScreenToWorldX(X),
			YW = ScreenToWorldY(Y);
		X0 -= k*px*XW;
		Y0 += k*py*YW;
		px = (1.0 + k) * px;
		py = (1.0 + k) * py;

	}

	void StartDragging(int X, int Y)
	{
		prevX0 = X;
		prevY0 = Y;
		isDragging = true;
	}

	void StopDragging()
	{
		isDragging = false;
	}

	void drag(int X, int Y)
	{
		X0 += X - prevX0;
		Y0 += Y - prevY0;
		prevX0 = X;
		prevY0 = Y;
	}

	// Перемещение графического курсора (posX, posY)
	// Обратите внимание, что мы действуем в мировых координатах
	void MoveTo(double X, double Y)
	{
		posX = X;
		posY = Y;
	}

	// Отрисовка линии из текущей позиции графического курсора в точку (X, Y) и его перемещение в эту точку
	// Обратите внимание, что мы действуем в мировых координатах
	// При отрисовке линии могут быть использованы WinApi функции
	// ::MoveToEx(dc, Xs, Ys, nullptr) и ::LineTo(dc, Xs, Ys)
	void LineTo(HDC dc, double X, double Y)
	{
		MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), nullptr);
		WIN32::LineTo(dc, WorldToScreenX(X), WorldToScreenY(Y));
		MoveTo(X, Y);
	}

	// Отрисовка координатных осей
	void Axes(HDC dc)
	{
		HPEN pen = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, RGB(180, 180, 180)));
		// вертикальная линия
		MoveToEx(dc, X0, 0, nullptr);
        WIN32::LineTo(dc, X0, H);

		// горизонтальная
		MoveToEx(dc, 0, Y0, nullptr);
        WIN32::LineTo(dc, W, Y0);
		DeleteObject(SelectObject(dc, pen));
	}

	// Отрисовка полярной оси
	void polarAxes(HDC dc)
	{
		HPEN pen = (HPEN)SelectObject(dc, CreatePen(PS_SOLID, 1, RGB(180, 180, 180)));
		MoveToEx(dc, X0, Y0, nullptr);
        WIN32::LineTo(dc, W, Y0);
		DeleteObject(SelectObject(dc, pen));
	}
};

#endif // CAMERA_2D_H
