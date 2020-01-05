/*
 Funckija initialize() za inicijalizaciju tekstura preuzeta uz male izmene sa:
 http://www.matf.bg.ac.rs/p/rastko-djordjevic/cas/2805/cas-7/
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "funkcije.h"
#include "image.h"

#define FILENAME0 "./images/grass.bmp"
#define FILENAME1 "./images/gravel.bmp"
#define FILENAME2 "./images/crate.bmp"
#define FILENAME3 "./images/sky.bmp"

//niz imena tekstura
GLuint names[4];

//glavni parametar koji cuva da li je igra pokrenuta ili ne
int game_started;

//kontrola pauziranja se vrsi u jumps.c
extern int paused;

int window_width;
int window_height;

int animating_left;  //za skok leve
int animating_right; //za skok desne
 
//pocetne pozicije za levu (lbx,lby,lbz)  i desnu (rbx,rby,rbz) lopticu
GLfloat lbx = 0.6, lby = 0.2, lbz = 2;
GLfloat rbx = 2.4, rby = 0.2, rbz = 2;

//pocetne koordinate prve prepreke 
float o1x = 0, o1y = 0.35, o1z = -20;

//pocetne koordinate druge prepreke
float o2x = 0, o2y = 0.35, o2z = -20;

//pocetne koordinate trece prepreke
float o3x = 0, o3y = 0.35, o3z = -20;

//pocetne koordinate cetvrte prepreke
float o4x = 0,  o4y = 0.35, o4z = -20;

//koordinate za health drop
float hx = 0, hy = 0.35, hz = -20;

//oznake da li su tasteri 'a','d','j' i 'l' pritisnuti ili ne
int jdown, ldown;
int adown, ddown;

//parametar za animaciju kamere pri prvom pokretanju igrice
float viewParam = 0;

//promenljiva koja cuva broj boodva
int score = 0;

//broj zivota
int health = 3;

//pomocna promenljiva koja nam govori da li health drop treba da se crta ili ne
int should_be_drawn = 1;

//pomocne promenljive za detekciju sudara u slucaju kada igrac ima >1 hp
int detecting = 0;

//promenljiva koja cuva brzinu prepreka
float speed_coef = 0.25;

static void initialize(void){
    /*
     names[0] - trava
     names[1] - sljunak
     names[2] - drvene kutije
     names[3] - nebo
     */
    
    /* Objekat koji predstavlja teskturu ucitanu iz fajla. */
    Image * image;

    /* Ukljucuje se testiranje z-koordinate piksela. */
    glEnable(GL_DEPTH_TEST);

    /* Ukljucuju se teksture. */
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    /*
     * Inicijalizuje se objekat koji ce sadrzati teksture ucitane iz
     * fajla.
     */
    image = image_init(0, 0);

    /* Kreira se prva tekstura. (trava) */
    image_read(image, FILENAME0);

    /* Generisu se identifikatori tekstura. */
    glGenTextures(4, names);

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Kreira se druga tekstura. (sljunak) */
    image_read(image, FILENAME1);

    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    
    /* Kreira se treca tekstura. (drvene kutije) */
    image_read(image, FILENAME2);

    glBindTexture(GL_TEXTURE_2D, names[2]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    
    /* Kreira se cetvrta tekstura. (nebo) */
    image_read(image, FILENAME3);

    glBindTexture(GL_TEXTURE_2D, names[3]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla. */
    image_done(image);
}



int main(int argc,char **argv){
    
    //glut inicijalizacija
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(900, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Jumping Balls v1.0");
    
    //registrovanje callack funkcija
    glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(on_keyboard);
    glutKeyboardUpFunc(on_keyboard_up);
    
    //da bismo pomerali loptice u isto vreme, potrebno je da sami registrujemo kada je neki 
    //taster pritisnut, a kada je optpusten, bez da registrujemo ponovljene pozive on_keyboard funkcije,
    //zato iskljucujemo te ponovljene pozive. Ovo nam je potrebno samo za pomeranje loptica levo i desno, jer 
    //za skokove nije potrebno drzati taster
    glutIgnoreKeyRepeat(1);     
    //na pocetku nijedan taster nije pritisnut
    jdown = 0;
    ldown = 0;
    adown = 0;
    ddown = 0;
    
	glEnable(GL_DEPTH_TEST);
    
    animating_left = 0;  //inicijalizacija animacije skoka leve
    animating_right = 0; //i desne loptice

    srand(time(NULL));  //seed za nasumicne brojeve koji ce nam odredjivati polozaje prepreka
    
    //inicijalizacija parametara
    game_started = 0;
    
    //inicijalizacija tekstura
    initialize();

	glutMainLoop();

return 0;

}


void on_reshape(int width,int height){	
    //prilikom promene velicine prozora treba ponovo podesiti projekciju
	window_width = width;
	window_height = height;
    
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
	gluPerspective(80, window_width/(float)window_height, 0.1, 20);
}



void on_display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
    //animacija kamere pri prvom pokretanju igre 
    viewParam = viewParam < 3 ? viewParam : 3; 
	gluLookAt(1.5, 4 - viewParam, 0.5 + viewParam, 1.5, 0, 0, 0, 1, 0);
    
    //osvetljenje i materijali 
    //(koristimo teksture na svemu sem na lopticama tako da se ovo odnosi samo na loptice)
    GLfloat light_pos[] = { 1.5, 2, 4, 0 };
    GLfloat light_ambi[] = { 0.2, 0.2, 0.2, 1 };
    GLfloat light_diff[] = { 0.6, 0.6, 0.6, 1 };
    GLfloat light_spec[] = { 1, 1, 1, 1 };
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambi);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diff);
    glLightfv(GL_LIGHT0,GL_SPECULAR,light_spec);
    
    GLfloat material_diffuse[] = { 0.7, 0.7, 0.7, 1 };
    GLfloat material_specular[] = { 1, 1, 1, 1 };
    int shininess = 8;
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
    
    //crtanje traka sa preprekama
    draw_lanes();
	

    //ako je igra pokrenuta i ako je pritisnut taster 'a' i ako pomeranjem leve loptice
    //u levo za 0.05 ne dolazi do preklapanja loptica, treba izvrsiti tu izmenu, analogno i za tastere 'd','j' i 'l'
    if (game_started && adown && !are_players_coliding(lbx - 0.05, lby, lbz, rbx, rby, rbz)){   
                lbx -= 0.05;
    }
    if (game_started && ddown && !are_players_coliding(lbx + 0.05, lby, lbz, rbx, rby, rbz)){
                lbx += 0.05;
    }
    if (game_started && jdown && !are_players_coliding(lbx, lby, lbz, rbx - 0.05, rby, rbz)){
                rbx -= 0.05;
    }
    if (game_started && ldown && !are_players_coliding(lbx, lby, lbz, rbx + 0.05, rby, rbz)){
                rbx += 0.05;
    }
    

	//crtanje loptica
	draw_balls();
    
    //iscrtavamo health drop na svakih 16 (moze i neki drugi broj ali mora biti broj deljiv sa 4 zbog nacina dodele poena) 
    //poena da nebi bili previse cesti (ova provera je u obstacles.c )
    //moze se desiti da se on preklapa sa nekom od prepreka i to ga cini redjim
    draw_health_drop();
	
    //iscrtavanje nasumicnih prepreka
    draw_obstacles();
    
    //crtanje neba
    draw_sky();  
    
    //privremeno se iskljucuje osvetljenje da bi se postigla zeljena (bela) boja tekstualnih poruka
    //svetlo ce se ponovo ukljuciti pri sledecem pozivu on_display funckije
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    
    //ako jos uvek nismo poceli igru, treba priakazati odgovarajuce poruku
    if (viewParam < 0.3){
        
        //za ispis tekstualnih poruka portebno je promeniti presliakvanje sa projektivnog na ortografsko sa odgovarajucim parametrima
        //kostruisati odgovarajucu poruku, pozicionirati i bitmapirati je i na kraju se vratiti na projektivno presliakvanje
        //slicno i za ostale poruke u kodu ispod
        glColor3f(1, 1, 1);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, window_width, 0, window_height);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
    
        char menu_msg[30];
        sprintf(menu_msg,"JUMPING BALLS v1.0");
        glRasterPos2i(window_width/2-120, window_height/2);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, menu_msg);
    
        char menu_msg1[30];
        sprintf(menu_msg1,"Press 'p' to start");
        glRasterPos2i(window_width/2-70, window_height/2.3);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, menu_msg1);
    
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        
    }
    
    
    //ako je igra u toku, ili ako smo pauzirali igru treba u gornjem desnom uglu prikazati
    //trenutni broj poena i trenutnu brzinu kretanja prepreka
    //i u gornjem levom broj hp
    if(game_started || paused){
        
        glColor3f(1, 1, 1);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, window_width, 0, window_height);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
    
        //ispis poena
        char score_msg[20];
        sprintf(score_msg,"Score:  %d",score);
        glRasterPos2i(window_width - 200, window_height - 50);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, score_msg);
    
        //ispis brzine prepreka
        char obstacle_speed[40];
        sprintf(obstacle_speed,"Obstacle Speed:  %.2f",speed_coef);
        glRasterPos2i(window_width - 200, window_height - 75);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, obstacle_speed);
        
        //remaining hp
        char hp[30];
        sprintf(hp,"Remaing health:  %d",health);
        glRasterPos2i(50, window_height - 50);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, hp);
    
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
    }
    
    //game paused ispis
    if(paused){
       glColor3f(1, 1, 1);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, window_width, 0, window_height);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
    
        char pause_msg[20];
        sprintf(pause_msg,"PAUSED");
        glRasterPos2i(window_width / 2 - 50, window_height / 2);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, pause_msg);
    
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix(); 
    }
    
    //uvecavamo hp brojac ako je loptica dotakla health_drop i ako je health manji od maksimalne dozvoljene vrednosti (3) 
    //i ako detecting=0 (tj ako se loptica trenutno ne sece sa nekom preprekom. Ovo je potretno zbog
    //slucaja gde se centri health drop-a i prepreka nalaze na istoj koordinati). 
    //should_be_drawn koristimo za sinhronizacuju animacija prepreka i health drop-a. Kada se pokupi, zelimo da hp objekat nestane (hz=6 je van vidnog polja)
    //i ako nebi postojala should_be_drawn promenljiva, sledece iscrtavanje hp objekta nebi bilo u istoj ravni kao prepreke, sto ne zelimo
    if (health_collision() && health < 3 && !detecting){
        hz = 6;
        should_be_drawn = 0;
        health ++;
        printf("picked up hp\n");
    }
    
    
    //ako igrac ima vise od 1hp, sudar sa preprekom treba obraditi malo drugacije posto se sudar registruje u svakom pozivu on_display funkcije.
    //Health umanjujemo nakon sto loptica skroz prodje kroz prepreku. Ako bi u kodu samo stajalo da se radi health--, sudar sa jednom
    //preprekom bi umanjio brojac potencijalno za 3,4,5... puta, zavisi koliko brzo se ond_display izvrsava sto bi dovelo do nepravilnog ponasanja programa
    if (health > 1){
        //ulaz u prepreku
        if (is_there_a_collision() && !detecting){
            detecting = 1;
        } 
        //izlaz iz prepreke
        if (!is_there_a_collision() && detecting){
            detecting = 0;
            health--;       //!! nakon sto loptica skroz prodje kroz prepreku
        }
    }
    else{ //ako ima bas 1hp, dovoljno je detektovati prvi kontakt loptice sa preprekom i tu odmah staviti health = 0
        if(is_there_a_collision()){
            health = 0;
        }
    }
    
    //bez obrzira na health, ako neka loptica ispadne sa terena, treba odmah prekinuti igru
    if(is_out_of_bounds()){
        health = 0;
    }
    
    //prekid igre ako je to potrebno
    if (health == 0){
            //prekidanje svih animacija
            game_started = 0;
            animating_left = 0;
            animating_right = 0;
        
            //ispis odgovarajucih poruka
            glColor3f(1, 1, 1);
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            gluOrtho2D(0, window_width, 0, window_height);
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
        
            //game over ispis
            char game_over_msg[50];
            sprintf(game_over_msg,"   GAME OVER!\nPress 'r' to try again");
            glRasterPos2i(window_width / 2 - 70, window_height / 2);
            glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, game_over_msg);
        
            //ispis osvojenih poena
            char score_msg[21];
            sprintf(score_msg,"      Your Score:  %d",score);
            glRasterPos2i(window_width / 2 - 70, window_height / 2.5);
            glutBitmapString(GLUT_BITMAP_HELVETICA_18, score_msg);
        
            glPopMatrix();
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
    }
	

	glutSwapBuffers();
}
