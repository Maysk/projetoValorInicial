#include "../lib/imports.h"
Result::Result(int length){
	this->length = length;
	this->values = new double*[3];
	this->values[0] = new double[length];
	this->values[1] = new double[length];
	this->values[2] = new double[length];
	this->time = 0;
	this->deltaT = 0;
	this->iterations = 0;
}
Result::~Result(){
	delete values;
}
double Result::getValue(int var,int position){
	if(position >= 0 && position < length && var >= 0 && var < 3)
		return values[var][position];
	return -999999;
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