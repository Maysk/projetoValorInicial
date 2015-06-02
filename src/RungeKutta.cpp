#include "../lib/imports.h"

RungeKutta::RungeKutta(double (*dz)(double,double),double (*dw)(double,double,double,double,double),double (*dx)(double ,double ,double ,double ),double y1,double y2 ,double y3,double dy1,double dy2 ,double dy3,double t,double dt){
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

Result RungeKutta::rkSegundaOrdem(){
	// return iteration(error,multFacForward);
	Temporizador temporizador;
	temporizador.iniciarTemporizador();

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

    double k1 = 0;
    double k2 = 0;
    double l1 = 0;
    double l2 = 0;
    double resultado = 0;

    double valorDeY1DaRodada;
    double valorDeY2DaRodada;
    double valorDeY3DaRodada;

	while(index <= steps){
        valorDeY1DaRodada = result.getValue(0, index-1);
        valorDeY2DaRodada = result.getValue(1, index-1);
        valorDeY3DaRodada = result.getValue(2, index-1);

//y1

        k1 = dt * z[index-1];
        l1 = dt * (*dz)(valorDeY1DaRodada, valorDeY2DaRodada);
        k2 = dt * (z[index-1] + l1);
        l2 = dt * (*dz)(valorDeY1DaRodada + k1, valorDeY2DaRodada);

        resultado = z[index-1] + (l1 + l2)/2;
        z[index] = resultado;

        resultado = valorDeY1DaRodada + (k1 + k2)/2;
        result.setValue(0,index,resultado);


//y2
        k1 = dt * w[index-1];
        l1 = dt * (*dw)(valorDeY1DaRodada, valorDeY2DaRodada, valorDeY3DaRodada, w[index-1], x[index-1]);
        k2 = dt * (w[index-1] + l1);
        l2 = dt * (*dw)(valorDeY1DaRodada, valorDeY2DaRodada + k1, valorDeY3DaRodada, w[index-1] + l1, x[index-1]);

        resultado = w[index-1] + (l1 + l2)/2;
        w[index] = resultado;

        resultado = valorDeY2DaRodada + (k1 + k2)/2;
        result.setValue(1, index, resultado);

//y3

        k1 = dt * x[index-1];
        l1 = dt * (*dx)(valorDeY2DaRodada, valorDeY3DaRodada, w[index-1], x[index-1]);
        k2 = dt * (x[index-1] + l1);
        l2 = dt * (*dx)(valorDeY2DaRodada, valorDeY3DaRodada + k1, w[index-1], x[index-1] + l1);

        resultado = x[index-1] + (l1 + l2)/2;
        x[index] = resultado;

        resultado = valorDeY3DaRodada + (k1 + k2)/2;
        result.setValue(2,index,resultado);



		index++;
	}


	result.setTime(temporizador.getTimeInSec());
	return result;
}

Result RungeKutta::rkTerceiraOrdem(){

    Temporizador temporizador;
    temporizador.iniciarTemporizador();

    Result result(steps+1);
    result.setValue(0,0,y1);
	result.setValue(1,0,y2);
	result.setValue(2,0,y3);

    double z[steps+1];
	double w[steps+1];
	double x[steps+1];
	z[0] = dy1;
	w[0] = dy2;
	x[0] = dy3;

    double k1 = 0;
    double k2 = 0;
    double k3 = 0;
    double l1 = 0;
    double l2 = 0;
    double l3 = 0;
    double resultado = 0;


    double valorDeY1DaRodadaAnterior;
    double valorDeY2DaRodadaAnterior;
    double valorDeY3DaRodadaAnterior;

    for(int index = 1 ; index <= steps ; index++){
        valorDeY1DaRodadaAnterior = result.getValue(0, index-1);
        valorDeY2DaRodadaAnterior = result.getValue(1, index-1);
        valorDeY3DaRodadaAnterior = result.getValue(2, index-1);

        //y1:
        k1 = dt * z[index-1];
        l1 = dt * (*dz)(valorDeY1DaRodadaAnterior,valorDeY2DaRodadaAnterior);

        k2 = dt * (z[index-1] + l1/2);
        l2 = dt * (*dz)(valorDeY1DaRodadaAnterior+k1/2,valorDeY2DaRodadaAnterior);

        k3 = dt * (z[index-1] - l1 + 2*l2);
        l3 = dt * (*dz)(valorDeY1DaRodadaAnterior-k1+2*k2,valorDeY2DaRodadaAnterior);

        resultado = z[index-1] + (l1+4*l2+l3)/6;
        z[index] = resultado;

        resultado = valorDeY1DaRodadaAnterior + (k1+4*k2+k3)/6;
        result.setValue(0,index,resultado);

        //y2:
        k1 = dt * w[index-1];
        l1 = dt * (*dw)(valorDeY1DaRodadaAnterior,valorDeY2DaRodadaAnterior,valorDeY3DaRodadaAnterior,w[index-1],x[index-1]);

        k2 = dt * (w[index-1] + l1/2);
        l2 = dt * (*dw)(valorDeY1DaRodadaAnterior,valorDeY2DaRodadaAnterior+k1/2,valorDeY3DaRodadaAnterior,w[index-1]+l1/2,x[index-1]);

        k3 = dt * (w[index-1] - l1 + 2*l2);
        l3 = dt * (*dw)(valorDeY1DaRodadaAnterior,valorDeY2DaRodadaAnterior-k1+2*k2,valorDeY3DaRodadaAnterior,w[index-1]-l1+2*l2,x[index-1]);

        resultado = w[index-1] + (l1+4*l2+l3)/6;
        w[index] = resultado;

        resultado = valorDeY2DaRodadaAnterior + (k1+4*k2+k3)/6;
        result.setValue(1,index,resultado);

        //y3:
        k1 = dt * x[index-1];
        l1 = dt * (*dx)(valorDeY2DaRodadaAnterior,valorDeY3DaRodadaAnterior,w[index-1],x[index-1]);

        k2 = dt * (x[index-1] + l1/2);
        l2 = dt * (*dx)(valorDeY2DaRodadaAnterior,valorDeY3DaRodadaAnterior+k1/2,w[index-1],x[index-1]+l1/2);

        k3 = dt * (x[index-1] - l1 + 2*l2);
        l3 = dt * (*dx)(valorDeY2DaRodadaAnterior,valorDeY3DaRodadaAnterior-k1+2*k2,w[index-1],x[index-1]-l1+2*l2);

        resultado = x[index-1] + (l1+4*l2+l3)/6;
        x[index] = resultado;

        resultado = valorDeY3DaRodadaAnterior + (k1+4*k2+k3)/6;
        result.setValue(2,index,resultado);


    }


	result.setTime(temporizador.getTimeInSec());
	return result;
}


Result RungeKutta::rkQuartaOrdem(){

    Temporizador temporizador;
    temporizador.iniciarTemporizador();

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

    double k1 = 0;
    double k2 = 0;
    double k3 = 0;
    double k4 = 0;
    double l1 = 0;
    double l2 = 0;
    double l3 = 0;
    double l4 = 0;
    double resultado = 0;

    double valorDeY1DaRodadaAnterior;
    double valorDeY2DaRodadaAnterior;
    double valorDeY3DaRodadaAnterior;

    for(int index = 1 ; index <= steps ; index++){
        valorDeY1DaRodadaAnterior = result.getValue(0, index-1);
        valorDeY2DaRodadaAnterior = result.getValue(1, index-1);
        valorDeY3DaRodadaAnterior = result.getValue(2, index-1);


        //y1:
        k1 = dt * z[index-1];
        l1 = dt * (*dz)(valorDeY1DaRodadaAnterior,valorDeY2DaRodadaAnterior);

        k2 = dt * (z[index-1] + l1/3);
        l2 = dt * (*dz)(valorDeY1DaRodadaAnterior+l1/3,valorDeY2DaRodadaAnterior);

        k3 = dt * (z[index-1] + l1/3 + l2/3);
        l3 = dt * (*dz)(valorDeY1DaRodadaAnterior+k1/3+k2/3,valorDeY2DaRodadaAnterior);

        k4 = dt * (z[index-1] + l1 - l2 + l3);
        l4 = dt * (*dz)(valorDeY1DaRodadaAnterior+k1-k2+k3,valorDeY2DaRodadaAnterior);

        resultado = z[index-1] + (l1 + 3*l2 + 3*l3 + l4)/8;
        z[index] = resultado;

        resultado = valorDeY1DaRodadaAnterior + (k1 + 3*k2 + 3*k3 + k4)/8;
        result.setValue(0,index,resultado);


        //y2:
        k1 = dt * w[index-1];
        l1 = dt * (*dw)(valorDeY1DaRodadaAnterior,valorDeY2DaRodadaAnterior,valorDeY3DaRodadaAnterior,w[index-1],x[index-1]);

        k2 = dt * (w[index-1] + l1/3);
        l2 = dt * (*dw)(valorDeY1DaRodadaAnterior,valorDeY2DaRodadaAnterior+k1/3,valorDeY3DaRodadaAnterior,w[index-1]+l1/3,x[index-1]);

        k3 = dt * (w[index-1] + l1/3 + l2/3);
        l3 = dt * (*dw)(valorDeY1DaRodadaAnterior,valorDeY2DaRodadaAnterior+k1/3+k2/3,valorDeY3DaRodadaAnterior,w[index-1]+l1/3+l2/3,x[index-1]);

        k4 = dt * (w[index-1] + l1 - l2 + l3);
        l4 = dt * (*dw)(valorDeY1DaRodadaAnterior,valorDeY2DaRodadaAnterior+k1-k2+k3,valorDeY3DaRodadaAnterior,w[index-1]+l1-l2+l3,x[index-1]);

        resultado = w[index-1] + (l1 + 3*l2 + 3*l3 + l4)/8;
        w[index] = resultado;

        resultado = valorDeY2DaRodadaAnterior + (k1 + 3*k2 + 3*k3 + k4)/8;
        result.setValue(1,index,resultado);

        //y3:
        k1 = dt * x[index-1];
        l1 = dt * (*dx)(valorDeY2DaRodadaAnterior,valorDeY3DaRodadaAnterior,w[index-1],x[index-1]);

        k2 = dt * (x[index-1] + l1/3);
        l2 = dt * (*dx)(valorDeY2DaRodadaAnterior,valorDeY3DaRodadaAnterior+k1/3,w[index-1],x[index-1]+l1/3);

        k3 = dt * (x[index-1] + l1/3 + l2/3);
        l3 = dt * (*dx)(valorDeY2DaRodadaAnterior,valorDeY3DaRodadaAnterior+k1/3+k2/3,w[index-1],x[index-1]+l1/3+l2/3);

        k4 = dt * (x[index-1] + l1 - l2 + l3);
        l4 = dt * (*dx)(valorDeY2DaRodadaAnterior,valorDeY3DaRodadaAnterior+k1-k2+k3,w[index-1],x[index-1]+l1-l2+l3);

        resultado = x[index-1] + (l1 + 3*l2 + 3*l3 + l4)/8;
        x[index] = resultado;

        resultado = valorDeY3DaRodadaAnterior + (k1 + 3*k2 + 3*k3 + k4)/8;
        result.setValue(2,index,resultado);

    }

    result.setTime(temporizador.getTimeInSec());
    return result;
}
