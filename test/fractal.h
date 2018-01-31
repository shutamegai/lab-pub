// fractal.h

#ifndef FRACTAL_H
#define FRACTAL_H


typedef struct {
     int    **init;
     double **p;
     double **right_0;
     double **up_1;
     double **left_2;
     double **down_3;
     double **sub_right_0;
     double **sub_up_1;
     double **sub_left_2;
     double **sub_down_3;
} FRACTAL;


int  FRACTAL_edge     (int);
void FRACTAL_generator(int, int num, FRACTAL fractal);


// extern int edge_num;


#endif
