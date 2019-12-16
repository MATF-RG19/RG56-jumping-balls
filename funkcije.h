#ifndef __FUNKCIJE__
#define __FUNKCIJE__


//glavne funkcije
void on_reshape(int width,int height);
void on_display(void);
void on_keyboard(unsigned char key, int x, int y);

//tajmer funkcije za animacije
void on_timer_left (int value);
void on_timer_right(int value);
void on_timer_obstacle(int value);

//pomocne funkcije
void drawCoord(void);
void draw_obstacles(void);

#endif

