jumping_balls: main.c jumps.c draw_calls.c obstacles.c collisions.c image.c funkcije.h image.h
	gcc -Wall main.c jumps.c draw_calls.c obstacles.c collisions.c image.c -lGL -lGLU -lglut -lm -o jumping_balls 
