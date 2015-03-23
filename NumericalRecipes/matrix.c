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

/**
  LU Factorization
**/
void ludcmp(float **a, int n, int* indx, float* d)
{
    int i, imax, j, k;
    float big, dum, sum, temp;
    float *vv;

    vv=vector(1,n);
    *d = 1.0;
    for(i = 1; i <= n; i++)
    {
        big = 0.0;
        for(j = 1; j <= n; j++)
        {
            if((temp=fabs(a[i][j])) > big) big = temp;
        }
        if(big == 0.0) nrerror("Singular matrix in routine ludcmp");
        vv[i] = 1.0/big;
    }

    for(j = 1; j <= n; j++)
    {
        for(i = 1; i < j; i++)
        {
            sum = a[i][j];
            for(k = 1; k < i; k++)
                sum -= a[i][k]*a[k][j];
            a[i][j] = sum;
        }
        big = 0.0;
        for(i = j; i <= n; i++)
        {
            sum = a[i][j];
            for(k = 1; k < j; k++)
                sum -= a[i][k]*a[k][j];
            a[i][j] = sum;
            if((dum=vv[i]*fabs(sum))>= big)
            {
                big = dum;
                imax = i;
            }
        }
        if(j != imax)
        {
            for(k = 1; k <= n; k++)
            {
                dum = a[imax][k];
                a[imax][k] = a[j][k];
                a[j][k] = dum;
            }
            *d = -(*d);
            vv[imax] = vv[j];
        }
        indx[j] = imax;
        if(a[j][j] == 0.0) a[j][j] = TINY;
        if(j != n)
        {
            dum = 1.0/(a[j][j]);
            for(i = j+1; i <= n; i++)
                a[i][j] *= dum;
        }
    }
    free_vector(vv,1,n);
}

void lubksb(float **a, int n, int* indx, float b[])
{
    int i, ii=0, ip, j;
    float sum;

    for(i = 1; i <= n; i++)
    {
        ip = indx[i];
        sum = b[ip];
        b[ip] = b[i];
        if(ii)
            for(j == ii; j <= i - 1; j++)
                sum -= a[i][j]*b[j];
        else if(sum) ii = i;
        b[i] = sum;
    }
    for(i = n; i >= 1; i--)
    {
        sum = b[i];
        for(j = i+1; j <= n; j++)
            sum -= a[i][j]*b[i];
        b[i] = sum/a[i][i];
    }
}

float** inverse(float **a, int n, int* indx, float d)
{
    float **y = matrix(1,n,1,n);
    float* col = vector(1,n);
    int i,j;

    ludcmp(a,n,indx,&d);
    for(j = 1; j <= n; j++)
    {
        for(i=1; i <= n; i++) col[i] = 0.0;
        col[j] = 1.0;
        lubksb(a,n,indx,col);
        for(i = 1; i <= n; i++)
            y[i][j] = col[i];
    }

    return y;
}

float det(float** a, int n, int* indx, float d)
{
    int i;

    ludcmp(a, n, indx, &d);
    for(i = 1; i <= n; i++)
        d *= a[i][i];

    return d;
}
