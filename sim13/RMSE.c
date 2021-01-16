#include<stdio.h>
#include<math.h>
#define N 4

double X[N] = {1,2,3,4};
double Y[N] = {0,1,2,4};


void RMSE(void){
    double meanx=0;
    double meany=0;
    double cov=0;
    double varx=0;
    double vary=0;
    double slope,intercept;
    double r;
    int i;
    // calculate mean
    for(i=0;i<N;i++){
        meanx+=X[i];
        meany+=Y[i];
    }
    meanx/=N;
    meany/=N;
    // calculate variance
    for(i=0;i<N;i++){
        varx+=(X[i]-meanx)*(X[i]-meanx);
        vary+=(Y[i]-meany)*(Y[i]-meany);
    }    
    varx/=N;
    vary/=N;
    // calculate covariance
        for(i=0;i<N;i++){
        cov+=(X[i]-meanx)*(Y[i]-meany);
    } 
    cov/=N;
    slope = cov/varx;
    intercept = meany-slope*meanx;
    r=cov/(sqrt(varx)*sqrt(vary));
    printf("説明変数の平均 %lf\n",meanx);
    printf("説明変数の分散 %lf\n",varx);
    printf("従属変数の平均 %lf\n",meany);
    printf("従属変数の分散 %lf\n",vary);
    printf("\n共分散 %lf\n",cov);
    printf("相関係数 %lf\n",r);
    printf("\n回帰方程式 y= %lf + %lf x\n",intercept,slope);
    printf("決定係数 %lf\n",r*r);
}

int main(void){
    RMSE();
    return 0;
}