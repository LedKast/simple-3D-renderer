#include <windows.h>
#include <windowsx.h>


#include "Data.h"

#include "Drawing/Scene2D.h"
#include "Drawing/Model2D.h"

#include "Math/Matrix.h"
#include "Math/AffineTransform.h"


#define WINW 480
#define WINH 320

LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// прототип оконной процедуры
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// основнаRя процедура
{
	// ѕервая составляющая часть основной процедуры - создание окна: сначала описывается оконный класс wc, затем создаЄтся окно hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// имя оконной процедуры, закрепленной за данным классом
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// идентификатор приложения, содержащий адрес начала выделенной ему области памяти
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;							// меню в оконном классе отсутствует
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// имя оконного класса, используемое при создании экземпляров окна
	RegisterClass(&wc);								// регистрация класса wc

	HWND hWnd = CreateWindow(						// hWnd - дескриптор, идентифицирующий окно; функция создания окна заполняет дескриптор hWnd ненулевым значением
		(LPCSTR)"MainWindowClass",					// имя оконного класса
		(LPCSTR)"Plot2D Viewer",					// заголовок окна
		WS_OVERLAPPEDWINDOW,						// стиль окна
		200,200, WINW + 200, WINH + 200,			// координаты на экране левого верхнего угла окна, его ширина и высота
		nullptr,nullptr,hInstance,nullptr);

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	// ¬торая составляющая часть основной процедуры - основной цикл обработки системных сообщений, который ожидает сообщения и рассылает их соответствующим окнам
	MSG msg;
	while(GetMessage(&msg,nullptr,0,0))				// функция GetMessage выбирает из очереди сообщение и заносит его в структуру msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// функция DispatchMessage оповещает систему о необходимости вызова оконной процедуры
	}

	return 0;
}

// ¬ основном модуле объявляется только одна глобальная переменная - создаЄтся объект класса Scene2D
// ¬се дальнейшие действия осуществляются посредством обращения к методам, реализованным в этом классе
Scene2D scene(WINW/2, WINH/2, DEFSCALE, DEFSCALE + 50);
int plotType = 1;

LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// оконная процедура принимает и обрабатывает все сообщения, отправленные окну
{
	switch(msg)
	{
		case WM_PAINT:
		{
			HDC dc = GetDC(hWnd);
			scene.Clear(dc);				// вызов реализованного в классе Camera2D метода, отвечающего за очистку рабочей области окна hWnd
			if (plotType)
			{
				scene.plot(dc, sinusoid, RED);
				scene.plot(dc, parabola, BLUE);
				scene.plot(dc, test, ORANGE);
			}
			else
			{
				scene.polarPlot(dc, polarCos, BLUE);
				scene.polarPlot(dc, polarRose, ORANGE);
				scene.polarPlot(dc, polarSpiral, RED);
			}
			ReleaseDC(hWnd,dc);
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}

		case WM_SIZE:
		{
			HDC dc = GetDC(hWnd);
			scene.SetResolution(dc);
			ReleaseDC(hWnd,dc);
			InvalidateRect(hWnd,nullptr,false);
			return 0;
		}
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case 0x31: //1 key
				{
					plotType = 1;
					break;
				}
				case 0x32: //2 key
				{
					plotType = 0;
					break;
				}
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			scene.StartDragging(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		}
		case WM_LBUTTONUP:
		{
			scene.StopDragging();
			return 0;
		}
		case WM_MOUSEMOVE:
		{
			if (scene.isDragging)
			{
				scene.drag(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				InvalidateRect(hWnd, nullptr, false);
			}
			break;
		}

		case WM_MOUSEWHEEL:
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(hWnd, &pt);

			int x = GET_X_LPARAM(lParam);
			int y = GET_Y_LPARAM(lParam);
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) //UP
				scene.scale(pt.x, pt.y, true);
			else //DOWN
				scene.scale(pt.x, pt.y, false);

			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		default:
		{
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}
	}
	return 0;
}
