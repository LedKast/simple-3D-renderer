#ifndef SCENE_2D_H
#define SCENE_2D_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <string>

#include "Camera2D.h"
#include "Model2D.h"

class Scene2D : public Camera2D
{
    int modelcount;
    int currmodel;
    Model2D *model;
protected:

	Scene2D(double X0, double Y0, double px, double py) : Camera2D(X0, Y0, px, py)
	{
	    model = nullptr;
        modelcount = currmodel = 0;
	}

	void render(HDC dc)
    {
        HPEN pen;

        for (int curr = 0; curr < modelcount; ++curr) // цикл по моделькам
        {
            if (curr == currmodel)
                pen = (HPEN)WIN32::SelectObject(dc, WIN32::CreatePen(PS_SOLID, 2, ORANGE)); // устанавливаем цвет если выбрана текущая модель
            else
                pen = (HPEN)WIN32::SelectObject(dc, WIN32::CreatePen(PS_SOLID, 2, GRAY));

            for (int i = 1; i < model[curr].getEdges().getRows(); ++i) // рассматриваем только верхний треугольник матрицы
                for (int j = i + 1; j <= model[curr].getEdges().getCols(); ++j)
                    if (model[curr].getEdges()(i, j)) // если в верхнетреугольной матрице стоит 1, значит проводим линию
                    {
                        MoveTo(model[curr].getVertexX(i), model[curr].getVertexY(i));
                        LineTo(dc, model[curr].getVertexX(j), model[curr].getVertexY(j));
                    }
            DeleteObject(SelectObject(dc, pen));
        }


    }
public:
    void addModel(Matrix<> &vert, Matrix<bool> &edg) // добавить модель из матрицы
    {
	    modelcount++;
        Model2D *temp = new Model2D[modelcount];
        for (int i = 0; i < modelcount - 1; ++i) // переопределение массива с моделями
            temp[i] = model[i];

        temp[modelcount - 1] = Model2D(vert, edg); // добавляем новую модель
        model = temp;
    }
    void addModel(string vert, string edg) // добавить модель из файла
    {
        modelcount++;
        Model2D *temp = new Model2D[modelcount];
        for (int i = 0; i < modelcount - 1; ++i) // переопределение массива с моделями
            temp[i] = model[i];

        temp[modelcount - 1] = Model2D(vert, edg); // добавляем новую модель
        //delete model;
        model = temp;
    }
    void removeLastModel() // удалить последнюю модель
    {
        if (modelcount <= 1 || currmodel == modelcount - 1)
            return;

        modelcount--;
        Model2D *temp = new Model2D[modelcount];
        for (int i = 0; i < modelcount; ++i) // переопределение массива с моделями
            temp[i] = model[i];

        // возможно вызывать деструктор конкретной модели
        //delete model;
        model = temp;
    }
    void selectModel(int i) // выбрать модель по номеру
    {
        if (i <= modelcount)
            currmodel = i;
        else
            cout << "INVALID_MODEL_NUMBER" << endl;
    }
    void selectNextModel()
    {
        if (currmodel < modelcount - 1)
            currmodel++;
        else
            currmodel = 0;
    }
    void selectPrevModel()
    {
        if (currmodel > 0)
            currmodel--;
        else
            currmodel = modelcount - 1;
    }

    Model2D &getModel()
    {
	    return model[currmodel];
    }
};

#endif // SCENE_2D_H
