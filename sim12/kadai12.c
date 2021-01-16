#include<stdio.h>
#include<math.h>
#define N 3

double x[N]={0,0,0};

double A[N][N]={{2,4,2},
                {1,2,3},
                {4,6,2}};
double b[N]={6,9,8};

void disp(){
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

int pivoting(int m){
    int i;
    int maxvalue=0;
    int maxcolumn=m;
    for(i=m+1;i<N;i++){
        if(maxvalue<fabs(A[m][i])){
            maxvalue=fabs(A[m][i]);
            maxcolumn=i;
        }
    }
    return maxcolumn;
}

void changeindex(int p,int q){
    int tmp,i;
    for(i=0;i<N;i++){
        tmp = A[p][i];
        A[p][i] = A[q][i];
        A[q][i]=tmp;
    }
    tmp = b[p];
    b[p]=b[q];
    b[q]=tmp;
}

void forwardElimination(int isPivoting){
    int i,j,k;
    double m;
    int pivot;
   
   for(k=0;k<N-1;k++){
        for(i=k+1;i<N;i++){
            if(isPivoting){
                pivot = pivoting(i);
                changeindex(i,pivot);
            }
            m=A[i][k]/A[k][k];
            A[i][k]=0;
            for(j=k+1;j<N;j++){
                A[i][j] = A[i][j]-A[k][j]*m;
            }
            b[i]=b[i] -b[k]*m;
        }
    }  
}
void dispAns(){
    int i;
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

int main(void){
    int isPivoting=0;
    // 入力行列の表示
    printf("\nisPivoting = %d\n",isPivoting);
    printf("Init Array A and Vector b\n");
    disp();
    // 前進消去
    forwardElimination(isPivoting);
    // 前進消去の結果を表示
    printf("\nResult of forward elimination\n");
    disp();  
    // 後退代入
    backwordSubstitution();
    // 結果を表示
    printf("\nAnswer\n");
    dispAns(); 
    printf("\n");
    return 0;
}