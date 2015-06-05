class Result{
	double time;
	double deltaT;
	double** values;
    double** derivates;
	int length;
	int iterations;

public:
    Result();
	Result(int length);
	~Result();

    void operator=(Result);

	double getValue(int var,int position);
    double getDerivate(int var, int position);
	double getTime();
	double getDeltaT();
	int getLength();
	int getIterations();

	void setTime(double time);
	void setValue(int var, int position, double value);
	void setDerivate(int var, int position, double value);
	void setIterations(int iterations);
	void setDeltaT(double deltaT);

	void show();
	void showFinal();
};
