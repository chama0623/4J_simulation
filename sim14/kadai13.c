#include<stdio.h>
#include<math.h>
#define N 91
#define M 1

#define polynomial //多項式近似
//#define multiple // 重回帰分析

#ifdef polynomial
    // 課題13b
    double X[N] = {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,3300,3400,3500,3600,3700,3800,3900,4000,4100,4200,4300,4400,4500,4600,4700,4800,4900,5000,5100,5200,5300,5400,5500,5600,5700,5800,5900,6000,6100,6200,6300,6400,6500,6600,6700,6800,6800,7000,7100,7200,7300,7400,7500,7600,7700,7800,7900,8000,8100,8200,8300,8400,8500,8600,8700,8800,8900,9000,9100,9200,9300,9400,9500,9600,9700,9800,9900,10000};
    double Y[N] = {914.9957,1049.7443,1116.308,1180.79615,1248.07541,1331.61541,1450.45541,1529.68207,1610.57837,1752.41067,1796.84682,2026.24963,2280.21778,2379.91511,2465.94341,2612.40133,2727.64148,2650.08904,2806.26948,2756.62681,2745.22741,2987.19837,3227.63393,3075.72326,3237.90059,3371.21511,3553.568,3780.35304,3766.27881,3861.19882,3867.24918,4137.59156,3949.55763,4173.2477,4044.82504,4099.64341,4460.56963,4394.74563,4544.56667,4448.65274,4863.95096,5083.8397,4812.94207,5372.06785,5756.10074,5714.69615,6022.01644,5761.68459,6123.36148,5600.84933,5451.55644,5927.76933,5859.60163,6062.54459,5746.26133,6144.62918,6150.76267,6362.296,6324.30252,6325.21363,6880.02859,6876.19822,6745.99052,6743.7397,7524.78207,7702.38904,7974.79363,7671.28948,7750.5643,7081.45852,7302.47407,7764.33896,7492.42044,7715.38267,8331.78593,8336.66237,8596.22296,8845.44326,8296.27585,9065.50711,8833.28178,8695.81748,9341.11111,9615.15985,9645.05244,10241.72089,9678.62059,10103.584,10288.16044,9886.87615,9290.05644};
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