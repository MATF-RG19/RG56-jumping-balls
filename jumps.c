#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include "funkcije.h"

#define TIMER_ID1 0  //za skok leve
#define TIMER_ID2 1  //za  skok desne
#define TIMER_ID3  3 // za animaciju prepreka	
#define TIMER_INTERVAL 20

extern int animating_left;  //za skok leve
int going_up_left=1;
int going_down_left=0;

extern int animating_right; //za skok desne
int going_up_right=1;
int going_down_right=0;

//pocetne pozicije za levu (lbx,lby,lbz)  i desnu (rbx,rby,rbz) lopticu
//deklarisane i inicijalizovane u main.c
extern GLfloat lbx, lby, lbz;
extern GLfloat rbx, rby, rbx;

extern int game_started;

//pomocna funkcija za crtanje koordinatnih osa i pomocnih tacaka na x osi
void drawCoord(void){
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


void on_keyboard(unsigned char key, int x, int y){
	switch(key){
		case 27: 
			exit(0); 
			break;
		case 'w':   //kontrola kretanja leve loptice
		case 'W':
			if(!animating_left){
				glutTimerFunc(TIMER_INTERVAL, on_timer_left,TIMER_ID1);
				animating_left=1;
			}
			break;
        case 'a':
        case 'A':
            lbx-=0.1;
            glutPostRedisplay();
            break;
        case 'd':
        case 'D':
            lbx+=0.1;
            glutPostRedisplay();
            break;
            
        case 'i':  //kontrola kretanja desne loptice
		case 'I':
			if(!animating_right){
				glutTimerFunc(TIMER_INTERVAL, on_timer_right,TIMER_ID2);
				animating_right=1;
			}
			break;
        case 'j':
        case 'J':
            rbx-=0.1;
            glutPostRedisplay();
            break;
        case 'l':
        case 'L':
            rbx+=0.1;
            glutPostRedisplay();
            break;    

        case 'p':
        case 'P':
            if(!game_started){  //pocetak igre
                    glutTimerFunc(TIMER_INTERVAL, on_timer_obstacle,TIMER_ID3);
                    game_started=1;			
            }
            else{ //ako hocemo da pauziramo i zaustavimo animacije prepreka
                game_started=0;
            }
            break;
    }
	
	glutPostRedisplay();
}


//skok leve loptice
void on_timer_left(int value){
	if(value!=TIMER_ID1){
		return;
	}
    
    if(going_up_left){
      if(lby<1.3){
          lby+=0.05;
      }
      else if(lby>=1.3){
          going_up_left=0;
          going_down_left=1;
      }
    }
    
    else if(going_down_left){
      if(lby>0.2){
          lby-=0.05;  
      }
      else if(lby<=0.2){
          going_up_left=1;
          going_down_left=0;
          animating_left=0;
      }
    }
    glutPostRedisplay();
    if(animating_left){
        glutTimerFunc(TIMER_INTERVAL,on_timer_left,TIMER_ID1);
    }
}


//skok desne loptice
void on_timer_right(int value){
	if(value!=TIMER_ID2){
		return;
	}
    
    if(going_up_right){
      if(rby<1.3){
          rby+=0.05;
      }
      else if(rby>=1.3){
          going_up_right=0;
          going_down_right=1;
      }
    }
    
    else if(going_down_right){
      if(rby>0.2){
          rby-=0.05;  
      }
      else if(rby<=0.2){
          going_up_right=1;
          going_down_right=0;
          animating_right=0;
      }
    }
    glutPostRedisplay();
    if(animating_right){
        glutTimerFunc(TIMER_INTERVAL,on_timer_right,TIMER_ID2);
    }
}











