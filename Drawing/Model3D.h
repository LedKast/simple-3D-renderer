#ifndef LAB_3_3D_SCENE_MODEL3D_H
#define LAB_3_3D_SCENE_MODEL3D_H

#include <string>
#include <fstream>
#include "Model2D.h"
#include "../Math/Matrix.h"

// наследует Model2D
class Model3D : public Model2D
{
    // vertices, cumulativeAT, initVertices, edges - в классе Model2D
    Matrix<> projVertices;
    Matrix<int> faces;
    Matrix<int> imEdges; // мнимые рёбра. матрица 2xM, где М - кол-во мнимых рёбер

    // создание карты рёбер по заданной карте граней
    void setEdges() {
        edges = Matrix<bool>(faces.getRows());
        for (int i = 1; i <= faces.getRows(); ++i)
            for (int j = 1; j <= 2; ++j) {
                edges(faces(i, j), faces(i, j + 1), 1);
                edges(faces(i, j + 1), faces(i, j), 1);
            }
        for (int i = 1; i <= imEdges.getRows(); ++i)
        {
            edges(imEdges(i, 1), imEdges(i, 2), 0);
            edges(imEdges(i, 2), imEdges(i, 1), 0);
        }
    }

public:
    Model3D() : Model2D(), faces(), projVertices(), imEdges() { }

    // конструктор создания модели по заданным карте вершин и карте граней
    Model3D(const Matrix<> &v, const Matrix<int> &f, const Matrix<int> &im) : Model2D(v), faces(f), projVertices(), imEdges(im)
    {
        setEdges();
    }

    // конструктор создания модели по именам файлов, в которых лежат карта вершин и карта граней
    Model3D(string v, string f, string im) : Model2D(v), projVertices(), imEdges()
    {
        faces = matrixFromFile<int>(f);
        imEdges = matrixFromFile<int>(im);
        setEdges();
//        cout << edges; // TODO debug
//        cout << endl;
    }

    Matrix<int> getFaces() { return faces; }
    double getVertexZ(int i) { return vertices(3, i); }

    void project(Matrix<> P) // проецирование модели.
    {
        // TODO projector
    }
};


#endif //LAB_3_3D_SCENE_MODEL3D_H
