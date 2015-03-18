#include "matrix.h"

/**
  Cholesky Factorization
**/
void choldc(float **a, int n, float p[])
{
    int i,j,k;
    float sum;

    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
        {
            for(sum=a[i][j], k = i-1; k >= 1; k--) sum -= a[i][k]*a[j][k];
            if(i == j)
            {
                if(sum <= 0.0)
                    nrerror("choldc failed.");
                p[i] = sqrt(sum);
            }
            else
                a[j][i] = sum/p[i];
        }
    }
}
