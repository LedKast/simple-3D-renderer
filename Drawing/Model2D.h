#ifndef MODEL2D_H
#define MODEL2D_H

#include <string>
#include "../Math/Matrix.h"

/* Добавьте в класс Model2D следующие конструкторы и методы:
    ◦ Model2D(string, string) – конструктор создания модели по именам
        файлов, в которых лежат карта вершин и карта рёбер;
    ◦ double GetVertexX(int) и double GetVertexY(int) – получение координат
        вершины модели с заданным номером;
    ◦ void Apply(Matrix<>) – применение к модели аффинного преобразова-
        ния, заданного своей матрицей.
 * */

class Model2D
{
    Matrix<> Vertices; // вершины
    Matrix<int> Edges; // ребра

public:
    Model2D() : Vertices(), Edges() {}
    Model2D(const Matrix<> Vertices, const Matrix<int> Edges) : Vertices(Vertices), Edges(Edges) {}
    Matrix<> GetVertices() { return Vertices; }
    Matrix<int> GetEdges() { return Edges; }
};


#endif // MODEL2D_H
