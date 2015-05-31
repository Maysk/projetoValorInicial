#include "../lib/imports.h"

Temporizador::Temporizador(){}

void Temporizador::iniciarTemporizador(){
    startTime = clock();
}

long double Temporizador::getTimeInSec(){
    clock_t endTime = clock();
    clock_t executionTime = (endTime - startTime);
	return executionTime/(long double) CLOCKS_PER_SEC;
}
