#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include "funkcije.h"

int game_started;

int window_width;
int window_height;

int animating_left;  //za skok leve
int animating_right; //za skok desne
 
//pocetne pozicije za levu (lbx,lby,lbz)  i desnu (rbx,rby,rbz) lopticu
GLfloat lbx=0.6;
GLfloat lby=0.2;
GLfloat lbz=2;

GLfloat rbx=2.4;
GLfloat rby=0.2;
GLfloat rbz=2;

float o1x=0;     //pocetne koordinate prve prepreke (van vidljive scene)
float o1y=0.2;
float o1z=-20;

float o2x=0;	//pocetne koordinate druge prepreke (van vidljive scene)
float o2y=0.2;
float o2z=-20;

float o3x=0;	//pocetne koordinate trece prepreke (van vidljive scene)
float o3y=0.2;
float o3z=-20;


int main(int argc,char **argv){

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(900,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Jumping Balls v1.0");

	glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(on_keyboard);

	glClearColor(0.5,0.5,0.5,0);
	glEnable(GL_DEPTH_TEST);
    
    	animating_left=0;  //inicijalizacija animacije skoka leve
    	animating_right=0; //i desne loptice

	srand(time(NULL));  //seed za nasumicne brojeve koji ce nam odredjivati polozaje prepreka
	game_started=0;

	glutMainLoop();

return 0;

}


void on_reshape(int width,int height){	
	window_width=width;
	window_height=height;
    
	glViewport(0,0,window_width,window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
	gluPerspective(80,window_width/(float)window_height,0.1,20);
}



void on_display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawCoord();

	gluLookAt(1.5,1,3,1.5,0,0,0,1,0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();   //prva traka sa preprekama (skroz levo)
	 glScalef(1.0,0.5,40);
	 glTranslatef(0.5,-0.5,0.0);	
	 glColor3f(0.0,1.0,1.0);
	 glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();   //druga traka sa preprekama  (srednja)
	 glScalef(1.0,0.5,40);
	 glTranslatef(1.5,-0.5,0.0);	
	 glColor3f(0.5,1.5,1.5);
	 glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();   //treca traka sa preprekama (skroz denso)
	 glScalef(1.0,0.5,40);
	 glTranslatef(2.5,-0.5,0.0);	
	 glColor3f(1,1,1);
	 glutSolidCube(1);
	glPopMatrix();

        

	glPushMatrix();   //leva loptica
	 glTranslatef(lbx, lby, lbz);
	 glColor3f(1,0.6,0.7);
	 glutSolidSphere(0.2,50,50);
	glPopMatrix();

	glPushMatrix();   //desna loptica
	 glTranslatef(rbx, rby, rbz);
	 glColor3f(0.3,0.9,0.4);
	 glutSolidSphere(0.2,50,50);
	glPopMatrix();

	
    //iscrtavanje nasumicnih prepreka
    draw_obstacles();
	

	glutSwapBuffers();
}
