#ifndef __FUNKCIJE__
#define __FUNKCIJE__

//glavne funkcije
void on_reshape(int width, int height);
void on_display(void);
void on_keyboard(unsigned char key, int x, int y);
void on_keyboard_up(unsigned char key, int x, int y);

//tajmer funkcije za animacije
void on_timer_left (int value);
void on_timer_right(int value);
void on_timer_obstacle(int value);
void on_timer_out_of_bounds_left(int value);
void on_timer_out_of_bounds_right(int value);

//funkcije za iscrtavanje objekata
void draw_lanes(void);
void draw_balls(void);
void draw_health_drop(void);
void draw_obstacles(void);
void draw_sky(void);

//detekcija kolizija
int is_there_a_collision(void);
int is_out_of_bounds(void);
int are_players_coliding(GLfloat lbx, GLfloat lby, GLfloat lbz, GLfloat rbx, GLfloat rby, GLfloat rbz);
int health_collision(void);

#endif
