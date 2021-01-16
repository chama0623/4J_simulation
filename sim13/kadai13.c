#include<stdio.h>
#include<math.h>
#define N 10
#define M 2

//#define polynomial //多項式近似
#define multiple // 重回帰分析

#ifdef polynomial
    // 課題13b
    double X[N] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6};
    double Y[N] = {0.0,0.034,0.138,0.282,0.479,0.724,1.120};
    double transX[M][N];
#else // multiple
    // 課題13bと等価な問題
    //double transX[M][N]={{0.0,0.1,0.2,0.3,0.4,0.5,0.6},{0.0,0.01,0.04,0.09,0.16,0.25,0.36}};
    //double Y[N] = {0.0,0.034,0.138,0.282,0.479,0.724,1.120};
    
    // マンションの価格データ
    double transX[M][N]={{51,38,57,51,53,77,63,69,72,73},{16,4,16,11,4,22,5,5,2,1}};
    double Y[N]={3.0,3.2,3.3,3.9,4.4,4.5,4.5,5.4,5.4,6.0};
#endif


double x[M+1];
double A[M+1][M+1];
double b[M+1];

// データを標準出力
void dispData(void){
    int i,j;
    printf("       データ       \n");
    printf("--------------------\n");
    #ifdef polynomial
        for(i=0;i<N;i++){
            printf("%lf ",X[i]);
            printf("| %lf \n",Y[i]);
        }
    #else
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            printf("%lf ",transX[j][i]);
        }
        printf("| %lf \n",Y[i]);
    }
    #endif
    printf("--------------------\n");
    printf("\n");
}
// A,bを標準出力
void disp(){
    int i,j;
    printf("      A           b \n");
    printf("--------------------\n");
    for(i=0;i<M+1;i++){
        for(j=0;j<M+1;j++){
            printf("%.2lf ",A[i][j]);
        }
        printf("| %.2lf\n",b[i]);
    }
    printf("--------------------\n\n");
}
// 結果を標準出力
void dispx(){
    int i;
    printf("y = %lf ",x[0]);
    for(i=1;i<M+1;i++){
        #ifdef polynomial
            printf("%+lf x^%d ",x[i],i);
        #else // multiple
            printf("%+lf x%d ",x[i],i);
        #endif
    }
    printf("\n");
}
// ピボット選択
int pivoting(int m){
    int i;
    int maxvalue=0;
    int maxcolumn=m;
    for(i=m+1;i<M+1;i++){
        if(maxvalue<fabs(A[m][i])){
            maxvalue=fabs(A[m][i]);
            maxcolumn=i;
        }
    }
    return maxcolumn;
}

void changeindex(int p,int q){
    int tmp,i;
    for(i=0;i<M+1;i++){
        tmp = A[p][i];
        A[p][i] = A[q][i];
        A[q][i]=tmp;
    }
    tmp = b[p];
    b[p]=b[q];
    b[q]=tmp;
}

// Gauss Elimination 
// solve Ax=b
// 前進消去
void forwardElimination(int isPivoting){
    int i,j,k;
    double m;
    int pivot;
   
   for(k=0;k<M;k++){
        for(i=k+1;i<M+1;i++){
            if(isPivoting){
                pivot = pivoting(i);
                changeindex(i,pivot);
            }
            m=A[i][k]/A[k][k];
            A[i][k]=0;
            for(j=k+1;j<M+1;j++){
                A[i][j] = A[i][j]-A[k][j]*m;
            }
            b[i]=b[i] -b[k]*m;
        }
    }  
}
// 後退代入
void backwordSubstitution(void){
    int k,j;
    x[M]=b[M]/A[M][M];
    for(k=M-1;k>=0;k--){
        x[k]=b[k];
        for(j=k+1;j<=M+1;j++){
            x[k]-=A[k][j]*x[j];
        }
        x[k]/=A[k][k];
    }
}

// 分析関数
void RMSE(int isPivoting){
    int i,j,k;
    double tmp,p,q;
    // transfit X shape
    #ifdef polynomial
        for(i=0;i<M;i++){
            for(j=0;j<N;j++){
                tmp=1;
                for(k=0;k<i+1;k++){
                    tmp*=X[j];
                }
                transX[i][j]=tmp;
            }
        }
    #endif
    
    dispData();

    // cal A,b,x
    for(k=0;k<M+1;k++){
        for(j=0;j<M+1;j++){
            A[k][j]=0;
            for(i=0;i<N;i++){
                if(j==0){
                    p=1;
                }else{
                    p=transX[j-1][i];
                }

                if(k==0){
                    q=1;
                }else{
                    q=transX[k-1][i];
                }
                A[k][j]+=p*q;
            }
        }
        b[k]=0;
        for(i=0;i<N;i++){
            if(k==0){
                q=1;
            }else{
                q=transX[k-1][i];
            }
            b[k]+=Y[i]*q;
        }
        x[k]=0;
    }

    disp();
    // solve by Gauss Elimination
    forwardElimination(isPivoting);
    backwordSubstitution();
    dispx();
}

int main(void){
    int isPivoting=0;
    RMSE(isPivoting);
    return 0;
}