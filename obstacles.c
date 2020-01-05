#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "funkcije.h"

#define TIMER_INTERVAL 20
#define TIMER_ID3  3 // za animaciju prepreka

extern int game_started;

extern float o1x, o1y, o1z;  //koordinate prve prepreke
extern float o2x, o2y, o2z;  //koordinate druge prepreke
extern float o3x, o3y, o3z;  //koordinate trece prepreke
extern float o4x, o4y, o4z;  //koordinate cetvrte prepreke

//koordinate health drop-a
extern float hx, hy, hz;

//oznake da li se 1/2/3/4 prepreka nalazi u vidnom polju, na pocetku se ne vide
int in_view1 = 0;
int in_view2 = 0;
int in_view3 = 0;
int in_view4 = 0;

//oznaka da li se health drop nalazi u vidnom polju
int in_view_health = 0;

//pomocna promenljiva koja nam govori da li health drop treba da se crta ili ne
extern int should_be_drawn;

//parametar koji sluzi za poemranje kamere na pocetku igre
extern float viewParam;

//broj poena
extern int score;

//brzina kretanja prepreka;
extern float speed_coef;

void on_timer_obstacle(int value){
	if(value != TIMER_ID3){
		return;
	}
	
	//pri pokretanju igre, kameru treba spustiti, to se kontrolise ovim parametrom
	//nakon tog prvog pokretanja kamera treba da ostane fiksirana u polozaju u kom stoji tokom igre 
	//tako da se viewParam nece ponovo postaviti na 0 u jumps.c kad se pritisne 'r' kao neke druge promenljive
	if(viewParam < 3){
	   viewParam += 0.15;
    }
	
	//ako je neka prepreka izasla iz vidnog polja (otprilike z>=5), njena z koordina se postavlja na default vrednost -20
	//sto oznacava delu koda ispod da treba da se nasumicno generise u kojoj od tri trake ce se ta prepreka sledece pojaviti
	if(o1z >= 5){
        o1z = -20;
        in_view1 = 0;
        //posto su sve z koordinate prepreka iste, dovoljno je pogledati da li se jedna
        //od njih nalazi van vidnog polja. U tom slucaju uvecavamo poene jer je igrac uspesno izbegao prepreke
        score += 4;
        //da bi se health drop pojavljivao u istoj ravni kao prepreke, potrebno je na ovom mestu azurirati
        //ovu promenljivu, kako bi se izbegla situacija da nakon sto igrac pokupi hp drop, a jos uvek nije 
        //izbegao prepreke, da se iscrta hp ponovo 
        should_be_drawn = 1;
    }
    if(o2z >= 5){
        o2z = -20;
        in_view2 = 0;
    }
    if(o3z >= 5){
        o3z = -20;
        in_view3 = 0;
    }
    if(o4z >= 5){
        o4z = -20;
        in_view4 = 0;
    }
    
    //slicna provera za health drop
    if( hz >= 5 ){
        hz = -20;
        in_view_health = 0;
    }
    
    //odredjivanje trake za prvu prepreku
    //nadjemo random broj, smestimo ga u interval 0-1 i gledamo sledece:
    //0-0.33 - prva traka, 0.33-0.66 - druga traka, 0.66-1 - treca traka
    //slicno za ostale prepreke
	if ( o1z == -20){                       
        float r = rand()/(float)RAND_MAX;
        if(r <= 0.33){
            o1x = 0.5;	
        }
        else if (r > 0.33 && r <= 0.66){
            o1x = 1.5;	
        }
        else{ //r > 0.66
            o1x = 2.5;	
        }
        
        //odredjivanje da li ce se prepreka nalaziti u gornjem ili donjem redu
        //slicnom logikom, 0 - 0.5 - donji red, 0.5 - 1 - gornji red  
        r = rand()/(float)RAND_MAX;
        if(r <= 0.5){
            o1y = 0.35;
        }
        else{  // r>0.5
            o1y = 1.05;
        }
        
        //nakon sto smo podesili koordinate centra prepreke, oznacimo da je treba iscrtavati
        in_view1 = 1;
	}
	
	//odredjivanje trake za drugu prepreku
	if ( o1z == -20){                        
        float r = rand()/(float)RAND_MAX;
        if(r <= 0.33){
            o2x = 0.5;	
        }
        else if (r > 0.33 && r <= 0.66){
            o2x = 1.5;	
        }
        else{ //r>0.66
            o2x = 2.5;	
        }
        
        //odredjivanje da li ce se prepreka nalaziti u gornjem ili donjem redu
        r = rand()/(float)RAND_MAX;
        if(r <= 0.5){
            o2y = 0.35;
        }
        else{  // r>0.5
            o2y = 1.05;
        }
        
        //nakon sto smo podesili koordinate centra prepreke, oznacimo da je treba iscrtavati
        in_view2 = 1;
	}
	
	//odredjivanje trake za trecu prepreku
	if ( o3z == -20){                         
        float r = rand()/(float)RAND_MAX;
        if(r <= 0.33){
            o3x = 0.5;	
        }
        else if (r > 0.33 && r <= 0.66){
            o3x = 1.5;	
        }
        else{ //r>0.66
            o3x = 2.5;	
        }
        
        //odredjivanje da li ce se prepreka nalaziti u gornjem ili donjem redu
        r = rand()/(float)RAND_MAX;
        if(r <= 0.5){
            o3y = 0.35;
        }
        else{  // r>0.5
            o3y = 1.05;
        }
        
        //nakon sto smo podesili koordinate centra prepreke, oznacimo da je treba iscrtavati
        in_view3 = 1;
	}
	
	//odredjivanje trake za trecu prepreku
	if ( o4z == -20){                         
        float r = rand()/(float)RAND_MAX;
        if(r <= 0.33){
            o4x = 0.5;	
        }
        else if (r > 0.33 && r <= 0.66){
            o4x = 1.5;	
        }
        else{ //r>0.66
            o4x = 2.5;	
        }
        
        //odredjivanje da li ce se prepreka nalaziti u gornjem ili donjem redu
        r = rand()/(float)RAND_MAX;
        if(r <= 0.5){
            o4y = 0.35;
        }
        else{  // r>0.5
            o4y = 1.05;
        }
        
        //nakon sto smo podesili koordinate centra prepreke, oznacimo da je treba iscrtavati
        in_view4 = 1;
	}
        
	//slicna provera za health drop samo sto uzimamo u obzir jos i should_be_drawn i trenutni skor(mora biti broj deljiv sa 4,
	//kad je 16 ne bude ni previse cesto ni previse retko)da bismo videli da li treba da se iscrtava ili ne
	//moze se desiti da se prepreka i hp objekat preklapaju kad im se nasumicno generisu koordinate, sto ih cini redjim
	if ( hz == -20 && (score % 16 == 0) && should_be_drawn){
        float r = rand()/(float)RAND_MAX;
        if(r <= 0.33){
            hx = 0.5;	
        }
        else if (r > 0.33 && r <= 0.66){
            hx = 1.5;	
        }
        else{ //r>0.66
            hx = 2.5;	
        }

        r = rand()/(float)RAND_MAX;
        if(r <= 0.5){
            hy = 0.35;
        }
        else{  // r>0.5
            hy = 1.05;
        }
        
        in_view_health = 1;
    }
	
	//u zavisnosti od osvojenih poena ubrzavamo kretanje prepreka
    if (score < 50) speed_coef = 0.25; 
    if (score >= 50 && score < 100) speed_coef = 0.3; 
    if (score >= 100 && score < 200) speed_coef = 0.35; 
    if (score >= 200 && score < 500) speed_coef = 0.4;
    if (score >= 500) speed_coef = 0.45;
	
	//ako je prepreka vidljiva, onda ima smisla animirati je (povecavati njenu z koordinatu)
    if(in_view1) o1z += speed_coef;
    if(in_view2) o2z += speed_coef;
    if(in_view3) o3z += speed_coef;
    if(in_view4) o4z += speed_coef;
	
    //slicno za health drop
    if(in_view_health) hz += speed_coef;
    
    glutPostRedisplay();
    
    if(game_started){
        glutTimerFunc(TIMER_INTERVAL, on_timer_obstacle, TIMER_ID3);
    }

}
