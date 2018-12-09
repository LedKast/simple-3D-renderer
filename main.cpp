// aka 2DPlotViewer
#include <windows.h>
#include <windowsx.h>
#include <math.h>

//#include "Drawing/Scene2D.h"
#include "Drawing/Scene3D.h"
//#include "Drawing/Model2D.h"
#include "Drawing/Model3D.h"

//#include "Math/Matrix.h"
#include "Math/AffineTransform.h"

#define TRNSPEED 2 	// скорость переноса
#define SCLSPEED 0.2  	// скорость масштабирования
#define RTSPEED 3.14/24 // скорость вращения

// TODO change PATH
#define PROJECTPATH "d:/DOCs/3_course/CGraphics/CG_3D_Scene/"
#define DEFSCALE 50 	//стандартный масштаб сцены
#define WINW 480
#define WINH 320

Scene3D scene(WINW/2, WINH/2, DEFSCALE, DEFSCALE + 50);

//void relativeRotation(double);
//void relativeScaling(double, double);

LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);						// прототип оконной процедуры
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// основнаRя процедура
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
	wc.lpszMenuName = nullptr;							// меню в оконном классе отсутствует
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// имя оконного класса, используемое при создании экземпляров окна
	RegisterClass(&wc);								// регистрация класса wc

	HWND hWnd = CreateWindow(						// hWnd - дескриптор, идентифицирующий окно; функция создания окна заполняет дескриптор hWnd ненулевым значением
		(LPCSTR)"MainWindowClass",					// имя оконного класса
		(LPCSTR)"Simple 2D render",					// заголовок окна
		WS_OVERLAPPEDWINDOW,						// стиль окна
		200,200, WINW + 200, WINH + 200,			// координаты на экране левого верхнего угла окна, его ширина и высота
		nullptr,nullptr,hInstance,nullptr);

    // задаем модель из файла
    scene.addModel(
    		PROJECTPATH "models/3Dmodel1_vert",
    		PROJECTPATH "models/3Dmodel1_faces",
    		PROJECTPATH "models/3Dmodel1_im");

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

LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// оконная процедура принимает и обрабатывает все сообщения, отправленные окну
{
	switch(msg)
	{
		case WM_PAINT:
		{
			HDC dc = GetDC(hWnd);
			scene.Clear(dc);				// вызов реализованного в классе Camera_ метода, отвечающего за очистку рабочей области окна hWnd
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
				/* MODEL MOVE */
				/// USE arrows
				case VK_RIGHT:
					scene.apply(translation3D(TRNSPEED, 0, 0));
					break;
                case VK_LEFT:
                    scene.apply(translation3D(-TRNSPEED, 0, 0));
                    break;
                case VK_UP:
                    scene.apply(translation3D(0, 0, TRNSPEED));
                    break;
                case VK_DOWN:
                    scene.apply(translation3D(0, 0, -TRNSPEED));
                    break;

				/* MODELS CONTROL */
				/// USE [{ - add,  }] - del,  1 - next,  2 - prev
				case VK_OEM_4: 	// [{ key
					scene.addModel(
							PROJECTPATH "models/3Dmodel1_vert",
							PROJECTPATH "models/3Dmodel1_faces",
							PROJECTPATH "models/3Dmodel1_im");
					break;
				case VK_OEM_6: 	// }] key
					scene.removeLastModel();
					break;
				case 0x31: 		// 1 key
					scene.selectPrevModel(); // выбор предыдущей модели
					break;
				case 0x32: 		// 2 key
					scene.selectNextModel(); // выбор следующей
					break;


				/* ROTATION */
				/// USE W A S D
					// A
				case 0x41: // поворот по Y
					scene.apply(rotationY(RTSPEED));
					break;
					// D
				case 0x44: // поворот по Y
					scene.apply(rotationY(-RTSPEED));
					break;
					// W
				case 0x57: // поворот по Х
					scene.apply(rotationX(RTSPEED));
					//relativeRotation(RTSPEED);
					break;
					// S
				case 0x53: // поворот по Х
					scene.apply(rotationX(-RTSPEED));
					//relativeRotation(-RTSPEED);
					break;

				/* MODEL SIZE */
				/// USE + -
				case VK_OEM_PLUS: // изменение размера модели
					//relativeScaling(1,1 + SCLSPEED);
					scene.apply(scaling(1 + SCLSPEED, 1 + SCLSPEED, 1 + SCLSPEED));
					break;

				case VK_OEM_MINUS: // изменение размера модели
					//relativeScaling(1,1 - SCLSPEED);
					scene.apply(scaling(1 - SCLSPEED, 1 - SCLSPEED, 1 - SCLSPEED));
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

            GET_WHEEL_DELTA_WPARAM(wParam) > 0 ?
                scene.incD(4) : scene.decD(4);
            scene.updateCamera();
            scene.apply(identity3D());
			//scene.scale(pt.x, pt.y, GET_WHEEL_DELTA_WPARAM(wParam) > 0);

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


//// составные преобразование 2D
//void relativeRotation(double angle)
//{
//	double currPosX = scene.getModel().getPosX();
//	double currPosY = scene.getModel().getPosY();
//	// составное аффинное преобразование
//	// перемещаем в (0,0), делаем поворот, и возвращаем назад
//	scene.getModel().apply(
//			translation(
//					currPosX,
//					currPosY) *
//			rotation(angle) *
//			translation(
//					-currPosX,
//					-currPosY)
//	);
//}
//void relativeScaling(double x, double y)
//{
//	double currOVecX = scene.getModel().getOVecY();
//	double currOVecY = scene.getModel().getOVecX();
//
//	scene.getModel().apply(
//			rotation(currOVecX, -currOVecY) *
//			scaling(x, y) *
//			rotation(currOVecX, currOVecY)
//	);
//}