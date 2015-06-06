#include "../lib/imports.h"


// Largura e altura da janela
	GLfloat windowWidth;
	GLfloat windowHeight;


	GLfloat M1x0 = 100.0f;
	GLfloat M1y0 = 150.0f;
	GLfloat sizeM = 50.0f;
	GLfloat sizeK = 20.0f;
	GLfloat M2x0 = M1x0+sizeK+sizeM;
	GLfloat M2y0 = M1y0;
	GLfloat M3x0 = M2x0+sizeK+sizeM;
	GLfloat M3y0 = M2y0;
	double dt = 0.001;//secs
	double t = 20;//secs
	double iteration = 0;
	GLfloat Y1 = 0,Y2 = 0,Y3 = 0;
	Result* result;
	// double rate = pow(dt,-1) / 50; //Dura 17 segundos
	double rate = pow(dt,-1) / 20; //Dura 7 segundos, mas fica agradável

// Função callback chamada para fazer o desenho
void Desenha(void)
{
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();

     glClear(GL_COLOR_BUFFER_BIT);


     // Desenha M1
     glColor3f(1.0f, 0.0f, 0.0f);
     glBegin(GL_QUADS);
               glVertex2i(M1x0 + Y1,M1y0);
               glVertex2i(M1x0 + Y1,M1y0 + sizeM);
               // Especifica que a cor corrente é azul

               glVertex2i(M1x0 + sizeM + Y1,M1y0 + sizeM);
               glVertex2i(M1x0 + sizeM + Y1,M1y0);
     glEnd();

	//Desenha K1
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex2i(M1x0 + sizeM + Y1,M1y0 + sizeM * 0.5);
        glVertex2i(M1x0 + sizeM + sizeK + Y1,M1y0 + sizeM * 0.5);
	glEnd();

     // Desenha M2
     glColor3f(0.0f, 0.0f, 1.0f);
     glBegin(GL_QUADS);
               glVertex2i(M2x0 + Y2,M2y0 + sizeM);
               glVertex2i(M2x0 + Y2,M2y0);
               // Especifica que a cor corrente é azul

               glVertex2i(M2x0 + sizeM + Y2,M2y0);
               glVertex2i(M2x0 + sizeM + Y2,M2y0 + sizeM);
     glEnd();

     //Desenha K2
    glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex2i(M2x0 + sizeM + Y2,M2y0 + sizeM * 0.5);
        glVertex2i(M2x0 + sizeM + sizeK + Y2,M2y0 + sizeM * 0.5);
	glEnd();
     //Desenha B1
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex2i(M2x0 + sizeM + Y2,M2y0);
        glVertex2i(M2x0 + sizeM + sizeK + Y2,M2y0);
	glEnd();


     // Desenha M3
     glColor3f(0.0f, 1.0f, 0.0f);
     glBegin(GL_QUADS);
               glVertex2i(M3x0 + Y3,M3y0 + sizeM);
               glVertex2i(M3x0 + Y3,M3y0);
               // Especifica que a cor corrente é azul

               glVertex2i(M3x0 + sizeM + Y3,M3y0);
               glVertex2i(M3x0 + sizeM + Y3,M3y0 + sizeM);
     glEnd();

	//Desenha B2
 //    glColor3f(1.0f, 1.0f, 1.0f);
	// glBegin(GL_LINES);
	// 	glVertex2i(M3x0 + sizeM + Y3,M3y0);
 //        glVertex2i(M3x0 + sizeM + sizeK,M3y0);
	// glEnd();

	//Desenha K3
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex2i(M3x0 + sizeM +Y3,M3y0 + sizeM * 0.5);
        glVertex2i(M3x0 + sizeM + sizeK,M3y0 + sizeM * 0.5);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex2i(M3x0 + sizeM + sizeK,M3y0 - sizeM);
        glVertex2i(M3x0 + sizeM + sizeK,M3y0 + 2 * sizeM);
	glEnd();
     // Executa os comandos OpenGL
     glutSwapBuffers();
}


void Timer(int value)
{


    // Move o quadrado
    Y1 = (GLfloat) result->getValue(0,iteration);
    Y2 = (GLfloat) result->getValue(1,iteration);
    Y3 = (GLfloat) result->getValue(2,iteration);
    // iteration++;//deveria ser isso
    iteration+=rate;
    // Redesenha o quadrado com as novas coordenadas
    glutPostRedisplay();
    glutTimerFunc(rate,Timer, 1);//deveria ser isso
    // glutTimerFunc(1,Timer, 1);
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
     // Evita a divisao por zero
     if(h == 0) h = 1;

     // Especifica as dimensões da Viewport
     glViewport(0, 0, w, h);

     // Inicializa o sistema de coordenadas
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

     // Estabelece a janela de seleção (left, right, bottom, top)
     if (w <= h)  {
		windowHeight = 250.0f*h/w;
		windowWidth = 250.0f;
     }
     else  {
		windowWidth = 250.0f*w/h;
		windowHeight = 250.0f;
     }

     gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);
}


int main(int argc, char **argv){
	cout << "Entre com o dt:\n";
	cin >> dt;
	cout <<"\n---------------------------------Euler---------------------------------\n";
	Euler euler(dz,dw,dx,0,0,0,0,0,0,t,dt);
	Result eulerResult1 = euler.backward(0.1);
	Result eulerResult2 = euler.forward();
	Result eulerResult3 = euler.eulerModify(0.1);
	cout << "Backward:\n";
	eulerResult1.showFinal();
	cout << "Forward:\n";
	eulerResult2.showFinal();
	cout << "Modified:\n";
	eulerResult3.showFinal();
	cout <<"-----------------------------------------------------------------------\n";

	cout <<"---------------------------------Runge-Kutta---------------------------------\n";
	RungeKutta rugeKutta(dz,dw,dx,0,0,0,0,0,0,t,dt);
	Result rugeKuttaResult1 = rugeKutta.rkSegundaOrdem();
	Result rugeKuttaResult2 = rugeKutta.rkTerceiraOrdem();
	Result rugeKuttaResult3 = rugeKutta.rkQuartaOrdem();
	cout << "SegundaOrdem:\n";
	rugeKuttaResult1.showFinal();
	cout << "TerceiraOrdem:\n";
	rugeKuttaResult2.showFinal();
	cout << "QuartaOrdem:\n";
	rugeKuttaResult3.showFinal();
	cout <<"------------------------------------------------------------------------------\n";


    PreditorCorretor pc(dz,dw,dx,0,0,0,0,0,0,t,dt);
	cout <<"---------------------------------Preditor 3ª Ordem---------------------------------\n";
    Result preditorCorretorResult = pc.pcTerceiraOrdem(FORWARD_EULER);
    cout << "FORWARD_EULER:\n";
    preditorCorretorResult.showFinal();

    Result preditorCorretorResult2 = pc.pcTerceiraOrdem(BACKWARD_EULER);
    cout << "BACKWARD_EULER:\n";
    preditorCorretorResult2.showFinal();

    Result preditorCorretorResult3 = pc.pcTerceiraOrdem(EULER_MODIFY);
    cout << "EULER_MODIFY:\n";
    preditorCorretorResult3.showFinal();

    Result preditorCorretorResult4 = pc.pcTerceiraOrdem(RUNGEKUTTA_2ORDEM);
    cout << "RUNGEKUTTA_2ORDEM:\n";
    preditorCorretorResult4.showFinal();

    Result preditorCorretorResult5 = pc.pcTerceiraOrdem(RUNGEKUTTA_3ORDEM);
    cout << "RUNGEKUTTA_3ORDEM:\n";
    preditorCorretorResult5.showFinal();
    
    Result preditorCorretorResult6 = pc.pcTerceiraOrdem(RUNGEKUTTA_4ORDEM);
    cout << "RUNGEKUTTA_4ORDEM:\n";
    preditorCorretorResult6.showFinal();
    cout <<"----------------------------------------------------------------------------------\n";
    cout <<"---------------------------------Preditor 4ª Ordem---------------------------------\n";
    Result preditorCorretorResult7 = pc.pcQuartaOrdem(FORWARD_EULER);
    cout << "FORWARD_EULER:\n";
    preditorCorretorResult7.showFinal();

    Result preditorCorretorResult8 = pc.pcQuartaOrdem(BACKWARD_EULER);
    cout << "BACKWARD_EULER:\n";
    preditorCorretorResult8.showFinal();

    Result preditorCorretorResult9 = pc.pcQuartaOrdem(EULER_MODIFY);
    cout << "EULER_MODIFY:\n";
    preditorCorretorResult9.showFinal();

    Result preditorCorretorResult10 = pc.pcQuartaOrdem(RUNGEKUTTA_2ORDEM);
    cout << "RUNGEKUTTA_2ORDEM:\n";
    preditorCorretorResult10.showFinal();

    Result preditorCorretorResult11 = pc.pcQuartaOrdem(RUNGEKUTTA_3ORDEM);
    cout << "RUNGEKUTTA_3ORDEM:\n";
    preditorCorretorResult11.showFinal();
    
    Result preditorCorretorResult12 = pc.pcQuartaOrdem(RUNGEKUTTA_4ORDEM);
    cout << "RUNGEKUTTA_4ORDEM:\n";
    preditorCorretorResult12.showFinal();
    cout <<"----------------------------------------------------------------------------------\n";
    int op;
    do{
    cout << "----------------------------------------Menu----------------------------------------\n";
	cout << "(1)Mostrar resultado completo para método\n";
	cout << "(2)Mostrar animeção\n";
	cout << "(3)Sair\n";
	cin >> op;
	cout << "-------------------------------------------------------------------------------------\n";
	if(op == 3)
		return 0;
	if(op == 1){
		cout << "Escolha o método para exibição:\n";
    	cout << "(1)Euler-Backward:\n";
		cout << "(2)Euler-Forward:\n";
		cout << "(3)Euler-Modified:\n";
		cout << "(4)Runge-Kutta-SegundaOrdem:\n";
		cout << "(5)Runge-Kutta-TerceiraOrdem:\n";
		cout << "(6)Runge-Kutta-QuartaOrdem:\n";
		cout << "(7)Preditor-Corretor-3Ordem-FORWARD_EULER:\n";
		cout << "(8)Preditor-Corretor-3Ordem-BACKWARD_EULER:\n";
		cout << "(9)Preditor-Corretor-3Ordem-EULER_MODIFY:\n";
		cout << "(10)Preditor-Corretor-3Ordem-RUNGEKUTTA_2ORDEM:\n";
		cout << "(11)Preditor-Corretor-3Ordem-RUNGEKUTTA_3ORDEM:\n";
		cout << "(12)Preditor-Corretor-3Ordem-RUNGEKUTTA_4ORDEM:\n";
		cout << "(13)Preditor-Corretor-4Ordem-BACKWARD_EULER:\n";
		cout << "(14)Preditor-Corretor-4Ordem-Preditor-Corretor-EULER_MODIFY:\n";
		cout << "(15)Preditor-Corretor-4Ordem-FORWARD_EULER:\n";
		cout << "(16)Preditor-Corretor-4Ordem-RUNGEKUTTA_2ORDEM:\n";
		cout << "(17)Preditor-Corretor-4Ordem-RUNGEKUTTA_3ORDEM:\n";
		cout << "(18)Preditor-Corretor-4Ordem-RUNGEKUTTA_4ORDEM:\n";
		cin >> op;
		if(op ==  1){
			eulerResult1.show();
		}
		if(op ==  2){
			eulerResult2.show();
		}
		if(op ==  3){
			eulerResult3.show();
		}
		if(op ==  4){
			rugeKuttaResult1.show();
		}
		if(op ==  5){
			rugeKuttaResult2.show();
		}
		if(op ==  6){
			rugeKuttaResult2.show();
		}
		if(op ==  7){
			preditorCorretorResult.show();
		}
		if(op ==  8){
			preditorCorretorResult2.show();
		}
		if(op ==  9){
			preditorCorretorResult3.show();
		}
		if(op ==  10){
			preditorCorretorResult4.show();
		}
		if(op ==  11){
			preditorCorretorResult5.show();
		}
		if(op ==  12){
			preditorCorretorResult6.show();
		}
		if(op ==  13){
			preditorCorretorResult7.show();
		}
		if(op ==  14){
			preditorCorretorResult8.show();
		}
		if(op ==  15){
			preditorCorretorResult9.show();
		}
		if(op ==  16){
			preditorCorretorResult10.show();
		}
		if(op ==  17){
			preditorCorretorResult11.show();
		}
		if(op ==  18){
			preditorCorretorResult12.show();
		}
	}
    }while(op != 2);

    
    cout << "Escolha o método da animação:\n";
    cout << "(1)Euler-Backward:\n";
	cout << "(2)Euler-Forward:\n";
	cout << "(3)Euler-Modified:\n";
	cout << "(4)Runge-Kutta-SegundaOrdem:\n";
	cout << "(5)Runge-Kutta-TerceiraOrdem:\n";
	cout << "(6)Runge-Kutta-QuartaOrdem:\n";
	cout << "(7)Preditor-Corretor-3Ordem-FORWARD_EULER:\n";
	cout << "(8)Preditor-Corretor-3Ordem-BACKWARD_EULER:\n";
	cout << "(9)Preditor-Corretor-3Ordem-EULER_MODIFY:\n";
	cout << "(10)Preditor-Corretor-3Ordem-RUNGEKUTTA_2ORDEM:\n";
	cout << "(11)Preditor-Corretor-3Ordem-RUNGEKUTTA_3ORDEM:\n";
	cout << "(12)Preditor-Corretor-3Ordem-RUNGEKUTTA_4ORDEM:\n";
	cout << "(13)Preditor-Corretor-4Ordem-BACKWARD_EULER:\n";
	cout << "(14)Preditor-Corretor-4Ordem-Preditor-Corretor-EULER_MODIFY:\n";
	cout << "(15)Preditor-Corretor-4Ordem-FORWARD_EULER:\n";
	cout << "(16)Preditor-Corretor-4Ordem-RUNGEKUTTA_2ORDEM:\n";
	cout << "(17)Preditor-Corretor-4Ordem-RUNGEKUTTA_3ORDEM:\n";
	cout << "(18)Preditor-Corretor-4Ordem-RUNGEKUTTA_4ORDEM:\n";
	cin >> op;
		if(op ==  1){
			result = &eulerResult1;
		}
		if(op ==  2){
			result = &eulerResult2;
		}
		if(op ==  3){
			result = &eulerResult3;
		}
		if(op ==  4){
			result = &rugeKuttaResult1;
		}
		if(op ==  5){
			result = &rugeKuttaResult2;
		}
		if(op ==  6){
			result = &rugeKuttaResult2;
		}
		if(op ==  7){
			result = &preditorCorretorResult;
		}
		if(op ==  8){
			result = &preditorCorretorResult2;
		}
		if(op ==  9){
			result = &preditorCorretorResult3;
		}
		if(op ==  10){
			result = &preditorCorretorResult4;
		}
		if(op ==  11){
			result = &preditorCorretorResult5;
		}
		if(op ==  12){
			result = &preditorCorretorResult6;
		}
		if(op ==  13){
			result = &preditorCorretorResult7;
		}
		if(op ==  14){
			result = &preditorCorretorResult8;
		}
		if(op ==  15){
			result = &preditorCorretorResult9;
		}
		if(op ==  16){
			result = &preditorCorretorResult10;
		}
		if(op ==  17){
			result = &preditorCorretorResult11;
		}
		if(op ==  18){
			result = &preditorCorretorResult12;
		}

	// rate = floor((result->getIterations() / 1000) * (20/(result->getIterations()/1000))); // deveria ser isso
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Valor Inicial");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    // glutTimerFunc(rate, Timer, 1);//deveria ser isso
    glutTimerFunc(1, Timer, 1);
    Inicializa();
    glutMainLoop();

    return 0;
}
double dz(double y1,double y2){
	return (F1 - K1 * y1 + K1 * y2) / M1;
}
double dw(double y1,double y2, double y3,double w,double x){
	return	(K1 * y1 -B1 * w - (K1 + K2) * y2 + B1 * x + K2 * y3) / M2;
}
double dx(double y2,double y3,double w,double x){
	return	(F3 + K2 * y2 + B1 * w - B1 * x - (K2 + K3) *y3) / M3;
}
