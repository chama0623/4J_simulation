#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// 試行回数n
// 移動距離 L
void randomWalk2(int n,int L){
    double X=0;
    double Y=0;
    double rnd;
    int i;
    printf("%d,%lf,%lf\n",0,0.0,0.0);
    for(i=0;i<n;i++){
        // make random[0,1]
        rnd = (double)rand()/RAND_MAX;
        // make random[0,2pi]
        rnd*=2*M_PI;
        X+=L*cos(rnd);
        Y+=L*sin(rnd);
        printf("%d,%lf,%lf\n",i+1,X,Y);
    }
}

int main(void){
    srand((unsigned) time(NULL));
    randomWalk2(5000,1);
    return 0;
}