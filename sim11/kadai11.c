#include<stdio.h>
#define N 3

double A[N][N]={{2,2,6},
                {4,5,13},
                {5,8,24}};
double b[N]={24,52,93};


/*
double A[N][N] = {{1,-2,3},
                  {2,-1,1},
                  {1,3,-5}};
double b[N]={5,6,2};
*/

void disp(double A[N][N],double b[N]){
    int i,j;
    printf("--------------------\n");
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%.2lf ",A[i][j]);
        }
        printf("| %.2lf\n",b[i]);
    }
    printf("--------------------\n");
}

void forwardElimination(){
    int i,j,k;
    double m;
   
   for(k=0;k<N-1;k++){
        for(i=k+1;i<N;i++){
            m=A[i][k]/A[k][k];
            printf("m = %lf\n",m);
            A[i][k]=0;
            for(j=k+1;j<N;j++){
                A[i][j] = A[i][j]-A[k][j]*m;
                printf("A[%d][%d] = %lf\n",i,j,A[i][j]);
            }
            b[i]=b[i] -b[k]*m;
            printf("b[%d] = %lf\n\n",i,b[i]);
        }
        disp(A,b); 
    }  
}

int main(void){
    disp(A,b);
    forwardElimination();
    disp(A,b);  
    return 0;
}