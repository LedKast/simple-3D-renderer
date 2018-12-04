#ifndef LAB_3_3D_SCENE_SCENE3D_H
#define LAB_3_3D_SCENE_SCENE3D_H

#include "Camera3D.h"
#include "Model3D.h"


class Scene3D : public Camera3D
{
    Model3D *model;
    int modelcount;
    int currmodel;
public:

    Scene3D(double X0, double Y0, double px, double py) : Camera3D(X0, Y0, px, py)
    {
        model = nullptr;
        modelcount = currmodel = 0;
        // model->project(); //TODO init project
    }

    void render(HDC dc) // TODO change render
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

    void apply() // вызывает apply и project у текущей модели
    {
        // TODO scene apply
    }

    void addModel(Matrix<> &v, const Matrix<int> &f, const Matrix<int> &im) // добавить модель из матрицы
    {
        modelcount++;
        auto *temp = new Model3D[modelcount];
        for (int i = 0; i < modelcount - 1; ++i) // переопределение массива с моделями
            temp[i] = model[i];

        temp[modelcount - 1] = Model3D(v, f, im); // добавляем новую модель
        model = temp;
    }
    void addModel(string v, string f, string im) // добавить модель из файла
    {
        modelcount++;
        auto *temp = new Model3D[modelcount];
        for (int i = 0; i < modelcount - 1; ++i) // переопределение массива с моделями
            temp[i] = model[i];

        temp[modelcount - 1] = Model3D(v, f, im); // добавляем новую модель
        //delete model;
        model = temp;
    }
    void removeLastModel() // удалить последнюю модель
    {
        if (modelcount <= 1 || currmodel == modelcount - 1)
            return;

        modelcount--;
        auto temp = new Model3D[modelcount];
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

    Model3D &getModel()
    {
        return model[currmodel];
    }
};


#endif //LAB_3_3D_SCENE_SCENE3D_H
