#include <iostream>

#include "Math/Matrix.h"
#include "Math/AffineTransform.h"
#include "Drawing/Model2D.h"

#define PROJECTPATH "d:/DOCs/3_course/CGraphics/Lab_2_2D_Scene/"

using namespace std;

int main()
{
//	double a[6] = {
//	    1, -2, 7,
//        3, 0, 6};
//	Matrix<> A(2, 3, a);
//
//	double b[6] = {
//        2, 2,
//        0, 1,
//        7, 7};
//	Matrix<> B(3, 2, b);
//
//	Matrix<> C = A*B;
//	cout
//		<< endl <<   "A =" << endl << A
//		<< endl <<   "B =" << endl << B
//		<< endl <<   "C =" << endl << C
//		<< endl << "A+B =" << endl << (A+B)
//		<< endl << "A-B =" << endl << (A-B)
//		<< endl << "T(1,2) =" << endl << translation(1, 2);

    //Model2D model1(PROJECTPATH "Model1_vert.txt",PROJECTPATH "Model1_edg.txt");

    double v[6] = {2, 1, 3, 0, 1, 1};
    Matrix<> V(3, 2, v);
    int e[2] = {1, 2};
    Matrix<int> E(1, 2, e);
    Model2D model(V, E);
    cout
            << endl << "Edges:" << endl << model.getEdges()
            << endl << "Vertices before AT:" << endl << model.getVertices();
    model.apply(translation(1, 2));

    cout
            << endl << "Vertices after AT:" << endl << model.getVertices();


	return 0;
}
