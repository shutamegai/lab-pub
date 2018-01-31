// fft.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fftw3.h"

#define SIZE 10000000


int main (void) {
     FILE  *time_log;
     time_t time_s, time_g;
     time(&time_s);
     
     FILE  *fft_dat;
     int    num;
     double dat;

     double       *in;
     fftw_complex *out;
     fftw_plan     p;
     int           i=0;
     int           sample=0;
     double        scale = 1.0 / SIZE;

     double out_2r, out_2i, out_2c=0.0;
     double peak_t=0;

     size_t mem_size = sizeof(fftw_complex) * SIZE;

     
     in  = (double*)fftw_malloc(mem_size);
     out = (fftw_complex*)fftw_malloc(mem_size);

     
     fft_dat = fopen( ".//bin//data//stage//7//fractal_p.txt" , "r" );

     if (fft_dat == NULL) {
          printf("FILE ERROR!\n"); return 0;
     }
     
     while((fscanf(fft_dat, "%d%lf", &num, &dat)) != EOF ) sample++;

     rewind(fft_dat);
     
     while((fscanf(fft_dat, "%d%lf", &num, &dat)) != EOF ) {
          in[i]    = dat/* * (0.5-0.5*cos(i*2*M_PI/sample)) */;
          //in[i]    = sin(i*2*M_PI/400);
          //in[i][1] = 0.0;
          //printf("%5d  %lf\n", i, in[i]);
          i++;
     }

     p = fftw_plan_dft_r2c_1d(sample, in, out, FFTW_ESTIMATE);
     
     fclose(fft_dat);
     
     fftw_execute(p); /* repeat as needed */

     for(i=0; i<sample; i++) {
          /*
          for(int l=0; l<sample; l++) {
            out[i][0] +=  in[l]*cos(2*M_PI*l*i/sample);
            out[i][1] += -in[l]*sin(2*M_PI*l*i/sample);
          }
          */
          out_2r = out[i][0]*out[i][0];
          out_2i = out[i][1]*out[i][1];
          
          //if (i!=0) printf("%18.10f %18.10f\n", (double)(sample)/i, sqrt(out_2r+out_2i));
	 }
     out_2r = out[0][0]*out[0][0];
     out_2i = out[0][1]*out[0][1];

     //printf("%18.10f %18.10f\n", 0.0, sqrt(out_2r+out_2i));

     
     // peak
     for (i=2; i<(sample-1); i++) {
          if (out_2c<(out[i][0]*out[i][0]+out[i][1]*out[i][1])) {
               out_2c = out[i][0]*out[i][0]+out[i][1]*out[i][1];
               peak_t = (double)(sample)/i;
          }
     }

     
     fftw_destroy_plan(p);
     fftw_free(in); fftw_free(out);


     // time
     time(&time_g);
     time_log = fopen(".//bin//debug//time.log", "w");
     fprintf(time_log, "start: %.24s\n", ctime(&time_s));
     fprintf(time_log, "goal : %.24s\n", ctime(&time_g));
     fprintf(time_log, "diff : %.6f\n" , difftime(time_g, time_s));
     fprintf(time_log, "--------------------\n");
     fprintf(time_log, "peak : %.10f\n", peak_t);
     fclose(time_log);

     return 0;
}
