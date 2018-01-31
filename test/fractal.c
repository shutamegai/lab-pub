// fractal.c

#include <stdio.h>
#include <stdlib.h>
#include "fractal.h"

// #define DEBUG_FRACTAL_PRINT
// int edge_num;


int FRACTAL_edge (int FRACTAL_stage) {
     int vertex_edge=1;
     int i;

     
     for (i=0; i<FRACTAL_stage; i++) vertex_edge *= 3;

     return vertex_edge;
}


void FRACTAL_generator (int FRACTAL_stage_num, int num, FRACTAL fractal) {
     int i, m, n, a, b;
     int times;
     int quotient1, quotient2;
     // edge_num=FRACTAL_edge(FRACTAL_stage_num);

     
     // initalization
     for (m=0; m<num; m++) {
          for (n=0; n<num; n++) fractal.init[m][n] = 1;
     }
     

     // make fractal
     quotient1 = num;
     for (i=0; i<FRACTAL_stage_num; i++) {
          times      = num/quotient1;
          quotient1 /= 3;
          quotient2  = quotient1*2;
          
          for (a=0; a<times; a++) {
          for (b=0; b<times; b++) {
               for (m=quotient1; m<quotient2; m++) {
               for (n=quotient1; n<quotient2; n++) {
                    fractal.init[m+(3*a*quotient1)][n+(3*b*quotient1)] = 0;
               }
               }
          }
          }
          
     }

       
// DEBUG -----------------------------------------
#ifdef DEBUG_FRACTAL_PRINT
     printf("STAGE = %d\n", FRACTAL_stage_num);
     for (m=0; m<num; m++) {
          for (n=0; n<num; n++) printf("%d", fractal.init[m][n]);
          printf("\n");
     }
#endif //-----------------------------------------
     
     return;
}
