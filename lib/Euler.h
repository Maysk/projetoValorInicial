class Euler{
	double (*dz) (double,double);
	double (*dw)(double,double,double,double,double);
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
	double multFacForward(double fnk,double fn1);
	double multFacModify(double fnk,double fn1);
	Result iteration(double error,double (*multFac) (double,double));
public:
	Euler(double (*dz) (double,double),double (*dw)(double,double,double,double,double),double (*dx)(double ,double ,double ,double ),double y1,double y2 ,double y3,double dy1,double dy2 ,double dy3,double t,double dt);
	Result forward();
	Result backward(double error);
	Result eulerModify(double error);
};