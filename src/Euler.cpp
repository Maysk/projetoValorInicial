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
Result Euler::eulerModify(double error){
	// return iteration(error,multFacModify);
}
Result Euler::iteration(double error,double (*multFac) (double,double)){
	
}
double Euler::multFacForward(double fnk,double fn1){
	return fnk; //f(ynĸ-¹,Tn-¹)
}
double Euler::multFacModify(double fnk,double fn1){
	return (fnk+fn1)/2;
}