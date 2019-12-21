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
float o1y=0.35;
float o1z=-20;

float o2x=0;	//pocetne koordinate druge prepreke (van vidljive scene)
float o2y=0.35;
float o2z=-20;

float o3x=0;	//pocetne koordinate trece prepreke (van vidljive scene)
float o3y=0.35;
float o3z=-20;

float o4x=0;	//pocetne koordinate cetvrte prepreke (van vidljive scene)
float o4y=0.35;
float o4z=-20;

//oznake da li su tasteri 'a','d','j' i 'l' pritisnuti ili ne
int jdown,ldown;
int adown,ddown;


int main(int argc,char **argv){

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(900,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Jumping Balls v1.0");

	glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(on_keyboard);
    glutKeyboardUpFunc(on_keyboard_up);
    
    //da bismo pomerali loptice u isto vreme, potrebno je da sami registrujemo kada je neki 
    //taster pritisnut, a kada je optpusten, bez da registrujemo ponovljene pozive on_keyboard funkcije,
    //zato iskljucujemo te ponovljene pozive. Ovo nam je potrebno samo za pomeranje loptica levo i desno, jer 
    //za skokove nije potrebno drzati taster
    glutIgnoreKeyRepeat(1);     
    //na pcoetku nijedan taster nije pritisnut
    jdown=0;
    ldown=0;
    adown=0;
    ddown=0;
        
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

    //ako je igra pokrenuta i ako je pritisnut taster 'a' i ako poemranjem leve loptice
    //u levo za 0.05 ne dolazi do preklapanja loptica, treba izvrsiti tu izmenu, analogno i za tastere 'd','j' i 'l'
    if (game_started && adown && !are_players_coliding(lbx-0.05,lby,lbz,rbx,rby,rbz)){   
                lbx-=0.05;
    }
    if (game_started && ddown && !are_players_coliding(lbx+0.05,lby,lbz,rbx,rby,rbz)){
                lbx+=0.05;
    }
    if (game_started && jdown && !are_players_coliding(lbx,lby,lbz,rbx-0.05,rby,rbz)){
                rbx-=0.05;
    }
    if (game_started && ldown && !are_players_coliding(lbx,lby,lbz,rbx+0.05,rby,rbz)){
                rbx+=0.05;
    }
    

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
    
   if (is_there_a_collision()){
        game_started=0;
        animating_left=0;
        animating_right=0;
    }
	

	glutSwapBuffers();
}
