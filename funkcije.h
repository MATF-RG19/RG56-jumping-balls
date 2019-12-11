#ifndef __FUNKCIJE__
#define __FUNKCIJE__

//pomocne funkcije
void drawCoord(void);

//glavne funkcije
void on_reshape(int width,int height);
void on_display(void);
void on_keyboard(unsigned char key, int x, int y);
void on_timer_left (int value);
void on_timer_right(int value);

#endif

