#include "../lib/imports.h"
int main(){
	Euler euler(dz,dw,dx,0,0,0,0,0,0,20,0.01);
	Result result1 = euler.backward(0.1);
	Result  result2 = euler.forward();
	cout << "Backward:\n";
	result1.showFinal();
	cout << "Forward:\n";
	result2.showFinal();
    return 0;
}
double dz(double y1,double y2){
	return 1 - y1 + y2;
}
double dw(double y1,double y2, double y3,double w,double x){
	return	y1 -0.25 * w - 2 * y2 + 0.25 * x + y3;
}
double dx(double y2,double y3,double w,double x){
	return	0.5 + y2 + 0.25 * w - 0.25 * x - 2 *y3;
}