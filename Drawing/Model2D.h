#ifndef MODEL2D_H
#define MODEL2D_H

#include <string>
#include <fstream>
#include "../Math/Matrix.h"
#include "../Math/AffineTransform.h"

// Вариант #6
// предполагается, что последняя точка в модели это центр фигуры
// UPD identity заменилось на identity3D
class Model2D
{
protected:
    Matrix<> vertices;      // вершины
    Matrix<> cumulativeAT;  // накопленное аффинное преобразование
    Matrix<> initVertices;  // исходные вершины
    Matrix<bool> edges;      // ребра

    template <typename T = double>
    Matrix<T> matrixFromFile(string file);

public:
    Model2D() : vertices(), edges(), initVertices(), cumulativeAT(identity3D()) {}

    Model2D(Matrix<> vert, Matrix<bool> edg);
    explicit Model2D(Matrix<> vert);

    Model2D(string vert, string edg);
    explicit Model2D(string vert);

    ~Model2D() = default;

    // получение координат X,Y вершины под номером i
    double getVertexX(int i) { return vertices(1, i); }
    double getVertexY(int i) { return vertices(2, i); }
    Matrix<> getVertices() { return vertices; }
    Matrix<bool> getEdges() { return edges; }

    double getPosX() { return vertices(1, vertices.getCols()); }
    double getPosY() { return vertices(2, vertices.getCols()); }

    double getOVecX() { return vertices(1, vertices.getCols()); }
    double getOVecY() { return vertices(2, vertices.getCols()); }

    void apply(Matrix<> AT);
};

template<typename T>
Matrix<T> Model2D::matrixFromFile(string file)
{
    fstream fs(file, ios::in); // входной поток
    if (!fs.is_open()) {
        cout << "CANT_OPEN_FILE::" << file;
        return Matrix<T>(1, 1);
    }

    string temp;
    int rows = 1, cols = 1;
    getline(fs, temp);
    for(char i : temp)
        if (i == ' ')
            cols++;
    while(getline(fs, temp))
        rows++;
    fs.close();

    fs.open(file, ios::in);
    T *list = new T[rows*cols];
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            fs >> list[i*cols + j];

    Matrix<T> mtemp(rows, cols, list);
    delete[] list;
    fs.close();

    return mtemp;
}

Model2D::Model2D(Matrix<> vert, const Matrix<bool> edg) : edges(edg), initVertices(), cumulativeAT(identity3D())
{
    initVertices = vertices = vert;
}
Model2D::Model2D(Matrix<> vert) : edges(), initVertices(), cumulativeAT(identity3D())
{
    initVertices = vertices = vert;
}

Model2D::Model2D(string vert, string edg) : cumulativeAT(identity3D()) // конструктор задания данных из файла
{
    initVertices = vertices = matrixFromFile<>(vert);
    edges = matrixFromFile<bool>(edg);
}
Model2D::Model2D(string vert) : cumulativeAT(identity3D()) // конструктор задания данных из файла
{
    initVertices = vertices = matrixFromFile<>(vert);
}

void Model2D::apply(Matrix<> AT)
{
    cumulativeAT = AT * cumulativeAT;
    vertices = cumulativeAT * initVertices;
}




#endif // MODEL2D_H
