/**   simulation program  **/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include "sim.h"




int main(int argc, const char** argv) {


  if(argc != 6) {
    printf("Please give give arguments: input_file_name \n");
    return -1;
          } 

int N = atoi(argv[1]);
const char* in_file = argv[2];
int nsteps = atoi(argv[3]);
int delta_t = atoi(argv[4]);
int graphics = atoi(argv[5]);

printf("%d\n",N);
printf("input_file_name = %s\n", in_file);
printf("%d\n",nsteps);
printf("%d\n",delta_t);
printf("%d\n", graphics);

printf("\n");

/* Open input file and determine its size. */
  double buf1[6*N];
  if(read_doubles_from_file(6*N, buf1, in_file) != 0){

    printf("Error reading file '%s'\n", in_file);
    return -1;
  }

    for(int i = 0; i < N; i++){
      printf("x%d: %0.10f\n",i,buf1[i*6+0]);
      x[i] = buf1[i*6+0];
      printf("y%d: %0.10f\n",i,buf1[i*6+1]);
      y[i] = buf1[i*6+1];
      printf("mass%d: %0.10f\n",i,buf1[i*6+2]);
      printf("vx%d: %0.10f\n",i,buf1[i*6+3]);
      vx[i] = buf1[i*6+3];
      printf("vy%d; %0.10f\n",i,buf1[i*6+4]);
      vy[i] = buf1[i*6+4];
      printf("brightness%d: %0.10f\n",i,buf1[i*6+5]);
      printf("\n");

      r01[i] =  (x[i] - x[i+1])  +  (y[i] - y[i+1]) ;
      R01[i] = sqrt(  ( (x[i] - x[i+1])*(x[i] - x[i+1]) )  + ( (y[i] - y[i+1])*(y[i] - y[i+1]) ) ) ;

      printf("r01%d: %f\n", i, r01[i]);
      printf("R01%d: %f\n", i, R01[i]);

      printf("\n");

}

printf("%f\n", x[0]);
printf("%f\n", y[0]);


double E0 = 10^-3;
double G = (double)100/N;

//for(int j=0; j<=)


r011[0] =  (x[0] - x[1])  +  (y[0] - y[1]) ;
R011[0] = sqrt(  ( (x[0] - x[1])*(x[0] - x[1]) )  + ( (y[0] - y[1])*(y[0] - y[1]) ) ) ;

//Norm_ro1 = r01/R01;

printf("r011: %f\n", r011[0]);
printf("R011: %f\n", R011[0]);

//printf("Norm_ro1: %f\n", Norm_ro1);



 //fclose(buf1);
  return 0;
}