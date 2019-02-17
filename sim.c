#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "sim.h"


/*  Function diffination */

int read_doubles_from_file(int n, double* p, const char* fileName) {
  /* Open input file and determine its size. */
  FILE* input_file = fopen(fileName, "rb");
  if(!input_file) {
    printf("read_doubles_from_file error: failed to open input file '%s'.\n", fileName);
    return -1;
  
  }

  /* Get filesize using fseek() and ftell(). */
  fseek(input_file, 0L, SEEK_END);
  size_t fileSize = ftell(input_file);
  /* Now use fseek() again to set file position back to beginning of the file. */
  fseek(input_file, 0L, SEEK_SET);
  if(fileSize != n * sizeof(double)) {
    printf("read_doubles_from_file error: size of input file '%s' does not match the given n.\n", fileName);
    printf("For n = %d the file size is expected to be (n * sizeof(double)) = %lu but the actual file size is %lu.\n",
   n, n * sizeof(double), fileSize);
    return -1;
  }
  /* Read contents of input_file into buffer. */
  size_t noOfItemsRead = fread(p, sizeof(char), fileSize, input_file);
  if(noOfItemsRead != fileSize) {
    printf("read_doubles_from_file error: failed to read file contents into buffer.\n");
    return -1;
  }
  /* OK, now we have the file contents in the buffer.
     Since we are finished with the input file, we can close it now. */
  if(fclose(input_file) != 0) {
    printf("read_doubles_from_file error: error closing input file.\n");
    return -1;
  }
  /* Return 0 to indicate success. */

  return 0;
}


/*  Function diffination */

void calcul(int N, double *buf, double nsteps, int delta_t) {

	double temp[6*N], p1_B, r, p;
	double p1_X, p1_Y, p1_m, p1_valX, p1_valY;
	double p2_X, p2_Y, p2_m, p2_valX, p2_valY;
	double comp_X=0, comp_Y=0;
	double acc_X, acc_Y;
	double e = 1e-3;
	double G = (double)100.0/N;

	for (int t = 0; t < nsteps; t++) {
		for (int i= 0; i < N; i++) {
			p1_X = buf[i*6 + 0];
      p1_Y = buf[i*6 + 1];
      p1_m = buf[i*6 + 2];
      p1_valX = buf[i*6 + 3];
      p1_valY = buf[i*6 + 4];
      p1_B = buf[i*6 +5];

      for (int j = 0; j < N; j++) {

        if (i != j) {
          p2_Y = buf[j*6 + 0];
          p2_Y = buf[j*6 + 1];
          p2_m = buf[j*6 + 2];
          r = sqrt(  ( (p1_X - p2_X)*(p1_X - p2_X) )  + ( (p1_Y - p2_Y)*(p1_Y - p2_Y) ) );
          p = p2_m/(r+e)*(r+e)*(r+e);
          comp_X += p * (p1_X - p2_X);
          comp_Y += p * (p1_Y - p2_Y);

        } // end of if 

      } // end of for loop j

      acc_X = -G * comp_X;
      acc_Y = -G * comp_Y;
      
      p1_valX += delta_t * acc_X;
      p1_valY += delta_t * acc_Y;

      p1_X += delta_t * p1_valX;
      p1_Y += delta_t * p1_valY;

      temp[i*6 + 0] = p1_X;
      temp[i*6 + 1] = p1_Y;
      temp[i*6 + 2] = p1_m;
      temp[i*6 + 4] = p1_valX;
      temp[i*6 + 5] = p1_valY;
      temp[i*6 + 3] = p1_B;

      } // end of for loop t

      for(int k = 0; k < (6*N); k++){
        buf[k] = temp[k];
      } // end k for loop


	} // end of for loop i
   


}