// init.c

#include <stdio.h>
#include <math.h>
#include "fractal.h"
#include "init.h"

// #define DEBUG_INITIAL_P

double init_p;
double node_sum;


void FRACTAL_initializer (int FRACTAL_stage_num, int num, FRACTAL fractal) {
     int m, n;


     // initalization
     for (m=0; m<num; m++) {
          for (n=0; n<num; n++) fractal.p[m][n] = 0.0;
     }
     
     for (m=0; m<num; m++) {
          for (n=0; n<num; n++) {
               if (fractal.init[m][n] == 1) node_sum++;
          }
     }

     init_p = 1/sqrt(4*node_sum);

     
// DEBUG -----------------------------------------
#ifdef DEBUG_INITIAL_P
     for (m=0; m<num; m++) {
          for (n=0; n<num; n++) {
               if (fractal.init[m][n] == 1) fractal.p[m][n] = init_p;
          }
     }
#endif //-----------------------------------------
     
     return;
}
