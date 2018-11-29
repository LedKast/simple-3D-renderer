#ifndef MODEL2D_H
#define MODEL2D_H

#include <string>
#include <fstream>
#include "../Math/Matrix.h"
#include "../Math/AffineTransform.h"

/*
 *      в матрице смежности размера M на M, состоящей из нулей и единиц,
 *  – при этом на пересечении i-ой строки и j-ого столбца стоит единица,
 *  если i-ая и j-ая вершины соединены ребром.
 *
 *      Кроме того, необходимо реализовать метод Apply(Matrix AT)
 *  применения к модели аффинного преобразования, заданного матрицей AT.
 *  В памяти должна храниться исходная матрица вершин модели и накопленное аффинное преобразование.
 * */

// Вариант #6
// предполагается, что последняя точка в модели это центр фигуры
class Model2D
{
    Matrix<> vertices;      // вершины
    Matrix<> cumulativeAT;  // накопленное аффинное преобразование
    Matrix<> initVertices;  // исходные вершины

    Matrix<bool> edges;      // ребра

protected:
    template <typename T = double>
    Matrix<T> matrixFromFile(string file);

public:
    Model2D() : vertices(), edges(), initVertices(), cumulativeAT(identity()) {}
    Model2D(Matrix<> vert, const Matrix<bool> edg);
    Model2D(string vert, string edg);
    ~Model2D() = default;

    // получение координат X,Y вершины под номером i
    double getVertexX(int i) { return vertices(1, i); }
    double getVertexY(int i) { return vertices(2, i); }
    Matrix<> getVertices() { return vertices; }
    Matrix<bool> getEdges() { return edges; }

    double getPosX() { return vertices(1, vertices.getCols()); }
    double getPosY() { return vertices(2, vertices.getCols()); }

    double getOVecX() { return vertices(1, 1) - vertices(1, vertices.getCols()); }
    double getOVecY() { return vertices(2, 1) - vertices(2, vertices.getCols()); }

    virtual void apply(Matrix<> AT);
};

template<typename T>
Matrix<T> Model2D::matrixFromFile(string file) {
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

Model2D::Model2D(Matrix<> vert, const Matrix<bool> edg) : edges(edg), initVertices(), cumulativeAT(identity())
{
    // перемещаем центр фигуры в начало координат
    vertices = vert;
    initVertices = vertices =
            translation(
                    -vertices(1, vertices.getCols()),
                    -vertices(2, vertices.getCols())
            ) *
            vertices;
}

Model2D::Model2D(string vert, string edg) // конструктор задания данных из файла
{
    cumulativeAT = identity();
    vertices = matrixFromFile<>(vert);

    // перемещаем центр фигуры в начало координат
    initVertices = vertices =
            translation(
                    -vertices(1, vertices.getCols()),
                    -vertices(2, vertices.getCols())
            ) *
            vertices;

    edges = matrixFromFile<bool>(edg);

//    cout << "VERTICES: \n" << vertices; // DEBUG
//    cout << "EDGES: \n" << edges; // DEBUG
}

void Model2D::apply(Matrix<> AT) {
    cumulativeAT = AT * cumulativeAT;
    vertices = cumulativeAT * initVertices;
}


#endif // MODEL2D_H
