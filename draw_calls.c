#include <GL/glut.h>
#include "funkcije.h"

//niz imena tekstura koje se koriste
extern GLuint names[];

//pozicije za levu (lbx,lby,lbz)  i desnu (rbx,rby,rbz) lopticu
extern GLfloat lbx, lby, lbz;
extern GLfloat rbx, rby, rbz;

extern float o1x, o1y, o1z;  //koordinate prve prepreke
extern float o2x, o2y, o2z;  //koordinate druge prepreke
extern float o3x, o3y, o3z;  //koordinate trece prepreke
extern float o4x, o4y, o4z;  //koordinate cetvrte prepreke

extern float hx, hy, hz; //koordinate za health drop

//iscrtavanje terena
void draw_lanes(){
    glPushMatrix();   //prva traka sa preprekama (skroz levo), ima teksturu trave
        glBindTexture(GL_TEXTURE_2D, names[0]);
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(0, 0, 5);
        
            glTexCoord2f(0.9, 0);
            glVertex3f(1, 0, 5);
        
            glTexCoord2f(0.9, 22);
            glVertex3f(1, 0, -30);
        
            glTexCoord2f(0, 22);
            glVertex3f(0, 0, -30);
        glEnd();   
        glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	glPushMatrix();   //druga traka sa preprekama  (srednja), ima teksturu kamencica
        glBindTexture(GL_TEXTURE_2D, names[1]);
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(1, 0, 5);
        
            glTexCoord2f(0.9, 0);
            glVertex3f(2, 0, 5);
                
            glTexCoord2f(0.9, 22);
            glVertex3f(2, 0, -30);
        
            glTexCoord2f(0, 22);
            glVertex3f(1, 0, -30);
        glEnd();   
        glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	glPushMatrix();   //treca traka sa preprekama (skroz denso), ima teksturu trave
        glBindTexture(GL_TEXTURE_2D, names[0]);
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(2, 0, 5);
        
            glTexCoord2f(0.9, 0);
            glVertex3f(3, 0, 5);
        
            glTexCoord2f(0.9, 22);
            glVertex3f(3, 0, -30);
        
            glTexCoord2f(0, 22);
            glVertex3f(2, 0, -30);
        glEnd();   
        glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}


void draw_balls(){
    
    //leva loptica
    glPushMatrix();   
        glTranslatef(lbx, lby, lbz);
        glutSolidSphere(0.2, 50, 50);
	glPopMatrix();

    //desna loptica
	glPushMatrix();   
        glTranslatef(rbx, rby, rbz);
        glutSolidSphere(0.2, 50, 50);
	glPopMatrix();
}

void draw_health_drop(){
    glPushMatrix();
    //svetlo se privremeno iskljucuje i health drop se namesta da bude crvene boje
    //moglo je i sa manje ovih push i pop matrica ali mislim da je ovako citljivije
    glDisable(GL_LIGHTING);
    glColor3f(1, 0, 0);
        glTranslatef(hx, hy, hz);
        glPushMatrix();
            glScalef(3, 1, 1);
            glutSolidCube(0.1);
        glPopMatrix();
        glPushMatrix();
            glScalef(1, 3, 1);
            glutSolidCube(0.1);
        glPopMatrix();    
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void draw_obstacles(){
    //zadnje i donje strane prepreka se ne crtaju jer nisu vidljive tokom igre
    
    //prva prepreka
    glPushMatrix();
        glTranslatef(o1x, o1y, o1z);
        glScalef(1, 0.7, 0.5);
      
        glBindTexture(GL_TEXTURE_2D, names[2]);   //prednja strana prepreke
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5, -0.5, 0.5);
        
            glTexCoord2f(1, 0);
            glVertex3f(0.5, -0.5, 0.5);
        
            glTexCoord2f(1, 1);
            glVertex3f(0.5, 0.5, 0.5);
        
            glTexCoord2f(0, 1);
            glVertex3f(-0.5, 0.5, 0.5);
        glEnd();   
     
        glBindTexture(GL_TEXTURE_2D, names[2]);  //desna strana prepreke
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(0.5, -0.5, 0.5);
        
            glTexCoord2f(1, 0);
            glVertex3f(0.5, -0.5, -0.5);
        
            glTexCoord2f(1, 1);
            glVertex3f(0.5, 0.5, -0.5);
        
            glTexCoord2f(0, 1);
            glVertex3f(0.5, 0.5, 0.5);
        glEnd(); 
     
        glBindTexture(GL_TEXTURE_2D, names[2]);  //leva strana prepreke
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5, -0.5, -0.5);
        
            glTexCoord2f(1, 0);
            glVertex3f(-0.5, -0.5, 0.5);
        
            glTexCoord2f(1, 1);
            glVertex3f(-0.5, 0.5, 0.5);
        
            glTexCoord2f(0, 1);
            glVertex3f(-0.5, 0.5, -0.5);
        glEnd();
     
        glBindTexture(GL_TEXTURE_2D, names[2]);  //gornja strana prepreke
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5, 0.5, 0.5);
        
            glTexCoord2f(1, 0);
            glVertex3f(0.5, 0.5, 0.5);
        
            glTexCoord2f(1, 1);
            glVertex3f(0.5, 0.5, -0.5);
        
            glTexCoord2f(0, 1);
            glVertex3f(-0.5, 0.5, -0.5);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

	//druga prepreka
    glPushMatrix();
        glTranslatef(o2x, o2y, o2z);
        glScalef(1, 0.7, 0.5);
      
        glBindTexture(GL_TEXTURE_2D, names[2]);   //prednja strana prepreke
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5, -0.5, 0.5);
        
            glTexCoord2f(1, 0);
            glVertex3f(0.5, -0.5, 0.5);
        
            glTexCoord2f(1, 1);
            glVertex3f(0.5, 0.5, 0.5);
        
            glTexCoord2f(0, 1);
            glVertex3f(-0.5, 0.5, 0.5);
        glEnd();   
     
        glBindTexture(GL_TEXTURE_2D, names[2]);  //desna strana prepreke
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(0.5, -0.5, 0.5);
        
            glTexCoord2f(1, 0);
            glVertex3f(0.5, -0.5, -0.5);
        
            glTexCoord2f(1, 1);
            glVertex3f(0.5, 0.5, -0.5);
        
            glTexCoord2f(0, 1);
            glVertex3f(0.5, 0.5, 0.5);
        glEnd(); 
     
        glBindTexture(GL_TEXTURE_2D, names[2]);  //leva strana prepreke
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5, -0.5, -0.5);
        
            glTexCoord2f(1, 0);
            glVertex3f(-0.5, -0.5, 0.5);
        
            glTexCoord2f(1, 1);
            glVertex3f(-0.5, 0.5, 0.5);
         
            glTexCoord2f(0, 1);
            glVertex3f(-0.5, 0.5, -0.5);
        glEnd();
     
        glBindTexture(GL_TEXTURE_2D, names[2]);  //gornja strana prepreke
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5, 0.5, 0.5);
        
            glTexCoord2f(1, 0);
            glVertex3f(0.5, 0.5, 0.5);
        
            glTexCoord2f(1, 1);
            glVertex3f(0.5, 0.5, -0.5);
        
            glTexCoord2f(0, 1);
            glVertex3f(-0.5, 0.5, -0.5);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    //treca prepreka
    glPushMatrix();
        glTranslatef(o3x, o3y, o3z);
        glScalef(1, 0.7, 0.5);
      
        glBindTexture(GL_TEXTURE_2D, names[2]);   //prednja strana prepreke
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5, -0.5, 0.5);
        
            glTexCoord2f(1, 0);
            glVertex3f(0.5, -0.5, 0.5);
        
            glTexCoord2f(1, 1);
            glVertex3f(0.5, 0.5, 0.5);
        
            glTexCoord2f(0, 1);
            glVertex3f(-0.5, 0.5, 0.5);
        glEnd();   
     
        glBindTexture(GL_TEXTURE_2D, names[2]);  //desna strana prepreke
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(0.5, -0.5, 0.5);
        
            glTexCoord2f(1, 0);
            glVertex3f(0.5, -0.5, -0.5);
        
            glTexCoord2f(1, 1);
            glVertex3f(0.5, 0.5, -0.5);
        
            glTexCoord2f(0, 1);
            glVertex3f(0.5, 0.5, 0.5);
        glEnd(); 
     
        glBindTexture(GL_TEXTURE_2D, names[2]);  //leva strana prepreke
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5, -0.5, -0.5);
        
            glTexCoord2f(1, 0);
            glVertex3f(-0.5, -0.5, 0.5);
        
            glTexCoord2f(1, 1);
            glVertex3f(-0.5, 0.5, 0.5);
        
            glTexCoord2f(0, 1);
            glVertex3f(-0.5, 0.5, -0.5);
        glEnd();
     
        glBindTexture(GL_TEXTURE_2D, names[2]);  //gornja strana prepreke
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5, 0.5, 0.5);
        
            glTexCoord2f(1, 0);
            glVertex3f(0.5, 0.5, 0.5);
        
            glTexCoord2f(1, 1);
            glVertex3f(0.5, 0.5, -0.5);
        
            glTexCoord2f(0, 1);
            glVertex3f(-0.5, 0.5, -0.5);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
    
    //cetvrta prepreka
    glPushMatrix();
        glTranslatef(o4x, o4y, o4z);
        glScalef(1, 0.7, 0.5);
      
        glBindTexture(GL_TEXTURE_2D, names[2]);   //prednja strana prepreke
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5, -0.5, 0.5);
        
            glTexCoord2f(1, 0);
            glVertex3f(0.5, -0.5, 0.5);
        
            glTexCoord2f(1, 1);
            glVertex3f(0.5, 0.5, 0.5);
        
            glTexCoord2f(0, 1);
            glVertex3f(-0.5, 0.5, 0.5);
        glEnd();   
     
        glBindTexture(GL_TEXTURE_2D, names[2]);  //desna strana prepreke
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(0.5, -0.5, 0.5);
        
            glTexCoord2f(1, 0);
            glVertex3f(0.5, -0.5, -0.5);
        
            glTexCoord2f(1, 1);
            glVertex3f(0.5, 0.5, -0.5);
        
            glTexCoord2f(0, 1);
            glVertex3f(0.5, 0.5, 0.5);
        glEnd(); 
     
        glBindTexture(GL_TEXTURE_2D, names[2]);  //leva strana prepreke
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5, -0.5, -0.5);
        
            glTexCoord2f(1, 0);
            glVertex3f(-0.5, -0.5, 0.5);
        
            glTexCoord2f(1, 1);
            glVertex3f(-0.5, 0.5, 0.5);
        
            glTexCoord2f(0, 1);
            glVertex3f(-0.5, 0.5, -0.5);
        glEnd();
     
        glBindTexture(GL_TEXTURE_2D, names[2]);  //gornja strana prepreke
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(-0.5, 0.5, 0.5);
        
            glTexCoord2f(1, 0);
            glVertex3f(0.5, 0.5, 0.5);
        
            glTexCoord2f(1, 1);
            glVertex3f(0.5, 0.5, -0.5);
        
            glTexCoord2f(0, 1);
            glVertex3f(-0.5, 0.5, -0.5);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}


void draw_sky(){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, names[3]);  
        //sliku neba rotiramo izmenom texcoord
        //time psotizemo malo lepse povezivanje tekstura na ivicama
        
        //donji deo
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(-25, -5, 15);
        
            glTexCoord2f(1, 0);
            glVertex3f(28, -5, 15);
        
            glTexCoord2f(1, 1);
            glVertex3f(28, -5, -15);
        
            glTexCoord2f(0, 1);
            glVertex3f(-25, -5, -15);
        glEnd();
       
        //gornji deo
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 1);
            glVertex3f(-25, -5.1, -15);
        
            glTexCoord2f(1, 1);
            glVertex3f(28, -5.1, -15);
        
            glTexCoord2f(1, 0);
            glVertex3f(28, 15, -15);
    
            glTexCoord2f(0, 0);
            glVertex3f(-25, 15, -15);
        glEnd();
        
        //levi deo
        glBegin(GL_POLYGON);
            glTexCoord2f(1, 1);
            glVertex3f(-23, -5.1, 15);
        
            glTexCoord2f(0, 1);
            glVertex3f(-23, -5.1, -16);
        
            glTexCoord2f(0, 0);
            glVertex3f(-23, 15, -16);
    
            glTexCoord2f(1, 0);
            glVertex3f(-23, 15, 15);
        glEnd();
        
        //desni deo
        glBegin(GL_POLYGON);
            glTexCoord2f(1, 1);
            glVertex3f(27, -5.1, -15.1);
        
            glTexCoord2f(0, 1);
            glVertex3f(27, -5.1, 15);
        
            glTexCoord2f(0, 0);
            glVertex3f(27, 15, 15);
    
            glTexCoord2f(1, 0);
            glVertex3f(27, 15, -15.1);
        glEnd();
        
        glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
  }
