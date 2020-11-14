#include<stdio.h>
#include<stdlib.h>
#define DIM 3
//#define STDOUT
#define CSVOUT

void multipleMatrix(double a[DIM][DIM+1],double b[DIM+1][1],double c[DIM][1]){
    int i,j,k;
    double tmp;
    tmp=0;
      for(i=0; i<DIM+1; i++){
        for(j=0; j<DIM; j++){
            c[i][j]=0;
            for(k=0; k<DIM+1; k++){
	            c[i][j]+=a[i][k]*b[k][j];
      }
    }
  }
}

void addVector(double a[DIM][1],double b[DIM][1],double c[DIM][1]){
    int i;
    for(i=0; i<DIM;i++){
        c[i][0] = a[i][0]+b[i][0];
    }
}

void scalerVector(double a[DIM][1],double h){
    int i;
    for(i=0; i<DIM;i++){
        a[i][0] *=h;
    }
}

void transformVector(double a[DIM][1],double b[DIM+1][1]){
    int i;
    b[0][0]=1;
    for(i=1; i<DIM+1;i++){
        b[i][0] = a[i-1][0];
    }
}

void setVector(double a[DIM][1],double b[DIM][1]){
    int i;
    for(i=0;i<DIM;i++){
        b[i][0] = a[i][0];
    }
}

int main(void){
    double h = 0.1;
    double lim=1.01;
    double a=0.7;
    double b=0.4;
    double c=0.09;
    double d=0.06;
    double y10=10;
    double y20=10;
    double step;
    int i;

    // 初期値を宣言するベクトルの配列
    double initVector[DIM][1] ={{y10},{y20},{y10*y20}};
    // ベクトル変換用配列
    double transVector[DIM+1][1];
    // 連立微分方程式のパラメータの配列
    double weightMatrix[DIM][DIM+1] = {{0,a,0,-c},
                                       {0,0,-b,d},
                                       {0,0,0,0}
                                       };
    // 計算用配列
    double yiVector[DIM][1];
    double tmpVector[DIM][1];
    //結果表示用配列
    double resultVector[DIM][1];

    // 初期値表示
    #ifdef STDOUT
    printf("step = %0.2lf\n",0.1);
    #else
    printf("%lf,%lf,%lf",0.0,initVector[0][0],initVector[1][0]);
    #endif

        for(i=0;i<DIM;i++){
            #ifdef STDOUT
            printf("y%d = %lf\n",i,initVector[i][0]);
            #endif
        }
        printf("\n");

    // 初期値を計算用配列にセット
    setVector(initVector,yiVector);

    for(step=h;step<=lim;step+=h){
        //ベクトル変換
        transformVector(yiVector,transVector);
        // 微分係数を計算
        multipleMatrix(weightMatrix,transVector,tmpVector);
        scalerVector(tmpVector,h);
        // 1次ラグとの和を計算
        addVector(yiVector,tmpVector,resultVector);

        //結果を表示
        #ifdef STROUT
        printf("step = %0.2lf\n",step);
        for(i=0;i<DIM;i++){
            printf("y%d = %lf\n",i,resultVector[i][0]);
        }
        printf("\n");
        #else
        printf("%lf,%lf,%lf\n",step,resultVector[0][0],resultVector[1][0]);
        #endif

        // y1*y2調整処理
        resultVector[2][0] = resultVector[0][0]*resultVector[1][0];
        // 結果を計算用配列にセット
        setVector(resultVector,yiVector);
    }
    return 0;
}