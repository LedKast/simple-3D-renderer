//
// Created by Alex on 01.12.2018.
//

#ifndef LAB_3_3D_SCENE_CAMERA3D_H
#define LAB_3_3D_SCENE_CAMERA3D_H

#include "Camera2D.h"
#include "../Math/Matrix.h"

class Camera3D : public Camera2D
{
    vec3D Ov, T, N;
public:


private:
    double D;
    Matrix<> WorldToView,
             ViewToProject,
             WorldToProject;

public:
    Camera3D() : Camera2D()
    {

    }

    void updateCamera() // обновление матриц перехода
    {

    }

    void setOv(const vec3D &Ov) {
        Camera3D::Ov = Ov;
    }
    void setT(const vec3D &T) {
        Camera3D::T = T;
    }
    void setN(const vec3D &N) {
        Camera3D::N = N;
    }
    void setD(double D) {
        Camera3D::D = D;
    }
    void setWorldToView(const Matrix<> &WorldToView) {
        Camera3D::WorldToView = WorldToView;
    }
    void setViewToProject(const Matrix<> &ViewToProject) {
        Camera3D::ViewToProject = ViewToProject;
    }
    void setWorldToProject(const Matrix<> &WorldToProject) {
        Camera3D::WorldToProject = WorldToProject;
    }
};


#endif //LAB_3_3D_SCENE_CAMERA3D_H
