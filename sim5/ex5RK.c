#include<stdio.h>
#include<stdlib.h>
#define MAX_STEP 1

double func(double x,double y){
    return 2*y/(1+x);
}

double RK(double x0,double y0,double h){
    double x=x0,y=y0;
    double xp,yp,k1,k2,k3,k4;
    for(int i=0;i<MAX_STEP;i++){
        xp = x+h;
        k1 = h*func(x,y);
        k2 = h*func(x+h/2,y+k1/2);
        k3 = h*func(x+h/2,y+k2/2);
        k4 = h*func(x+h,y+k3);
        yp = y+(k1+2*k2+2*k3+k4)/6;
        printf("t=%d   x=%lf,y=%lf\n",i+1,xp,yp);
        printf("k1=%lf\n",k1);
        printf("k2=%lf\n",k2);
        printf("k3=%lf\n",k3);
        printf("k4=%lf\n",k4);
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
    RK(x0,y0,h);
    
    return 0;
}