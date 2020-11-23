#include<stdio.h>
#include<stdlib.h>
#define DIM 2

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
    double h = 0.01;
    double lim=100.0;
    double R=0;
    double C=0.3;
    double L = 10;
    double Q0 = 10;
    double step;
    int i;
    double initVector[DIM][1] ={{0},{10}}; // 初期条件 y,v 
    double transVector[DIM+1][1];
    double weightMatrix[DIM][DIM+1] = {{0,-R/L,-1/(C*L)},
                                        {0,1,0}
                                       };
    double yiVector[DIM][1];
    double fiVector[DIM][1];
    double fiastaVector[DIM][1];
    double tmpVector[DIM][1];
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

    setVector(initVector,yiVector);
    for(step=h;step<=lim;step+=h){
        transformVector(yiVector,transVector);
        multipleMatrix(weightMatrix,transVector,fiVector);
        transformVector(fiVector,transVector);
        transVector[1][0]+=h;
        multipleMatrix(weightMatrix,transVector,fiastaVector);
        addVector(fiVector,fiastaVector,tmpVector);
        scalerVector(tmpVector,h/2);
        addVector(tmpVector,yiVector,resultVector);
        //結果を表示
        #ifdef STROUT
        printf("step = %0.2lf\n",step);
        printf("I%d = %lf\n",i,resultVector[0][0]);
        printf("Q%d = %lf\n",i,resultVector[1][0]);
        printf("\n");
        #else
        printf("%lf,%lf,%lf\n",step,resultVector[0][0],resultVector[1][0]);
        #endif
        setVector(resultVector,yiVector);
    }
    return 0;
}