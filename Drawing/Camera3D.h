#ifndef LAB_3_3D_SCENE_CAMERA3D_H
#define LAB_3_3D_SCENE_CAMERA3D_H

#include "Camera2D.h"
#include "../Math/Matrix.h"
#include "../Math/vec3D.h"

class Camera3D : public Camera2D
{
    vec3D<>
            Ov, // координаты точки экранной плоскости (напротив наблюдателя)
            T,  // вертикальный вектор для наблюдателя
            N;  // нормаль
    double D;   // расстояние между экраном и пользователем
    Matrix<> WorldToView,   // матрицы перехода
             ViewToProject,
             WorldToProject;

public:
    Camera3D(double X0, double Y0, double px, double py) :
        Camera2D(X0, Y0, px, py), Ov(), T(), N()
    {
        D = 16;
        T(1, 2, 1);
        N(1, 3, 1);
    }

    void updateCamera() // обновление матриц перехода
    {
        // TODO обновление матриц перехода

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
    void setD(double D) {
        Camera3D::D = D;
    }
};


#endif //LAB_3_3D_SCENE_CAMERA3D_H
