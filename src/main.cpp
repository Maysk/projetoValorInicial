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
	double dt = 0.01;//secs
	double t = 20;//secs
	double iteration = 0;
	GLfloat Y1 = 0,Y2 = 0,Y3 = 0;
	Result* result;
	double rate = pow(dt,-1) / 50; //Dura 17 segundos
	// double rate = pow(dt,-1) / 20; //Dura 7 segundos, mas fica agradável

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
	glColor3f(1.0f, 1.0f, 1.0f);     
	glBegin(GL_LINES);
		glVertex2i(M1x0 + sizeM + Y1,M1y0);
        glVertex2i(M1x0 + sizeM + sizeK + Y1,M1y0); 
	glEnd();
	//Desenha B1
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


     // Desenha M3
     glColor3f(0.0f, 1.0f, 0.0f);
     glBegin(GL_QUADS);
               glVertex2i(M3x0 + Y3,M3y0 + sizeM); 
               glVertex2i(M3x0 + Y3,M3y0);
               // Especifica que a cor corrente é azul
               
               glVertex2i(M3x0 + sizeM + Y3,M3y0);
               glVertex2i(M3x0 + sizeM + Y3,M3y0 + sizeM);               
     glEnd();

	//Desenha K3
    glColor3f(1.0f, 1.0f, 1.0f);     
	glBegin(GL_LINES);
		glVertex2i(M3x0 + sizeM + Y3,M3y0);
        glVertex2i(M3x0 + sizeM + sizeK,M3y0); 
	glEnd();
	
	//Desenha B2
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
    // glutTimerFunc(rate,Timer, 1);//deveria ser isso
    glutTimerFunc(1,Timer, 1);
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
	
	
	Euler euler(dz,dw,dx,0,0,0,0,0,0,t,dt);
	Result result1 = euler.backward(0.1);
	Result result2 = euler.forward();
	Result result3 = euler.eulerModify(0.1);
	cout << "Backward:\n";
	result1.showFinal();
	cout << "Forward:\n";
	result2.showFinal();
	cout << "Modified:\n";
	result3.showFinal();
	result = &result1;
	// cout << (result->getLength()) << endl;
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
	return 1 - y1 + y2;
}
double dw(double y1,double y2, double y3,double w,double x){
	return	y1 -0.25 * w - 2 * y2 + 0.25 * x + y3;
}
double dx(double y2,double y3,double w,double x){
	return	0.5 + y2 + 0.25 * w - 0.25 * x - 2 *y3;
}
