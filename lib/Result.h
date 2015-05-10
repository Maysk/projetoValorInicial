class Result{
	double time;
	double deltaT;
	double** values;
	int length;
	int iterations;

public:
	Result(int length);
	~Result();
	double getValue(int var,int position);
	double getTime();
	double getDeltaT();
	int getLength();
	int getIterations();

	void setTime(double time);
	void setValue(int var,int position,double value);
	void setIterations(int iterations);
	void setDeltaT(double deltaT);

	void show();
	void showFinal();
};