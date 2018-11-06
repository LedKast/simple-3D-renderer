#define _USE_MATH_DEFINES
#include <math.h>

#define DEFSCALE 50 //стандартный масштаб графика

double parabola(double x)
{
	return x*x-2;
}

double sinusoid(double x)
{
	return sin(x);
}

double test(double x)
{
	return 1/(x*x);
}

double polarCos(double phi)
{
	return cos(phi);
}

double polarRose(double phi)
{
	return sin(4 * phi);
}

double polarSpiral(double phi)
{
	return 0.125*phi;
}