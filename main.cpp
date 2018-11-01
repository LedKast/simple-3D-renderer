#include <iostream>

#include "Matrix.h"
#include "AffineTransform.h"

using namespace std;

int main()
{
/*
	Matrix<int> M(2);
	cout << "Input M ->\rows ";
	cin >> M;
*/
	double a[6] = {
	    1, -2, 7,
        3, 0, 6};
	Matrix<> A(2, 3, a);

	double b[6] = {
        2, 2,
        0, 1,
        7, 7};
	Matrix<> B(3, 2, b);

	Matrix<> C = A*B;
	cout
		<< endl <<   "A =" << endl << A
		<< endl <<   "B =" << endl << B
		<< endl <<   "C =" << endl << C
		<< endl << "A+B =" << endl << (A+B)
		<< endl << "A-B =" << endl << (A-B)
		<< endl << "T(1,2) =" << endl << translation(1, 2);

	return 0;
}
