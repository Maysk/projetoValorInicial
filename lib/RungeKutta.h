class RungeKutta{
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
	
public:
	RungeKutta(double (*dz) (double,double),double (*dw)(double,double,double,double,double),double (*dx)(double ,double ,double ,double ),double y1,double y2 ,double y3,double dy1,double dy2 ,double dy3,double t,double dt);
	Result rkSegundaOrdem();
	Result rkTerceiraOrdem();
	Result rkQuartaOrdem();
};
