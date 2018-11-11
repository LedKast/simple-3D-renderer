// aka 2DPlotViewer
#include <windows.h>
#include <windowsx.h>


#include "Data.h"

#include "Drawing/Scene2D.h"
#include "Drawing/Model2D.h"

#include "Math/Matrix.h"
#include "Math/AffineTransform.h"

#define PROJECTPATH "d:/DOCs/3_course/CGraphics/Lab_2_2D_Scene/"
#define WINW 480
#define WINH 320

Scene2D scene(WINW/2, WINH/2, DEFSCALE, DEFSCALE + 50);

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
		(LPCSTR)"Simple 2D render",					// заголовок окна
		WS_OVERLAPPEDWINDOW,						// стиль окна
		200,200, WINW + 200, WINH + 200,			// координаты на экране левого верхнего угла окна, его ширина и высота
		nullptr,nullptr,hInstance,nullptr);

    // задаем модели из файла
    scene.addModel(PROJECTPATH "model1_vert.txt", PROJECTPATH "model1_edg.txt");

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

LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// оконная процедура принимает и обрабатывает все сообщения, отправленные окну
{
	switch(msg)
	{
		case WM_PAINT:
		{
			HDC dc = GetDC(hWnd);
			scene.Clear(dc);				// вызов реализованного в классе Camera2D метода, отвечающего за очистку рабочей области окна hWnd
            scene.render(dc);

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
			switch (wParam) // перемещение модели
			{
				case VK_RIGHT:
					scene.getModel().apply(translation(0.5, 0));
					break;

                case VK_LEFT:
                    scene.getModel().apply(translation(-0.5, 0));
                    break;

                case VK_UP:
                    scene.getModel().apply(translation(0, 0.5));
                    break;

                case VK_DOWN:
                    scene.getModel().apply(translation(0, -0.5));
                    break;

				case 0x31:
					scene.selectPrevModel(); // выбор предыдущей модели
					break;

				case 0x32:
					scene.selectNextModel(); // выбор следующей
					break;
				case VK_OEM_PLUS: // можно задать любую модель по кнопке +
					scene.addModel(PROJECTPATH "model1_vert.txt", PROJECTPATH "model1_edg.txt");
					break;
				case VK_OEM_MINUS: // удаление последней модели
					scene.removeLastModel();
					break;
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
			scene.scale(pt.x, pt.y, GET_WHEEL_DELTA_WPARAM(wParam) > 0);

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
