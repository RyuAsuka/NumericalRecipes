/**************************
 * main.c
 *
 * Testing program of my functions
 *
 * Author: Mao Jiewen
 * Date: 2015-3-19
 *
 ***************************/
#include "../NumericalRecipes/matrix.h"
#include <stdio.h>

void input_matrix(float **m, int nrl, int nrh, int ncl, int nch);
void output_matrix(float **m, int nrl, int nrh, int ncl, int nch);
void output_vector(float *p, int n);
float** make_ans(float **m, int nrl, int nrh, int ncl, int nch, float* p);

int main(void)
{
    int n;
    float **m, **ans;
    float *p;

    printf("Please input matrix's size: ");
    scanf("%d",&n);
    m = matrix(1,n,1,n);
    p = vector(1,n);

    printf("\nPlease input matrix's elements:\n");
    input_matrix(m,1,n,1,n);

    choldc(m, n, p);
    ans = make_ans(m,1,n,1,n,p);

    printf("\nCholesky factorization answer is: \n");
    output_matrix(ans,1,n,1,n);
    return 0;
}

float** make_ans(float **m, int nrl, int nrh, int ncl, int nch, float *p)
{
    float** ans = matrix(nrl,nrh,ncl,nch);
    int i, j;

    for(i = nrl; i <= nrh; i++)
    {
        for(j = ncl; j <= nch; j++)
        {
            if(i < j) ans[i][j] = 0;
            else if(i > j) ans[i][j] = m[i][j];
            else ans[i][j] = p[i];
        }
    }

    return ans;
}

void input_matrix(float **m, int nrl, int nrh, int ncl, int nch)
{
    int i, j;
    for(i = nrl; i <= nrh; i++)
        for(j = ncl; j <= nch; j++)
    {
        scanf("%f", &m[i][j]);
    }
}

void output_matrix(float **m, int nrl, int nrh, int ncl, int nch)
{
    int i, j;
    for(i = nrl; i <= nrh; i++)
    {

        for(j = ncl; j <= nch; j++)
        {
            printf("%.2f", m[i][j]);
            if(j < nch) putchar(' ');
            else putchar('\n');
        }
    }
    printf("\n");
}

void output_vector(float *p, int n)
{
    int i;
    for(i = 1; i <= n; i++)
    {
        printf("%.2f", p[i]);
        if(i < n-1) putchar(' ');
        else putchar('\n');
    }
}
