#include "../lib/imports.h"
Result::Result(){}

Result::Result(int length){
	this->length = length;
	this->values = new double*[3];
	this->values[0] = new double[length];
	this->values[1] = new double[length];
	this->values[2] = new double[length];
	this->derivates = new double*[3];
	this->derivates[0] = new double[length];
	this->derivates[1] = new double[length];
	this->derivates[2] = new double[length];
	this->time = 0;
	this->deltaT = 0;
	this->iterations = length-1;
}
Result::~Result(){
	delete values;
}

void Result::operator=(Result result){
    this->length = result.length;
    this->values = new double*[3];
    this->values[0] = new double[length];
	this->values[1] = new double[length];
	this->values[2] = new double[length];

	for(int i=0; i<length; i++){
        this->setValue(0,i,result.getValue(0,i));
        this->setValue(1,i,result.getValue(1,i));
        this->setValue(2,i,result.getValue(2,i));
	}

    this->derivates = new double*[3];
    this->derivates[0] = new double[length];
	this->derivates[1] = new double[length];
	this->derivates[2] = new double[length];

    for(int i=0; i<length; i++){
        this->setDerivate(0,i,result.getDerivate(0,i));
        this->setDerivate(1,i,result.getDerivate(1,i));
        this->setDerivate(2,i,result.getDerivate(2,i));
	}

	this->time = result.getTime();
	this->deltaT = result.getDeltaT();
	this->iterations = result.getIterations();

}

double Result::getValue(int var,int position){
	if(position >= 0 && position < length && var >= 0 && var < 3)
		return values[var][position];
	return 0;
}

double Result::getDerivate(int var,int position){
	if(position >= 0 && position < length && var >= 0 && var < 3)
		return derivates[var][position];
	return 0;
}


double Result::getTime(){
	return time;
}
double Result::getDeltaT(){
	return deltaT;
}
int Result::getLength(){
	return length;
}
int Result::getIterations(){
	return iterations;
}
void Result::setTime(double time){
	this->time = time;
}
void Result::setValue(int var,int position,double value){
	if(position >= 0 && position < length && var >= 0 && var < 3)
		values[var][position] = value;
}

void Result::setDerivate(int var, int position, double value){
	if(var < 3 && position < length)
		derivates[var][position] = value;
}


void Result::setIterations(int iterations){
	this->iterations = iterations;
}

void Result::setDeltaT(double deltaT){
	this->deltaT = deltaT;
}

void Result::show(){
	for(int i = 0 ; i < length ; i++)
		cout << "Rodada: " << i << "\tTempo: " << i * deltaT << "\ty1: " << getValue(0,i) << "\ty2: " << getValue(1,i) << "\ty3: " << getValue(2,i) << endl;
	cout << "Tempo de execução: " << time << " secs\n";
}

void Result::showFinal(){
	cout << "Rodadas: " << (length-1) << "\tTempo: " << (length-1) * deltaT << "\ty1: " << getValue(0,length-1) << "\ty2: " << getValue(1,length-1) << "\ty3: " << getValue(2,length-1) << "\t";
	cout << "Tempo de execução: " << time << " secs\n";
}
