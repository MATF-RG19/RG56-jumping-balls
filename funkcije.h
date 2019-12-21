#ifndef __FUNKCIJE__
#define __FUNKCIJE__


//glavne funkcije
void on_reshape(int width,int height);
void on_display(void);
void on_keyboard(unsigned char key, int x, int y);
void on_keyboard_up(unsigned char key, int x, int y);

//tajmer funkcije za animacije
void on_timer_left (int value);
void on_timer_right(int value);
void on_timer_obstacle(int value);

//funkcije za iscrtavanje
void draw_obstacles(void);

//detekcija kolizija
int is_there_a_collision(void);
int are_players_coliding(GLfloat lbx, GLfloat lby, GLfloat lbz, GLfloat rbx, GLfloat rby, GLfloat rbz);


#endif
