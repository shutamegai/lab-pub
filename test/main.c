// main.c

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "fractal.h"
#include "init.h"
#include "iteration.h"
#include "return.h"

// #define DEBUG_FRACTAL_PRINT
// #define DEBUG_FRACTAL_P_PRINT
// #define DEBUG_FRACTAL_GNUPLOT
#define DEBUG_PEAK_CHECK
// #define DEBUG_RETURN_TEST


#define STAGE 4


int main (void) {
// DEBUG -----------------------------------------
#ifndef DEBUG_RETURN_TEST
     //FILE *time_log;
     time_t  time_s, time_1, time_2, time_3, time_g;
     time(&time_s);
     int     edge_num=FRACTAL_edge(STAGE);
     // FRACTAL fractal_main[edge_num][edge_num];
     FRACTAL fractal_main;


// DEBUG -----------------------------------------
#ifdef DEBUG_FRACTAL_PRINT
     int m, n;
#endif //-----------------------------------------
     
     
// DEBUG -----------------------------------------
#ifdef DEBUG_FRACTAL_P_PRINT
     int    m, n;
     double all_p=0.0;
#endif //-----------------------------------------

     
// DEBUG -----------------------------------------
#ifdef DEBUG_FRACTAL_GNUPLOT
     int m, n;
#endif //-----------------------------------------


// DEBUG -----------------------------------------
#ifdef DEBUG_PEAK_CHECK
     int n;
#endif //-----------------------------------------


     // a memory area dynamically secured
     fractal_main.init        = malloc(edge_num * sizeof(int*));
     fractal_main.p           = malloc(edge_num * sizeof(double*));
     fractal_main.right_0     = malloc(edge_num * sizeof(double*));
     fractal_main.up_1        = malloc(edge_num * sizeof(double*));
     fractal_main.left_2      = malloc(edge_num * sizeof(double*));
     fractal_main.down_3      = malloc(edge_num * sizeof(double*));
     fractal_main.sub_right_0 = malloc(edge_num * sizeof(double*));
     fractal_main.sub_up_1    = malloc(edge_num * sizeof(double*));
     fractal_main.sub_left_2  = malloc(edge_num * sizeof(double*));
     fractal_main.sub_down_3  = malloc(edge_num * sizeof(double*));
     if (fractal_main.sub_down_3 == NULL) {
          printf("heap = NULL!\n"); exit(0);
     }
     
     for (n=0; n<edge_num; n++) {
          fractal_main.init[n]        = malloc(edge_num * sizeof(int));
          fractal_main.p[n]           = malloc(edge_num * sizeof(double));
          fractal_main.right_0[n]     = malloc(edge_num * sizeof(double));
          fractal_main.up_1[n]        = malloc(edge_num * sizeof(double));
          fractal_main.left_2[n]      = malloc(edge_num * sizeof(double));
          fractal_main.down_3[n]      = malloc(edge_num * sizeof(double));
          fractal_main.sub_right_0[n] = malloc(edge_num * sizeof(double));
          fractal_main.sub_up_1[n]    = malloc(edge_num * sizeof(double));
          fractal_main.sub_left_2[n]  = malloc(edge_num * sizeof(double));
          fractal_main.sub_down_3[n]  = malloc(edge_num * sizeof(double));
          if (fractal_main.sub_down_3[n] == NULL) {
               printf("heap = NULL!\n"); exit(0);
          }
     }
     
     
     // FRACTAL_generator
     FRACTAL_generator(STAGE, edge_num, fractal_main);
     time(&time_1);

     
// DEBUG -----------------------------------------
#ifdef DEBUG_FRACTAL_PRINT
     printf("STAGE = %d\n", STAGE);
     for (m=0; m<edge_num; m++) {
          for (n=0; n<edge_num; n++) printf("%d", fractal_main.init[m][n]);
          printf("\n");
     }
#endif //-----------------------------------------
     
     
     // FRACTAL_initializer
     FRACTAL_initializer(STAGE, edge_num, fractal_main);
     time(&time_2);


     // FRACTAL_probability
     FRACTAL_probability(STAGE, edge_num, fractal_main);
     time(&time_3);


// DEBUG -----------------------------------------
#ifdef DEBUG_FRACTAL_P_PRINT
     // printf("STAGE = %d\n", STAGE);
     for (n=0; n<edge_num; n++) {
          for (m=0; m<edge_num; m++) {
               all_p += fractal_main.p[m][n];
               // observe
               printf("%8d %8d %20.15f\n", n,     m, fractal_main.p[m][n]);
          }
          printf("\n");
     }
     printf("all_probability = %f\n", all_p);
#endif //-----------------------------------------

     
// DEBUG -----------------------------------------
#ifdef DEBUG_FRACTAL_GNUPLOT
     // printf("STAGE = %d\n", STAGE);
     for (n=0; n<edge_num; n++) {
          for (m=0; m<edge_num; m++) {
               // observe
               printf("%8d %8d %20.15f\n", n,     m, fractal_main.p[m][n]);
               if (m!=edge_num) {
               printf("%8d %8d %20.15f\n", n,   m+1, fractal_main.p[m][n]);
               }
          }
          printf("\n");

          for (m=0; m<edge_num; m++) {
               // observe
               printf("%8d %8d %20.15f\n", n+1,   m, fractal_main.p[m][n]);
               if (m!=edge_num) {
               printf("%8d %8d %20.15f\n", n+1, m+1, fractal_main.p[m][n]);
               }
          }
          printf("\n");
     }
#endif //-----------------------------------------


     // memory free
     for (n=0; n<edge_num; n++) {
          free(fractal_main.init       [n]);
          free(fractal_main.p          [n]);
          free(fractal_main.right_0    [n]);
          free(fractal_main.up_1       [n]);
          free(fractal_main.left_2     [n]);
          free(fractal_main.down_3     [n]);
          free(fractal_main.sub_right_0[n]);
          free(fractal_main.sub_up_1   [n]);
          free(fractal_main.sub_left_2 [n]);
          free(fractal_main.sub_down_3 [n]);
     }
     
     free(fractal_main.init);
     free(fractal_main.p);
     free(fractal_main.right_0);
     free(fractal_main.up_1);
     free(fractal_main.left_2);
     free(fractal_main.down_3);
     free(fractal_main.sub_right_0);
     free(fractal_main.sub_up_1);
     free(fractal_main.sub_left_2);
     free(fractal_main.sub_down_3);
     
     // time
     time(&time_g);
     /*
     time_log = fopen(".//bin//debug//time.log", "w");
     fprintf(time_log, "start: %.24s\n", ctime(&time_s));
     fprintf(time_log, "time1: %.24s\n", ctime(&time_1));
     fprintf(time_log, "time2: %.24s\n", ctime(&time_2));
     fprintf(time_log, "time3: %.24s\n", ctime(&time_3));
     fprintf(time_log, "goal : %.24s\n", ctime(&time_g));
     fprintf(time_log, "diff : %.6f\n" , difftime(time_g, time_s));
     fclose(time_log);
     */
#endif //-----------------------------------------


// DEBUG -----------------------------------------
#ifdef DEBUG_RETURN_TEST
     int     n;
     int     edge_num=FRACTAL_edge(STAGE);
     FRACTAL fractal_main;


     // a memory area dynamically secured
     fractal_main.init = malloc(edge_num * sizeof(int*));
     for (n=0; n<edge_num; n++) {
          fractal_main.init[n] = malloc(edge_num * sizeof(int));
          if (fractal_main.init[n] == NULL) {
               printf("heap = NULL!\n"); exit(0);
          }
     }

     // FRACTAL_generator
     FRACTAL_generator(STAGE, edge_num, fractal_main);

     
     // FRACTAL_return
     FRACTAL_return(STAGE, edge_num, fractal_main);
#endif //-----------------------------------------

     
     return 0;
}
