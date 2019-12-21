#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include "funkcije.h"

#define TIMER_ID3  3 // za animaciju prepreka	
#define TIMER_INTERVAL 20

extern int game_started;

extern float o1x,o1y,o1z;  //koordinate prve prepreke
extern float o2x,o2y,o2z;  //koordinate druge prepreke
extern float o3x,o3y,o3z;  //koordinate trece prepreke
extern float o4x,o4y,o4z;  //koordinate cetvrte prepreke

//oznae da li se 1/2/3 prepreka nalazi u vidnom polju, na pocetku se ne vide
int in_view1=0;
int in_view2=0;
int in_view3=0;
int in_view4=0;

void draw_obstacles(){
    
    glPushMatrix();
	  glTranslatef(o1x,o1y,o1z);
      glScalef(1,0.7,0.5);
	  glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	  glTranslatef(o2x,o2y,o2z);
      glScalef(1,0.7,0.5);
	  glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	  glTranslatef(o3x,o3y,o3z);
      glScalef(1,0.7,0.5);
	  glutSolidCube(1);
	glPopMatrix();
    
    glPushMatrix();
	  glTranslatef(o4x,o4y,o4z);
      glScalef(1,0.7,0.5);
	  glutSolidCube(1);
	glPopMatrix();
}



void on_timer_obstacle(int value){
	if(value!=TIMER_ID3){
		return;		
	}
	
	//ako je neka prepreka izasla iz vidnog polja, njena z koordina se postavlja na default vrednost -20
	//sto oznacava delu koda ispod da treba da se nasumicno generise u kojoj od tri trake ce se ta prepreka sledece pojaviti
	if(o1z>=5){
        o1z=-20;
        in_view1=0;
    }
    if(o2z>=5){
        o2z=-20;
        in_view2=2;
    }
    if(o3z>=5){
        o3z=-20;
        in_view3=0;
    }
    if(o4z>=5){
        o4z=-20;
        in_view4=0;
    }
    
    //odredjivanje trake za prvu prepreku
	if ( o1z==-20){                       
        float r=rand()/(float)RAND_MAX;
        if(r<=0.33){
            o1x=0.5;	
        }
        else if (r>0.33 && r<=0.66){
            o1x=1.5;	
        }
        else{ //r>0.66
            o1x=2.5;	
        }
        
        //odredjivanje da li ce se prepreka nalaziti u gornjem ili donjem redu
        r=rand()/(float)RAND_MAX;
        if(r<=0.5){
            o1y=0.35;
        }
        else{  // r>0.5
            o1y=1.05;
        }
        
        in_view1=1;
	}
	
	//odredjivanje trake za drugu prepreku
	if ( o1z==-20){                        
        float r=rand()/(float)RAND_MAX;
        if(r<=0.33){
            o2x=0.5;	
        }
        else if (r>0.33 && r<=0.66){
            o2x=1.5;	
        }
        else{ //r>0.66
            o2x=2.5;	
        }
        
        //odredjivanje da li ce se prepreka nalaziti u gornjem ili donjem redu
        r=rand()/(float)RAND_MAX;
        if(r<=0.5){
            o2y=0.35;
        }
        else{  // r>0.5
            o2y=1.05;
        }
        
        in_view2=1;
	}
	
	//odredjivanje trake za trecu prepreku
	if ( o3z==-20){                         
        float r=rand()/(float)RAND_MAX;
        if(r<=0.33){
            o3x=0.5;	
        }
        else if (r>0.33 && r<=0.66){
            o3x=1.5;	
        }
        else{ //r>0.66
            o3x=2.5;	
        }
        
        //odredjivanje da li ce se prepreka nalaziti u gornjem ili donjem redu
        r=rand()/(float)RAND_MAX;
        if(r<=0.5){
            o3y=0.35;
        }
        else{  // r>0.5
            o3y=1.05;
        }
        
        in_view3=1;
	}
	
	//odredjivanje trake za trecu prepreku
	if ( o4z==-20){                         
        float r=rand()/(float)RAND_MAX;
        if(r<=0.33){
            o4x=0.5;	
        }
        else if (r>0.33 && r<=0.66){
            o4x=1.5;	
        }
        else{ //r>0.66
            o4x=2.5;	
        }
        
        //odredjivanje da li ce se prepreka nalaziti u gornjem ili donjem redu
        r=rand()/(float)RAND_MAX;
        if(r<=0.5){
            o4y=0.35;
        }
        else{  // r>0.5
            o4y=1.05;
        }
        
        in_view4=1;
	}
	
	//ako je prepreka vidljiva, onda ima smisla animirati je (povecavati njenu z koordinatu)
    if(in_view1) o1z+=0.25;
    if(in_view2) o2z+=0.25;
    if(in_view3) o3z+=0.25;
    if(in_view4) o4z+=0.25;
	
    glutPostRedisplay();
    
    if(game_started){
        glutTimerFunc(TIMER_INTERVAL,on_timer_obstacle,TIMER_ID3);
    }

}
