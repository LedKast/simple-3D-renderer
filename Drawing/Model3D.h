#ifndef LAB_3_3D_SCENE_MODEL3D_H
#define LAB_3_3D_SCENE_MODEL3D_H

#include <string>
#include <fstream>
#include "Model2D.h"
#include "../Math/Matrix.h"

class Model3D : public Model2D
{
    Matrix<> vertices;
    Matrix<> initialVertices;
    Matrix<> projectedVertices;
    Matrix<int> faces;
    Matrix<bool> edges;

public:
    Model3D() : Model2D() { }

    // конструктор создания модели по заданным карте вершин и карте граней
    Model3D(const Matrix<> &v, const Matrix<bool> &e) : vertices(v), edges(e) { }

    // конструктор создания модели по именам файлов, в которых лежат карта вершин и карта граней
    Model3D(string v, string f)
    {
        vertices = matrixFromFile<>(v);
        faces = matrixFromFile<int>(f);
    }

    // создание карты рёбер по заданной карте граней
    void setEdges()
    {

    }

    Matrix<> GetVertices() { return vertices; }
    Matrix<int> GetFaces() { return faces; }
    Matrix<bool> GetEdges() { return edges; }

    // получение координат вершины модели с заданным номером
    double GetVertexX(int i) { return vertices(1, i); }
    double GetVertexY(int i) { return vertices(2, i); }
    double GetVertexZ(int i) { return vertices(3, i); }

    void apply(Matrix<> AT) // применение к модели аффинного преобразования, заданного своей матрицей
    {

    }
    void Project(Matrix<> ) // проецирование модели.
    {

    }
};


#endif //LAB_3_3D_SCENE_MODEL3D_H
