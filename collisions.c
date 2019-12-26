#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "funkcije.h"

extern float o1x,o1y,o1z;  //koordinate prve prepreke
extern float o2x,o2y,o2z;  //koordinate druge prepreke
extern float o3x,o3y,o3z;  //koordinate trece prepreke
extern float o4x,o4y,o4z;  //koordinate cetvrte prepreke

//koordinate za levu (lbx,lby,lbz)  i desnu (rbx,rby,rbz) lopticu
extern GLfloat lbx, lby, lbz;
extern GLfloat rbx, rby, rbz;

int is_there_a_collision(){
    
    //proverava se da li je duzina vektora odredjenog centrima objekata na sceni <=0.7 
    //(0.7=poluprecnik lopte + pola stranice prepreke)
    
    if(  sqrt(pow(lbx-o1x,2)+pow(lby-o1y,2)+pow(lbz-o1z,2)) <= 0.6 ||
         sqrt(pow(lbx-o2x,2)+pow(lby-o2y,2)+pow(lbz-o2z,2)) <= 0.6 ||
         sqrt(pow(lbx-o3x,2)+pow(lby-o3y,2)+pow(lbz-o3z,2)) <= 0.6 ||
         sqrt(pow(lbx-o4x,2)+pow(lby-o4y,2)+pow(lbz-o4z,2)) <= 0.6 ||
         sqrt(pow(rbx-o1x,2)+pow(rby-o1y,2)+pow(rbz-o1z,2)) <= 0.6 ||
         sqrt(pow(rbx-o2x,2)+pow(rby-o2y,2)+pow(rbz-o2z,2)) <= 0.6 ||
         sqrt(pow(rbx-o3x,2)+pow(rby-o3y,2)+pow(rbz-o3z,2)) <= 0.6 ||
         sqrt(pow(rbx-o4x,2)+pow(rby-o4y,2)+pow(rbz-o4z,2)) <= 0.6
      ){
        
        printf("collison detected\n");
        return 1;
    }
    
    //ako je bilo koja loptica izasla sa traka
    if ( lbx<=0 || lbx>=3 || rbx<=0 || rbx>=3){
        printf("out of bounds\n");
        return 1;
    }
    
    return 0;
}


int are_players_coliding(GLfloat lbx, GLfloat lby, GLfloat lbz, GLfloat rbx, GLfloat rby, GLfloat rbz){
   
    //ako su loptice na razmaku <=0.4 (zbir njihovih poluprenika ), ne treba ih pomerati
   if( sqrt(pow(lbx-rbx,2)+pow(lby-rby,2)+pow(lbz-rbz,2)) <= 0.4 || 
       sqrt(pow(rbx-lbx,2)+pow(rby-lby,2)+pow(rbz-lbz,2)) <= 0.4
   ){
        printf("player collision\n");
        return 1;
   }
   
   //onemogucanavje da jedna loptica preskoci drugu
   if( rbx-lbx <= 0.4 ){
        printf("illegal jump attempt\n");
        return 1;
   }
   
   return 0;
}


