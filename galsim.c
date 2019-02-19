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
double delta_t = atoi(argv[4]);
int graphics = atoi(argv[5]);

printf("Number of particles: %d\n",N);
printf("input_file_name = %s\n", in_file);
printf("Number of timesteps: %d\n",nsteps);
printf("timestep: %f\n",delta_t);
printf("Graphics: %d\n", graphics);

if (graphics == 1) {
  printf(" Graphics not implemented\n");
}

printf("\n");

/* Open input file and determine its size. */
  double buf1[6*N];
  if(read_doubles_from_file(6*N, buf1, in_file) != 0){

    printf("Error reading file '%s'\n", in_file);
    return -1;
  }

    double time1 = get_wall_seconds();
    calcul(N, buf1, nsteps, delta_t);
    double time2 = get_wall_seconds();
    
    printf("secondsTaken: %f\n",time2-time1);

    /* Output file*/

    FILE * output_file = fopen("result.gal", "wb");
    if(!output_file) {

      printf("File error: failed to open Output file.\n");
      return -1;
    }

    fwrite(buf1, sizeof(char), 6 * N * sizeof(double), output_file);

    fclose(output_file);

  return 0;
}