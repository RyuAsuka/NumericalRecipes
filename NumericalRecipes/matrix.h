#include "../common/nrutil.h"
#include <math.h>
#define TINY 1.0e-20

void choldc(float **a, int n, float p[]);
void ludcmp(float **a, int n, int* indx, float* d);
void lubksb(float **a, int n, int* indx, float b[]);
float** inverse(float **a, int n, int* indx, float* d);
float det(float** a, int n, int* indx, float* d);
