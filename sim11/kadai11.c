#include<stdio.h>
#define N 4

double x[N]={0,0,0,0};

double A[N][N]={{1,2,1,5},
                {8,1,3,1},
                {1,7,1,1},
                {1,1,6,1}};
double b[N]={20.5,14.5,18.5,9.0};

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
            //printf("m = %lf\n",m);
            A[i][k]=0;
            for(j=k+1;j<N;j++){
                A[i][j] = A[i][j]-A[k][j]*m;
                //printf("A[%d][%d] = %lf\n",i,j,A[i][j]);
            }
            b[i]=b[i] -b[k]*m;
            //printf("b[%d] = %lf\n\n",i,b[i]);
        }
        //disp(A,b); 
    }  
}
void dispAns(){
    int i;
    printf("Answer\n");
    for(i=0;i<N;i++){
        printf("x[%d] = %lf\n",i+1,x[i]);
    }
}

void backwordSubstitution(void){
    int k,j;
    x[N-1]=b[N-1]/A[N-1][N-1];
    for(k=N-2;k>=0;k--){
        x[k]=b[k];
        for(j=k+1;j<=N;j++){
            x[k]-=A[k][j]*x[j];
        }
        x[k]/=A[k][k];
    }
}

void gaussElimination(void){
    disp(A,b);
    forwardElimination();
    disp(A,b);  
    backwordSubstitution();
    dispAns(); 
}

int main(void){
    gaussElimination();
    return 0;
}