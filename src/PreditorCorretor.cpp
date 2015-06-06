#include "../lib/imports.h"

PreditorCorretor::PreditorCorretor(double (*dz)(double,double),double (*dw)(double,double,double,double,double),double (*dx)(double ,double ,double ,double ),double y1,double y2 ,double y3,double dy1,double dy2 ,double dy3,double t,double dt){
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

Result PreditorCorretor::pcTerceiraOrdem(int metodoUsado){
	Result aux;
	Result result(steps+1);
    result.setDeltaT(dt);

	Temporizador temporizador;
    temporizador.iniciarTemporizador();

    double z[steps+1];
	double w[steps+1];
	double x[steps+1];
	double derivadaZ[steps+1];
	double derivadaW[steps+1];
	double derivadaX[steps+1];
	z[0] = dy1;
	w[0] = dy2;
	x[0] = dy3;

    double preditorZ,preditorW,preditorX,preditorY1,preditorY2,preditorY3;
    double derivadaPreditorZ,derivadaPreditorW,derivadaPreditorX,derivadaPreditorY1,derivadaPreditorY2,derivadaPreditorY3;

    if(metodoUsado == FORWARD_EULER)
        {
            Euler euler(dz,dw,dx,0,0,0,0,0,0,(3*dt),dt);
            aux = euler.forward();
        }
    if(metodoUsado ==  BACKWARD_EULER)
        {
            Euler euler(dz,dw,dx,0,0,0,0,0,0,(3*dt),dt);
            aux = euler.backward(0.01);
        }
    if(metodoUsado ==  EULER_MODIFY)
        {
            Euler euler(dz,dw,dx,0,0,0,0,0,0,(3*dt),dt);
            aux = euler.eulerModify(0.01);
        }
    if(metodoUsado ==  RUNGEKUTTA_2ORDEM)
        {
            RungeKutta rungeKutta(dz,dw,dx,0,0,0,0,0,0,(3*dt),dt);
            aux = rungeKutta.rkSegundaOrdem();
        }
    if(metodoUsado ==  RUNGEKUTTA_3ORDEM)
        {
            RungeKutta rungeKutta(dz,dw,dx,0,0,0,0,0,0,(3*dt),dt);
            aux = rungeKutta.rkTerceiraOrdem();
        }
    if(metodoUsado ==  RUNGEKUTTA_4ORDEM)
        {
            RungeKutta rungeKutta(dz,dw,dx,0,0,0,0,0,0,(3*dt),dt);
            aux = rungeKutta.rkQuartaOrdem();
        }

	for( int i = 0; i < aux.getLength(); i++){
		result.setValue(0,i,aux.getValue(0,i));
		result.setValue(1,i,aux.getValue(1,i));
		result.setValue(2,i,aux.getValue(2,i));
		z[i] = aux.getDerivate(0,i);
		derivadaZ[i] = (*dz)(aux.getValue(0,i),aux.getValue(1,i));
        w[i] = aux.getDerivate(1,i);
        derivadaW[i] = (*dw)(aux.getValue(0,i),aux.getValue(1,i),aux.getValue(2,i),aux.getDerivate(1,i),aux.getValue(2,i));
        x[i] = aux.getDerivate(2,i);
        derivadaX[i] = (*dx)(aux.getValue(1,i),aux.getValue(2,i),aux.getDerivate(1,i),aux.getValue(2,i));
        result.setDerivate(0,i,z[i]);
        result.setDerivate(1,i,w[i]);
        result.setDerivate(2,i,x[i]);
	}

    
	for(int i = 3; i < result.getLength(); i++){
        preditorZ = z[i - 1] + dt * (23 * derivadaZ[i - 1] - 16 * derivadaZ[i - 2] + 5 * derivadaZ[i - 3]) / 12;
        preditorW = w[i - 1] + dt * (23 * derivadaW[i - 1] - 16 * derivadaW[i - 2] + 5 * derivadaW[i - 3]) / 12;
        preditorX = x[i - 1] + dt * (23 * derivadaX[i - 1] - 16 * derivadaX[i - 2] + 5 * derivadaX[i - 3]) / 12;

        preditorY1 = result.getValue(0,i - 1) + dt * (23 * z[i - 1] - 16 * z[i - 2] + 5 * z[i - 3]) / 12;
        preditorY2 = result.getValue(1,i - 1) + dt * (23 * w[i - 1] - 16 * w[i - 2] + 5 * w[i - 3]) / 12;
        preditorY3 = result.getValue(2,i - 1) + dt * (23 * x[i - 1] - 16 * x[i - 2] + 5 * x[i - 3]) / 12;

        derivadaPreditorZ = (*dz)(preditorY1,preditorY2);
        derivadaPreditorW = (*dw)(preditorY1, preditorY2, preditorY3, preditorW, preditorX);
        derivadaPreditorX = (*dx)(preditorY2, preditorY3, preditorW, preditorX);

        z[i] = z[i - 1] + dt * (5 * derivadaPreditorZ + 8 * derivadaZ[i - 1] - derivadaZ[i - 2]) /12;
        w[i] = w[i - 1] + dt * (5 * derivadaPreditorW + 8 * derivadaW[i - 1] - derivadaW[i - 2]) /12;
        x[i] = x[i - 1] + dt * (5 * derivadaPreditorX + 8 * derivadaX[i - 1] - derivadaX[i - 2]) /12;

        derivadaPreditorY1 = z[i];
        derivadaPreditorY2 = w[i];
        derivadaPreditorY3 = x[i];

        result.setValue(0, i, result.getValue(0,i - 1) + dt * (5 * derivadaPreditorY1 + 8 * z[i - 1] - z[i - 2]) / 12);
        result.setValue(1, i, result.getValue(1,i - 1) + dt * (5 * derivadaPreditorY2 + 8 * w[i - 1] - w[i - 2]) / 12);
        result.setValue(2, i, result.getValue(2,i - 1) + dt * (5 * derivadaPreditorY3 + 8 * x[i - 1] - x[i - 2]) / 12);

        derivadaZ[i] = (*dz)(result.getValue(0,i), result.getValue(1,i));
        derivadaW[i] = (*dw)(result.getValue(0,i), result.getValue(1,i), result.getValue(2,i), w[i], x[i]);
        derivadaX[i] = (*dx)(result.getValue(1,i), result.getValue(2,i), w[i], x[i]);

        result.setDerivate(0,i,z[i]);
        result.setDerivate(1,i,w[i]);
        result.setDerivate(2,i,x[i]);
    }
    result.setTime(temporizador.getTimeInSec());
	return result;

}

Result PreditorCorretor::pcQuartaOrdem(int metodoUsado){
	Result aux;
	Result result(steps+1);
    result.setDeltaT(dt);

	Temporizador temporizador;
    temporizador.iniciarTemporizador();

    double z[steps+1];
	double w[steps+1];
	double x[steps+1];
	double derivadaZ[steps+1];
	double derivadaW[steps+1];
	double derivadaX[steps+1];
	z[0] = dy1;
	w[0] = dy2;
	x[0] = dy3;

	double preditorZ,preditorW,preditorX,preditorY1,preditorY2,preditorY3;
    double derivadaPreditorZ,derivadaPreditorW,derivadaPreditorX,derivadaPreditorY1,derivadaPreditorY2,derivadaPreditorY3;

    if(metodoUsado ==  FORWARD_EULER){
        Euler euler(dz,dw,dx,0,0,0,0,0,0,(4*dt),dt);
        aux = euler.forward();
    }

    if(metodoUsado ==  BACKWARD_EULER){
        Euler euler(dz,dw,dx,0,0,0,0,0,0,(4*dt),dt);
        aux = euler.backward(0.01);
    }

    if(metodoUsado ==  EULER_MODIFY){
        Euler euler(dz,dw,dx,0,0,0,0,0,0,(4*dt),dt);
        aux = euler.eulerModify(0.01);
    }

    if(metodoUsado ==  RUNGEKUTTA_2ORDEM){
        RungeKutta rungeKutta(dz,dw,dx,0,0,0,0,0,0,(4*dt),dt);
        aux = rungeKutta.rkSegundaOrdem();
    }

    if(metodoUsado ==  RUNGEKUTTA_3ORDEM){
        RungeKutta rungeKutta(dz,dw,dx,0,0,0,0,0,0,(4*dt),dt);
        aux = rungeKutta.rkTerceiraOrdem();
    }

    if(metodoUsado ==  RUNGEKUTTA_4ORDEM){
        RungeKutta rungeKutta(dz,dw,dx,0,0,0,0,0,0,(4*dt),dt);
        aux = rungeKutta.rkQuartaOrdem();
    }

	for( int i = 0; i < aux.getLength(); i++){
		result.setValue(0,i,aux.getValue(0,i));
		result.setValue(1,i,aux.getValue(1,i));
		result.setValue(2,i,aux.getValue(2,i));
		z[i] = aux.getDerivate(0,i);
		derivadaZ[i] = (*dz)(aux.getValue(0,i),aux.getValue(1,i));
        w[i] = aux.getDerivate(1,i);
        derivadaW[i] = (*dw)(aux.getValue(0,i),aux.getValue(1,i),aux.getValue(2,i),aux.getDerivate(1,i),aux.getValue(2,i));
        x[i] = aux.getDerivate(2,i);
        derivadaX[i] = (*dx)(aux.getValue(1,i),aux.getValue(2,i),aux.getDerivate(1,i),aux.getValue(2,i));
        result.setDerivate(0,i,z[i]);
        result.setDerivate(1,i,w[i]);
        result.setDerivate(2,i,x[i]);
	}

    for(int i = 4; i < result.getLength(); i++){
        preditorZ = z[i - 1] + dt * (55 * derivadaZ[i - 1] - 59 * derivadaZ[i - 2] + 37 * derivadaZ[i - 3] - 9 * derivadaZ[i - 4]) / 24;
        preditorW = w[i - 1] + dt * (55 * derivadaW[i - 1] - 59 * derivadaW[i - 2] + 37 * derivadaW[i - 3] - 9 * derivadaW[i - 4]) / 24;
        preditorX = x[i - 1] + dt * (55 * derivadaX[i - 1] - 59 * derivadaX[i - 2] + 37 * derivadaX[i - 3] - 9 * derivadaX[i - 4]) / 24;

        preditorY1 = result.getValue(0, i - 1) + dt * (55 * z[i - 1] - 59 * z[i - 2] + 37 * z[i - 3] - 9 * z[i - 4]) / 24;
        preditorY2 = result.getValue(1, i - 1) + dt * (55 * w[i - 1] - 59 * w[i - 2] + 37 * w[i - 3] - 9 * w[i - 4]) / 24;
        preditorY3 = result.getValue(2, i - 1) + dt * (55 * x[i - 1] - 59 * x[i - 2] + 37 * x[i - 3] - 9 * x[i - 4]) / 24;

        derivadaPreditorZ = (*dz)(preditorY1,preditorY2);
        derivadaPreditorW = (*dw)(preditorY1, preditorY2, preditorY3, preditorW, preditorX);
        derivadaPreditorX = (*dx)(preditorY2, preditorY3, preditorW, preditorX);

        z[i] = z[i - 1] + dt * (9 * derivadaPreditorZ + 19 * derivadaZ[i - 1] - 5 * derivadaZ[i - 2] + derivadaZ[i - 3]) / 24;
        w[i] = w[i - 1] + dt * (9 * derivadaPreditorW + 19 * derivadaW[i - 1] - 5 * derivadaW[i - 2] + derivadaW[i - 3]) / 24;
        x[i] = x[i - 1] + dt * (9 * derivadaPreditorX + 19 * derivadaX[i - 1] - 5 * derivadaX[i - 2] + derivadaX[i - 3]) / 24;

        derivadaPreditorY1 = z[i];
        derivadaPreditorY2 = w[i];
        derivadaPreditorY3 = x[i];

        result.setValue(0, i, result.getValue(0,i - 1) + dt * (9 * derivadaPreditorY1 + 19 * z[i - 1] - 5 * z[i - 2] + z[i - 3]) / 24);
        result.setValue(1, i, result.getValue(1,i - 1) + dt * (9 * derivadaPreditorY2 + 19 * w[i - 1] - 5 * w[i - 2] + w[i - 3]) / 24);
        result.setValue(2, i, result.getValue(2,i - 1) + dt * (9 * derivadaPreditorY3 + 19 * x[i - 1] - 5 * x[i - 2] + x[i - 3]) / 24);

        derivadaZ[i] = (*dz)(result.getValue(0,i), result.getValue(1,i));
        derivadaW[i] = (*dw)(result.getValue(0,i), result.getValue(1,i), result.getValue(2,i), w[i], x[i]);
        derivadaX[i] = (*dx)(result.getValue(1,i), result.getValue(2,i), w[i], x[i]);

        result.setDerivate(0,i,z[i]);
        result.setDerivate(1,i,w[i]);
        result.setDerivate(2,i,x[i]);
    }

    result.setTime(temporizador.getTimeInSec());
	return result;

}


