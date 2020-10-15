#include<stdio.h>
#include<stdlib.h>
#define MAX_STEP 2

double func(double x,double y){
    return 2*y/(1+x);
}

double Euler(double x0,double y0,double h){
    double x=x0,y=y0;
    double xp,yp;
    for(int i=0;i<MAX_STEP;i++){
        xp = x+h;
        yp = y+h*func(x,y);
        printf("t=%d   x=%lf,y=%lf\n",i+1,xp,yp);
        x=xp;
        y=yp;
    }
}

int main(int argc,char *argv[]){
    double x0 = 0;
    double y0 = 0.5;
    double h = 0.5;
    printf("-----setting-----\n");
    printf("h=%lf\nt=0   x=%lf,y=%lf\n",h,x0,y0);
    Euler(x0,y0,h);
    return 0;
}