#include <iostream>
#include <cmath>
#include <ctime>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "Temporizador.h"
#include "Result.h"
#include "Euler.h"
#include "RungeKutta.h"
#include "PreditorCorretor.h"

#define K1 2
#define K2 2
#define K3 2

#define M1 2
#define M2 2
#define M3 2

#define B1 0.5
#define F1 2
#define F3 1

#define FORWARD_EULER 1
#define BACKWARD_EULER 2
#define EULER_MODIFY 3
#define RUNGEKUTTA_2ORDEM 4
#define RUNGEKUTTA_3ORDEM 5
#define RUNGEKUTTA_4ORDEM 6

using namespace std;
double dz(double y1,double y2);
double dw(double y1,double y2, double y3,double w,double x);
double dx(double y2,double y3,double w,double x);
