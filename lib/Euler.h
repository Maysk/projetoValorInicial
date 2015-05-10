class Euler{
	double (*dz) (double,double);
	double (*dw)(double,double,double,double);
	double (*dx)(double ,double ,double ,double );
	double y1;
	double y2;
	double y3;
	double dy1;
	double dy2;
	double dy3;
	double t;
	double dt;
	int steps;
	// Result iteration(double error,double (*multFac)(int,double,double,double,double));
	// double multFacForward(int function,double ynKPrevious,double tn,double trash,double trash2);
	// double multFacModify(int function,double ynKPrevious,double tn,double yn1,double tn1);
public:
	Euler(double (*dz) (double,double),double (*dw)(double,double,double,double),double (*dx)(double ,double ,double ,double ),double y1,double y2 ,double y3,double dy1,double dy2 ,double dy3,double t,double dt);
	Result forward();
	Result backward(double error);
	Result eulerModify(double error);
};