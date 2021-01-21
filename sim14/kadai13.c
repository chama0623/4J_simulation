#include<stdio.h>
#include<math.h>
#define N 41
#define M 1

#define polynomial //多項式近似
//#define multiple // 重回帰分析

#ifdef polynomial
    // 課題13b
    double X[N] = {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,3300,3400,3500,3600,3700,3800,3900,4000,4100,4200,4300,4400,4500,4600,4700,4800,4900,5000};
    double Y[N] = {828.31941,890.87274,1011.04385,1000.86756,1101.36252,1162.22356,1258.216,1360.32889,1469.11585,1520.72163,1696.41881,1692.49111,1936.3683,1823.21082,1926.73496,2099.90193,2270.88889,2171.21467,2223.30652,2362.71274,2381.90859,2496.84104,2458.96267,2582.95111,2659.91659,2752.14341,2955.69111,3030.92163,3101.94815,3095.64148,3212.68356,3355.73215,3389.1877,3561.52311,3599.63496,3675.19556,3872.02533,3929.63022,3982.36711,4090.67304,4128.28311};
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