/**************************
 * matrix.h
 *
 * Definitions of Operations of matrix.
 *
 * Author: Mao Jiewen
 * Date: 2015-3-18
 *
 ***************************/

#include "../common/nrutil.h"
#include <math.h>

/**
 * Cholesky Factorization
 *
 * Arguments:
 *      float** a - the matrix to be factorized.
 *      int n     - the size of the matrix.
 *      float* p  - the main diagonal line of the matrix.
 */
void choldc(float **a, int n, float p[]);
