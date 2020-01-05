#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "funkcije.h"

#define TIMER_INTERVAL 20
#define TIMER_ID4  4 // za animaciju ispada leve loptice
#define TIMER_ID5  5 // za animaciju ispada desne loptice

extern float o1x, o1y, o1z;  //koordinate prve prepreke
extern float o2x, o2y, o2z;  //koordinate druge prepreke
extern float o3x, o3y, o3z;  //koordinate trece prepreke
extern float o4x, o4y, o4z;  //koordinate cetvrte prepreke

//koordinate za levu (lbx,lby,lbz)  i desnu (rbx,rby,rbz) lopticu
extern GLfloat lbx, lby, lbz;
extern GLfloat rbx, rby, rbz;

//trenutno stanje hp-a
extern int health;
//koordinate za health drop
extern float hx, hy, hz;
//promenljive koje oznacavaju detekciju sudara za slucaj hp>1 su potrebne i ovde
extern int not_detecting, detecting;

//parametri animacija za slucaj kada neka od loptica ispadne sa trake
int bounds_animation_left = 0;
int bounds_animation_right = 0;

int is_there_a_collision(){
    
    //proverava se da li je duzina vektora odredjenog centrima objekata na sceni <= 0.6 
    //(0.6 = poluprecnik lopte + otprilike pola stranice prepreke nakon skaliranja pri iscrtavanju)
    
    if(  sqrt(pow(lbx-o1x, 2) + pow(lby-o1y, 2) + pow(lbz-o1z, 2)) <= 0.6 ||
         sqrt(pow(lbx-o2x, 2) + pow(lby-o2y, 2) + pow(lbz-o2z, 2)) <= 0.6 ||
         sqrt(pow(lbx-o3x, 2) + pow(lby-o3y, 2) + pow(lbz-o3z, 2)) <= 0.6 ||
         sqrt(pow(lbx-o4x, 2) + pow(lby-o4y, 2) + pow(lbz-o4z, 2)) <= 0.6 ||
         sqrt(pow(rbx-o1x, 2) + pow(rby-o1y, 2) + pow(rbz-o1z, 2)) <= 0.6 ||
         sqrt(pow(rbx-o2x, 2) + pow(rby-o2y, 2) + pow(rbz-o2z, 2)) <= 0.6 ||
         sqrt(pow(rbx-o3x, 2) + pow(rby-o3y, 2) + pow(rbz-o3z, 2)) <= 0.6 ||
         sqrt(pow(rbx-o4x, 2) + pow(rby-o4y, 2) + pow(rbz-o4z, 2)) <= 0.6
      ){
        
        printf("collison detected\n");
        return 1;
    } 
    
    //nema nikakve kolizije
    return 0;
}

//provera da li je neka od loptica ispala sa traka
//ako jeste treba odmah prekinuti igru bez obzira na remaining hp
int is_out_of_bounds(){
    if ( lbx <= 0 || lbx >= 3){
        bounds_animation_left = 1;
        lbx -= 0.05;
        glutTimerFunc(TIMER_INTERVAL, on_timer_out_of_bounds_left, TIMER_ID4);
        printf("out of bounds left\n");
        return 1;
    }
    
    if (rbx <= 0 || rbx >= 3){
        bounds_animation_right = 1;
        rbx += 0.05;
        glutTimerFunc(TIMER_INTERVAL, on_timer_out_of_bounds_right, TIMER_ID5);
        printf("out of bounds right\n");
        return 1;
    }
    
    //ako su obe loptice i dalje na trakama
    return 0;
}


//provera da li se loptice sudaraju
int are_players_coliding(GLfloat lbx, GLfloat lby, GLfloat lbz, GLfloat rbx, GLfloat rby, GLfloat rbz){
   
    //ako su loptice na razmaku <=0.4 (zbir njihovih poluprenika ), ne treba ih pomerati
   if( sqrt(pow(lbx - rbx, 2) + pow(lby - rby, 2) + pow(lbz - rbz, 2)) <= 0.4 || 
       sqrt(pow(rbx - lbx, 2) + pow(rby - lby, 2) + pow(rbz - lbz, 2)) <= 0.4
   ){
        printf("player collision\n");
        return 1;
   }
   
   //onemogucanavje da jedna loptica preskoci drugu dok je i dalje u vazduhu
   if( rbx - lbx <= 0.4 ){
        printf("illegal jump attempt\n");
        return 1;
   }
   
   //loptice se ne sudaraju
   return 0;
}

//provera da li neka od loptica dodiruje health drop
int health_collision(){
    
    if( sqrt(pow(lbx - hx, 2) + pow(lby - hy, 2) + pow(lbz - hz, 2)) <= 0.4 ||
        sqrt(pow(rbx - hx, 2) + pow(rby - hy, 2) + pow(rbz - hz, 2)) <= 0.4
    ){
        return 1;
    }
    
    //nijedna ne dodiruje
    return 0;
}

//animacija ispada leve loptice sa trake
void on_timer_out_of_bounds_left(int value){
    
    if(value != TIMER_ID4) {
            return;
    }
    
    //nema potrebe animirati u nedogled jer je loptica vidljiva otprilkike samo do y=-1.3 ravni
    if(lby > -1.3) lby -= 0.01;
    else bounds_animation_left=0; 
    
    glutPostRedisplay();
    if(bounds_animation_left){
        glutTimerFunc(TIMER_INTERVAL, on_timer_out_of_bounds_left, TIMER_ID4);        
    }
}


//animacija ispada desne loptice sa trake
void on_timer_out_of_bounds_right(int value){
    
    if(value != TIMER_ID5) {
            return;
    }
    
    //nema potrebe animirati u nedogled jer je loptica vidljiva otprilkike samo do y=-1.3 ravni
    if(rby > -1.3) rby -= 0.01;
    else bounds_animation_right = 0;
    
    glutPostRedisplay();
    if(bounds_animation_right){
        glutTimerFunc(TIMER_INTERVAL, on_timer_out_of_bounds_right, TIMER_ID5);        
    }
}

