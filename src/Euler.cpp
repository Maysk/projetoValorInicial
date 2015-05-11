#include "../lib/imports.h"
Euler::Euler(double (*dz) (double,double),double (*dw)(double,double,double,double,double),double (*dx)(double ,double ,double ,double ),double y1,double y2 ,double y3,double dy1,double dy2 ,double dy3,double t,double dt){
	this->dz = dz;
	this->dw = dw;
	this->dx = dx;
	this->y1 = y1;
	this->y2 = y2;
	this->y3 = y3;
	this->dy1 = dy1;
	this->dy2 = dy2;
	this->dy3 = dy3;
	this->t = t;
	this->dt = dt;
	this->steps = floor(t/dt);
}

Result Euler::forward(){

	long double executionTimeInSec = 0;

    clock_t executionTime = 0;
    clock_t start;
    clock_t end;
    start = clock();

	Result result(steps+1);
	result.setDeltaT(dt);
	result.setValue(0,0,y1);
	result.setValue(1,0,y2);
	result.setValue(2,0,y3);
	double z[steps+1];
	double w[steps+1];
	double x[steps+1];
	z[0] = dy1;
	w[0] = dy2;
	x[0] = dy3;
	int index = 1;
	double currentStepTime = 0 + dt;
	while(index <= steps){
		double y1k = result.getValue(0,index-1) + dt * z[index - 1];
		z[index] = z[index - 1] + dt * (*dz)(result.getValue(0,index-1),result.getValue(1,index-1));
		result.setValue(0,index,y1k);

		double y2k = result.getValue(1,index-1) + dt * w[index - 1];
		w[index] = w[index - 1] + dt * (*dw)(result.getValue(0,index-1),result.getValue(1,index-1),result.getValue(2,index-1),w[index-1],x[index-1]);
		result.setValue(1,index,y2k);

		double y3k = result.getValue(2,index-1) + dt * x[index - 1];
		x[index] = x[index - 1] + dt * (*dx)(result.getValue(1,index-1),result.getValue(2,index-1),w[index-1],x[index-1]);
		result.setValue(2,index,y3k);

		currentStepTime+=dt;
		result.setIterations(index);
		index++;
	}
	end = clock();
	executionTime = (end - start);
	executionTimeInSec = executionTime/(long double) CLOCKS_PER_SEC;
	result.setTime(executionTimeInSec);
	return result;
}

Result Euler::backward(double error){
	// return iteration(error,multFacForward);
	long double executionTimeInSec = 0;

    clock_t executionTime = 0;
    clock_t start;
    clock_t end;
    start = clock();

	Result result(steps+1);
	result.setDeltaT(dt);
	result.setValue(0,0,y1);
	result.setValue(1,0,y2);
	result.setValue(2,0,y3);

	double z[steps+1];
	double w[steps+1];
	double x[steps+1];
	z[0] = dy1;
	w[0] = dy2;
	x[0] = dy3;

	int index = 1;

	//double currentStepTime = 0 + dt;    //Essa variavel nao esta sendo usada. Por que?

	while(index <= steps){
		double ykn = result.getValue(0,index-1);
		double zkn = z[index-1];
		double ykn1;
		double dif;
		do{
			ykn1 = result.getValue(0, index-1) + dt * zkn;
			zkn = z[index-1] + dt * (*dz)(ykn,result.getValue(1,index-1));
			// cout << zkn << endl;
			dif = fabs(ykn1 - ykn);
			ykn = ykn1;
		}while(dif > error);
		z[index] = zkn;
		result.setValue(0,index,ykn);

		ykn = result.getValue(1,index-1);
		double wkn = w[index-1];
		do{
			ykn1 = result.getValue(1,index-1) + dt * wkn;
			wkn = w[index-1] + dt * (*dw)(result.getValue(0,index-1),ykn,result.getValue(2,index-1),w[index-1],x[index-1]);
			// wkn = w[index-1] + dt * (*dw)(result.getValue(0,index),ykn,result.getValue(2,index-1),w[index-1],x[index-1]);
			dif = fabs(ykn1 - ykn);
			ykn = ykn1;
		}while(dif > error);
		w[index] = wkn;
		result.setValue(1,index,ykn);

		ykn = result.getValue(2,index-1);
		double xkn = x[index-1];
		do{
			ykn1 = result.getValue(2,index-1) + dt * xkn;
			xkn = x[index-1] + dt * (*dx)(result.getValue(1,index-1), ykn, w[index-1], x[index-1]);
			//xkn = x[index-1] + dt * (*dx)(result.getValue(1,index-1),result.getValue(2,index-1),w[index-1],x[index-1]);
			// xkn = x[index-1] + dt * (*dx)(result.getValue(1,index),result.getValue(2,index-1),w[index],x[index-1]);
			dif = fabs(ykn1 - ykn);
			ykn = ykn1;
		}while(dif > error);
		x[index] = xkn;
		result.setValue(2,index,ykn);
		index++;
	}
	end = clock();
	executionTime = (end - start);
	executionTimeInSec = executionTime/(long double) CLOCKS_PER_SEC;
	result.setTime(executionTimeInSec);
	return result;
}

Result Euler::eulerModify(double error){
	// return iteration(error,multFacModify);
    long double executionTimeInSec = 0;

    clock_t executionTime = 0;
    clock_t start;
    clock_t end;
    start = clock();

    int index = 1;

	Result result(steps+1);
	result.setDeltaT(dt);
	result.setValue(0,0,y1);
	result.setValue(1,0,y2);
	result.setValue(2,0,y3);

    double derivadasDeZ[steps+1];
    double derivadasDeW[steps+1];
    double derivadasDeX[steps+1];
	double z[steps+1];
	double w[steps+1];
	double x[steps+1];

	z[0] = dy1;
	w[0] = dy2;
	x[0] = dy3;

	while(index <= steps){
		double ykn = result.getValue(0,index-1);
		double zkn = z[index-1];
		derivadasDeZ[index-1] = (*dz)(result.getValue(0,index-1), result.getValue(1,index-1));

		double ykn1;
		double dif;
		do{
			ykn1 = result.getValue(0,index-1) + (dt/2) * (zkn + z[index-1]);
			zkn = z[index-1] + (dt/2) * ((*dz)(ykn,result.getValue(1,index-1)) + derivadasDeZ[index-1]);
			dif = fabs(ykn1 - ykn);
			ykn = ykn1;
		}while(dif > error);
		z[index] = zkn;
		result.setValue(0,index,ykn);

		ykn = result.getValue(1,index-1);
		double wkn = w[index-1];
		derivadasDeW[index-1] = (*dw)(result.getValue(0,index-1),result.getValue(1,index-1),result.getValue(2,index-1),w[index-1],x[index-1]);
		do{
			ykn1 = result.getValue(1,index-1) + (dt/2) * (wkn + w[index-1]);
			wkn = w[index-1] + (dt/2) * ((*dw)(result.getValue(0,index-1), ykn, result.getValue(2,index-1), w[index-1],x[index-1]) + derivadasDeW[index-1]);
			dif = fabs(ykn1 - ykn);
			ykn = ykn1;
		}while(dif > error);
		w[index] = wkn;
		result.setValue(1,index,ykn);

		ykn = result.getValue(2,index-1);
		double xkn = x[index-1];
		derivadasDeX[index - 1] = (*dx)(result.getValue(1,index-1),result.getValue(2,index-1),w[index-1], x[index-1]);
		do{
			ykn1 = result.getValue(2,index-1) + (dt/2) * (xkn + x[index-1]);
			xkn = x[index-1] + (dt/2) * ((*dx)(result.getValue(1,index-1), ykn, w[index-1], x[index-1]) + derivadasDeX[index-1]);
			dif = fabs(ykn1 - ykn);
			ykn = ykn1;
		}while(dif > error);
		x[index] = xkn;
		result.setValue(2,index,ykn);


		index++;
	}
	end = clock();
	executionTime = (end - start);
	executionTimeInSec = executionTime/(long double) CLOCKS_PER_SEC;
	result.setTime(executionTimeInSec);
	return result;
}


