// iteration.c

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include "fractal.h"
#include "init.h"
#include "iteration.h"

#define DEBUG_ITERATION
// #define DEBUG_MARK_POINT
#define DEBUG_PEAK_CHECK
// #define DEBUG_GIF

#define LOOP 999999


void FRACTAL_probability (int FRACTAL_stage_num, int num, FRACTAL fractal) {
     int m, n;

     FILE   *time_log;
     time_t  time_s, time_g;
     clock_t s, g, time_1, time_2, time_3, time_4, time_5;

     time(&time_s);
     s = clock();


// DEBUG -----------------------------------------
#ifdef DEBUG_PEAK_CHECK
     int    times;
     double mean;
#else //------------------------------------------
     int    times;
     double mean;
#endif //-----------------------------------------


// DEBUG -----------------------------------------
#ifdef DEBUG_GIF
     FILE *matrix_gif;
     char  matrix_name[40];
#endif //-----------------------------------------
     
     
     // initalization
     for (m=0; m<num; m++) {
     for (n=0; n<num; n++) {
          if (fractal.init[m][n] == 1) {
               fractal.right_0[m][n] = init_p;
               fractal.up_1   [m][n] = init_p;
               fractal.left_2 [m][n] = init_p;
               fractal.down_3 [m][n] = init_p;
          } else {
               fractal.right_0[m][n] = 0.0;
               fractal.up_1   [m][n] = 0.0;
               fractal.left_2 [m][n] = 0.0;
               fractal.down_3 [m][n] = 0.0;
          }
     }
     }
     time_1 = clock();


// DEBUG -----------------------------------------
#ifdef DEBUG_MARK_POINT
      for (m=0; m<num; m++) {
      for (n=0; n<num; n++) {
           if (fractal.init[m][n] == 1) {
           if (m==((num/3)-1) && n==((num/3)-1)) {
                fractal.right_0[m][n] = 10;
                fractal.up_1   [m][n] = 10;
                fractal.left_2 [m][n] = 10;
                fractal.down_3 [m][n] = 10;
           }
           }
      }
      }
#endif //-----------------------------------------
      

// DEBUG -----------------------------------------
#ifdef DEBUG_PEAK_CHECK
     // iteration
     for (times=0; times<LOOP; times++) {
#else //------------------------------------------
     // iteration
          for (times=0; times<200/*=(int)(sqrt(node_sum))*/; times++) {
#endif //-----------------------------------------
          
// DEBUG -----------------------------------------
#ifdef DEBUG_ITERATION
#pragma omp parallel for private(n)
          for (m=0; m<num; m++) {
// #pragma vector always
          for (n=0; n<num; n++) {
               if (fractal.init[m][n] == 1) {
                    mean = (fractal.right_0[m][n] + fractal.up_1  [m][n]
                          + fractal.left_2 [m][n] + fractal.down_3[m][n])*0.25;

                    fractal.sub_right_0[m][n] = 2*mean - fractal.right_0[m][n];
                    fractal.sub_up_1   [m][n] = 2*mean - fractal.up_1   [m][n];
                    fractal.sub_left_2 [m][n] = 2*mean - fractal.left_2 [m][n];
                    fractal.sub_down_3 [m][n] = 2*mean - fractal.down_3 [m][n];
               }
          }              
          }

          m = (num/3)-1; n = (num/3)-1;
          
          fractal.sub_right_0[m][n] = -fractal.right_0[m][n];
          fractal.sub_up_1   [m][n] = -fractal.up_1   [m][n];
          fractal.sub_left_2 [m][n] = -fractal.left_2 [m][n];
          fractal.sub_down_3 [m][n] = -fractal.down_3 [m][n];
          
          if (times==0) time_2 = clock();
          
#pragma omp parallel for private(n)
          for (m=0; m<num; m++) {
// #pragma vector always
          for (n=0; n<num; n++) {
               if (fractal.init[m][n] == 1) {
                    // right_0
                    if (n==(num-1) || fractal.init[m][n+1]==0) {
                         fractal.right_0[m][n]   = fractal.sub_right_0[m][n];
                    } else {
                         fractal.left_2 [m][n+1] = fractal.sub_right_0[m][n];
                    }
                    // up_1
                    if (m==0 || fractal.init[m-1][n]==0) {
                         fractal.up_1   [m][n]   = fractal.sub_up_1   [m][n];
                    } else {
                         fractal.down_3 [m-1][n] = fractal.sub_up_1   [m][n];
                    }
                    // left_2
                    if (n==0 || fractal.init[m][n-1]==0) {
                         fractal.left_2 [m][n]   = fractal.sub_left_2 [m][n];
                    } else {
                         fractal.right_0[m][n-1] = fractal.sub_left_2 [m][n];
                    }
                    // down_3
                    if (m==(num-1) || fractal.init[m+1][n]==0) {
                         fractal.down_3 [m][n]   = fractal.sub_down_3 [m][n];
                    } else {
                         fractal.up_1   [m+1][n] = fractal.sub_down_3 [m][n];
                    }
               }
          }
          }
          
          if (times==0) time_3 = clock();


// DEBUG -----------------------------------------
#ifdef DEBUG_PEAK_CHECK
          // |0> + |1> + |2> + |3>
/*
#pragma omp parallel for private(n)
          for (m=0; m<num; m++) {
// #pragma vector always
          for (n=0; n<num; n++) {
               fractal.p[m][n]  = 0.0;
               
               fractal.p[m][n] += pow(fractal.right_0[m][n], 2);
               fractal.p[m][n] += pow(fractal.up_1   [m][n], 2);
               fractal.p[m][n] += pow(fractal.left_2 [m][n], 2);
               fractal.p[m][n] += pow(fractal.down_3 [m][n], 2);
          }
          }
*/
          m = (num/3)-1; n = (num/3)-1;
          fractal.p[m][n]  = 0.0;
          
          fractal.p[m][n] += pow(fractal.right_0[m][n], 2);
          fractal.p[m][n] += pow(fractal.up_1   [m][n], 2);
          fractal.p[m][n] += pow(fractal.left_2 [m][n], 2);
          fractal.p[m][n] += pow(fractal.down_3 [m][n], 2);
          
          if (times==0) printf("%6d %20.15f\n", times, fractal.p[m][n]);
          printf("%6d %20.15f\n", times+1, fractal.p[m][n]);
          
          if (times==0) time_4 = clock();


// DEBUG -----------------------------------------
#ifdef DEBUG_GIF
          // GIF
          sprintf(matrix_name, ".//bin//data//matrix//%d.dat", times);          
          
          matrix_gif = fopen(matrix_name, "w");

// #pragma omp parallel for private(m)
          for (n=0; n<num; n++) {
// #pragma vector always
               for (m=0; m<num; m++) {
                    // observe
                    fprintf(matrix_gif, "%8d %8d %20.15f\n",
                            n, m, fractal.p[m][n]);
                    if (m!=num) {
                         fprintf(matrix_gif, "%8d %8d %20.15f\n", n, m+1, fractal.p[m][n]);
                    }
               }
               fprintf(matrix_gif, "\n");

// #pragma vector always
               for (m=0; m<num; m++) {
                    // observe
                    fprintf(matrix_gif, "%8d %8d %20.15f\n", n+1, m, fractal.p[m][n]);
                    if (m!=num) {
                         fprintf(matrix_gif, "%8d %8d %20.15f\n", n+1, m+1, fractal.p[m][n]);
                    }
               }
               fprintf(matrix_gif, "\n");
          }

          fclose(matrix_gif);
#endif //-----------------------------------------
#endif //-----------------------------------------

          
     }
#endif //-----------------------------------------


     // |0> + |1> + |2> + |3>
     for (m=0; m<num; m++) {
          for (n=0; n<num; n++) {
               fractal.p[m][n] += pow(fractal.right_0[m][n], 2);
               fractal.p[m][n] += pow(fractal.up_1   [m][n], 2);
               fractal.p[m][n] += pow(fractal.left_2 [m][n], 2);
               fractal.p[m][n] += pow(fractal.down_3 [m][n], 2);
          }
     }
     time_5 = clock();

     // time
     time(&time_g);
     g = clock();
     time_log = fopen(".//bin//debug//time.log", "w");
     fprintf(time_log, "start: %.24s\n", ctime(&time_s));
     fprintf(time_log, "time1: %f\n"   , (double)(time_1-s)     /CLOCKS_PER_SEC);
     fprintf(time_log, "time2: %f\n"   , (double)(time_2-time_1)/CLOCKS_PER_SEC);
     fprintf(time_log, "time3: %f\n"   , (double)(time_3-time_2)/CLOCKS_PER_SEC);
     fprintf(time_log, "time4: %f\n"   , (double)(time_4-time_3)/CLOCKS_PER_SEC);
     fprintf(time_log, "time5: %f\n"   , (double)(time_5-time_4)/CLOCKS_PER_SEC);
     fprintf(time_log, "goal : %.24s\n", ctime(&time_g));
     fprintf(time_log, "diff : %.6f\n" , difftime(time_g, time_s));
     fclose(time_log);

     return;
}
