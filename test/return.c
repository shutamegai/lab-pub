// return.c

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include "fractal.h"
#include "init.h"
//#include "iteration.h"
#include "return.h"
#include "MT.h"

#define LOOP  50000000
#define LIMIT 10000000
#define STEPS 1000000


void FRACTAL_return (int FRACTAL_stage_num, int num, FRACTAL fractal) {
     const int origin=(num/3)-1;
           int m, n;
           int diff_x=origin, diff_y=origin;
           int return_times[STEPS];
           int r, iteration, max=10;

           FILE   *time_log;
           time_t  time_s, time_g;


     time(&time_s);
     init_genrand((unsigned)time(NULL));

     for (n=0; n<STEPS; n++) return_times[n] = 0;
     
//#pragma omp parallel for private(n)
     for (m=0; m<LOOP; m++) {
          diff_x = origin;
          diff_y = origin;
          iteration = 0;

          // random walk
#pragma vector always
          for (n=0; n<LIMIT; n++) {
               r = genrand_int31();
               switch (r%4) {
               case 0:
                    // right_0
                    if (diff_x!=(num-1) && fractal.init[diff_y][diff_x+1]!=0) {
                         diff_x += 1; iteration++;
                         if (diff_x==origin && diff_y==origin) return_times[iteration-1]++;
                    }
                    break;

               case 1:
                    // up_1
                    if (diff_y!=0       && fractal.init[diff_y-1][diff_x]!=0) {
                         diff_y -= 1; iteration++;
                         if (diff_x==origin && diff_y==origin) return_times[iteration-1]++;
                    }     
                    break;

               case 2:
                    // left_2
                    if (diff_x!=0       && fractal.init[diff_y][diff_x-1]!=0) {
                         diff_x -= 1; iteration++;
                         if (diff_x==origin && diff_y==origin) return_times[iteration-1]++;
                    }     
                    break;

               case 3:
                    // down_3
                    if (diff_y!=(num-1) && fractal.init[diff_y+1][diff_x]!=0) {
                         diff_y += 1; iteration++;
                         if (diff_x==origin && diff_y==origin) return_times[iteration-1]++;
                    }     
                    break;
                    
               }
               if (iteration==STEPS) break;
               // if (n==0) printf("int = %3d, x = %d, y = %d\n", r%4, diff_x, diff_y);
          }
          
     }

     for (n=0; n<STEPS; n++) {
          if ((n+1)%max == 0) {
               printf("%10d %15.10f %% %10d\n", n+1, 100*(double)(return_times[n])/LOOP, return_times[n]);
               max *= 5;
          }
     }

     // time
     time(&time_g);
     time_log = fopen(".//bin//debug//time.log", "w");
     fprintf(time_log, "start: %.24s\n", ctime(&time_s));
     fprintf(time_log, "goal : %.24s\n", ctime(&time_g));
     fprintf(time_log, "diff : %.6f\n" , difftime(time_g, time_s));
     fclose(time_log);
     
     return;
}
