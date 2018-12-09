#ifndef LAB_3_3D_SCENE_CAMERA3D_H
#define LAB_3_3D_SCENE_CAMERA3D_H

#include "Camera2D.h"
#include "../Math/Matrix.h"
#include "../Math/vec3D.h"

class Camera3D : public Camera2D
{
protected:
    vec3D<>
            Ov, // координаты точки экранной плоскости (напротив наблюдателя)
            T,  // вертикальный вектор для наблюдателя
            N;  // нормаль

    double D;   // расстояние между экраном и пользователем
    Matrix<> WorldToView,       // 4x4 матрицы перехода
             ViewToProject,     // 3x4
             WorldToProject;    // 3x4

public:
    Camera3D(double X0, double Y0, double px, double py) :
        Camera2D(X0, Y0, px, py), Ov(), T(), N()
    {
        D = 16;
        T(2, 1);

        //Ov(1, 1);
        //Ov(2, 1);

        //N(1, 1);
        //N(2, 1);
        N(3, 1);

        updateCamera();
    }

    // правая колонка S w->v = скалярное произведение Ov и i, j, k по очереди
    /// Вызывается при изменении Ov T N D
    void updateCamera() // обновление матриц перехода.
    {
        // задаем базисные векторы
        vec3D<> k = N * (1.0 / N.norm());
        vec3D<> i = (T.vecprod(N)) * (1.0 / (T.vecprod(N)).norm());
        vec3D<> j = (k.vecprod(i)) * (1.0 / (k.vecprod(i)).norm());

        // обновление S v->p
        double T1[] = {
                1, 0, 0, 0,
                0, 1, 0 ,0,
                0, 0, -(1/D), 1
        };
        ViewToProject = Matrix<>(3, 4, T1);

        // обновление S w->v
        double T2[] = {
            i(1), i(2), i(3), -(Ov.scalarprod(i)),
            j(1), j(2), j(3), -(Ov.scalarprod(j)),
            k(1), k(2), k(3), -(Ov.scalarprod(k)),
            0, 0, 0, 1
        };
        WorldToView = Matrix<>(4, 4, T2);

        // обновление S w->p
        WorldToProject = ViewToProject * WorldToView;
    }

    void setOv(const vec3D<> &Ov) {
        Camera3D::Ov = Ov;
    }
    void setT(const vec3D<> &T) {
        Camera3D::T = T;
    }
    void setN(const vec3D<> &N) {
        Camera3D::N = N;
    }
    void incD(double i) {
        D += i;
    }
    void decD(double i) {
        D -= i;
    }
};


#endif //LAB_3_3D_SCENE_CAMERA3D_H
