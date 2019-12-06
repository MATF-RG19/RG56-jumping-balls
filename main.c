#include<GL/glut.h>
#include<stdlib.h>

static int window_width;
static int window_height;


static void on_reshape(int width,int height);
static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);

static void drawCoord(void){
glColor3f(1.0,0.0,0.0); //crvena X
glBegin(GL_LINES);
glVertex3f(0.0,0.0,0.0);
glVertex3f(10.0,0.0,0.0);
glEnd();
glColor3f(0.0,1.0,0.0); //zelena Y
glBegin(GL_LINES);
glVertex3f(0.0,10.0,0.0);
glVertex3f(0.0,0.0,0.0);
glEnd();
glColor3f(0.0,0.0,1.0); //plava Z
glBegin(GL_LINES);
glVertex3f(0.0,0.0,10.0);
glVertex3f(0.0,0.0,0.0);
glEnd();

glColor3f(0.0,0.0,0.0);
glPointSize(5);
glBegin(GL_POINTS);
glVertex3f(0,0,0);
glVertex3f(1,0,0);
glVertex3f(2,0,0);
glVertex3f(3,0,0);
glEnd();
glColor3f(1,1,0);
glBegin(GL_POINTS);
glVertex3f(0.5,0,0);
glVertex3f(1.5,0,0);
glVertex3f(2.5,0,0);
glEnd();
}



int main(int argc,char **argv){

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowSize(900,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Jumping Balls v1.0");

	glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(on_keyboard);

	glClearColor(0.5,0.5,0.5,0);
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();

return 0;

}



static void on_reshape(int width,int height){	
	window_width=width;
	window_height=height;
	glViewport(0,0,window_width,window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80,window_width/(float)window_height,0.1,20);
}


static void on_keyboard(unsigned char key, int x, int y){
	switch(key){
		case 27: exit(0); break; 	
	}
}



static void on_display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

drawCoord();

	gluLookAt(1.5,1,3,1.5,0,0,0,1,0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glPushMatrix();   //prva traka (skroz levo)
	 glScalef(1.0,0.5,20);
	 glTranslatef(0.5,-0.5,0.0);	
	 glColor3f(0.0,1.0,1.0);
	 glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();   //druga traka (srednja)
	 glScalef(1.0,0.5,20);
	 glTranslatef(1.5,-0.5,0.0);	
	 glColor3f(0.5,1.5,1.5);
	 glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();   //treca traka(skroz denso)
	 glScalef(1.0,0.5,20);
	 glTranslatef(2.5,-0.5,0.0);	
	 glColor3f(1,1,1);
	 glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();   //leva loptica
	 glTranslatef(1,0.4,2);	
	 glColor3f(1,0.6,0.7);
	 glutSolidSphere(0.2,50,50);
	glPopMatrix();

	glPushMatrix();   //desna loptica
	 glTranslatef(2,0.4,2);	
	 glColor3f(0.3,0.9,0.4);
	 glutSolidSphere(0.2,50,50);
	glPopMatrix();
	


	glutSwapBuffers();
}
