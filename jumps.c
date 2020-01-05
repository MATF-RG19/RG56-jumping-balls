#include <GL/glut.h>
#include "funkcije.h"
#include <stdio.h>

#define TIMER_ID1 0  //za skok leve
#define TIMER_ID2 1  //za  skok desne
#define TIMER_ID3  3 // za animaciju prepreka	
#define TIMER_INTERVAL 20

extern int game_started;

//promenljiva koja cuva da li je igra pauzirana ili ne
int paused;

extern int animating_left;  //za skok leve
int going_up_left = 1;
int going_down_left = 0;

extern int animating_right; //za skok desne
int going_up_right = 1;
int going_down_right = 0;

//pozicije za levu (lbx,lby,lbz)  i desnu (rbx,rby,rbz) lopticu
//deklarisane i inicijalizovane u main.c
extern GLfloat lbx, lby, lbz;
extern GLfloat rbx, rby, rbz;

//koordinate prepreka, deklasisane i inicijalizovane u main.c
extern float o1x, o1y, o1z;
extern float o2x, o2y, o2z;
extern float o3x, o3y, o3z;
extern float o4x, o4y, o4z;

//oznake da li su tasteri pritisnuti ili ne
extern int jdown, ldown;
extern int adown, ddown;

//potrebno je omoguciti da se ove promenljive menjaju u ovom fajlu jer 
//se ovde registruje restartovanje igre, za informacije o njima pogledati fajlove u kojima su deklarisane
extern int score;
extern float speed_coef;
extern int health;
extern int should_be_drawn;
extern float hx, hy,hz;
extern int detecting;
extern int bounds_animation_left;
extern int bounds_animation_right;

//registrovanje pustanja odredjenog tastera
void on_keyboard_up (unsigned char key, int x, int y){
    // ako je neki taster pusten, vracamo njegovu statusnu promenljivu na 0
    switch (key){
        case 'j':
        case 'J':
            jdown = 0;
            break;
        case 'l':
        case 'L':  
            ldown = 0;
            break;
        case 'a':
        case 'A':
            adown = 0;
            break;
        case 'd':
        case 'D':  
            ddown = 0;
            break;    
    }
}

//registrovanje pritiska odredjenog tastera
void on_keyboard(unsigned char key, int x, int y){
	switch(key){
		case 27: 
			exit(0); 
			break;
		case 'w':   //kontrola kretanja leve loptice
		case 'W':
            if (game_started){
                if(!animating_left){
                    animating_left = 1;
                    glutTimerFunc(TIMER_INTERVAL, on_timer_left, TIMER_ID1);
                }
            }
			break;
        case 'a':
        case 'A':
            // ako je pritisnut taster 'a', njegovu statusnu promenljivu stavljamo na 1, analogno za ostale
            adown = 1;
            break;
        case 'd':
        case 'D':
            ddown = 1;
            break;
            
        case 'i':  //kontrola kretanja desne loptice
		case 'I':
            if (game_started){
                if(!animating_right){
                    animating_right = 1;
                    glutTimerFunc(TIMER_INTERVAL, on_timer_right, TIMER_ID2);
                }
            }
			break; 
        case 'j':  
        case 'J':
            jdown = 1;
            break;
        case 'l':
        case 'L':
            ldown = 1;
            break;    

        case 'p':
        case 'P':
            if(!game_started){  //pocetak igre
                    paused = 0;
                    game_started = 1;
                    glutTimerFunc(TIMER_INTERVAL, on_timer_obstacle, TIMER_ID3);
                    //posto taster 'p' koristimo i za pocetak igre i za pause/unpause,
                    //ako smo pauzirali u sred animacije skoka treba ih nastaviti
                    if (animating_left) glutTimerFunc(TIMER_INTERVAL, on_timer_left, TIMER_ID1);
                    if (animating_right) glutTimerFunc(TIMER_INTERVAL, on_timer_right, TIMER_ID2);
            }
            else{ //ako hocemo da pauziramo i zaustavimo animacije prepreka
                game_started = 0;
                paused = 1;
            }
            break;
        case 'r':
        case 'R':
            //restartovanje igre, sve relevantne promenljive se vracaju na pocetne vrednosti
            game_started = 0;
            paused = 1;
            
            score = 0;
            speed_coef = 0.25;
            
            animating_left = 0; 
            animating_right = 0; 
            bounds_animation_left = 0;
            bounds_animation_right = 0;
            
            going_up_left = 1;
            going_down_left = 0;
            going_up_right = 1;
            going_down_right = 0;
 
            lbx = 0.6;
            lby = 0.2;
            lbz = 2;

            rbx = 2.4;
            rby = 0.2;
            rbz = 2;

            o1x = 0;     
            o1y = 0.35;
            o1z = -20;

            o2x = 0;
            o2y = 0.35;
            o2z = -20;

            o3x = 0;
            o3y = 0.35;
            o3z = -20;

            o4x = 0;
            o4y = 0.35;
            o4z = -20;     
            
            hx = 0;
            hy = 0.35;
            hz = -20;
            
            health = 3;
            should_be_drawn = 1;
        
            detecting = 0;
            
            glutPostRedisplay();
            break;
    }
	
	glutPostRedisplay();
}


//skok leve loptice
void on_timer_left(int value){
	if(value != TIMER_ID1){
		return;
	}
    
    if(going_up_left){
      if(lby < 1.3){
          lby += 0.05;
      }
      else if(lby >= 1.3){
          going_up_left = 0;
          going_down_left = 1;
      }
    }
    
    else if(going_down_left){
      if(lby > 0.2){
          lby -= 0.05;  
      }
      else if(lby <= 0.2){
          going_up_left = 1;
          going_down_left = 0;
          animating_left = 0;
      }
    }
    glutPostRedisplay();
    if(animating_left && !paused){
        glutTimerFunc(TIMER_INTERVAL, on_timer_left, TIMER_ID1);
    }
}


//skok desne loptice
void on_timer_right(int value){
	if(value != TIMER_ID2){
		return;
	}
    
    if(going_up_right){
      if(rby < 1.3){
          rby += 0.05;
      }
      else if(rby >= 1.3){
          going_up_right = 0;
          going_down_right = 1;
      }
    }
    
    else if(going_down_right){
      if(rby > 0.2){
          rby -= 0.05;  
      }
      else if(rby <= 0.2){
          going_up_right = 1;
          going_down_right = 0;
          animating_right = 0;
      }
    }
    glutPostRedisplay();
    if(animating_right && !paused){
        glutTimerFunc(TIMER_INTERVAL, on_timer_right, TIMER_ID2);
    }
}
