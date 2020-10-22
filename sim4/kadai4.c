#include<stdio.h>
#include<stdlib.h>
#define MAX_STEP 10

double func(double x,double y){
    return y;
}

double Euler(double x0,double y0,double h){
    double x=x0,y=y0;
    double xp,yp;
    for(int i=0;i<MAX_STEP;i++){
        xp = x+h;
        yp = y+h*func(x,y);
        printf("t=%02d   x=%lf,y=%lf\n",i+1,xp,yp);
        x=xp;
        y=yp;
    }
}

double EulerCsv(double x0,double y0,double h){
    double x=x0,y=y0;
    double xp,yp;
    for(int i=0;i<MAX_STEP;i++){
        xp = x+h;
        yp = y+h*func(x,y);
        printf("%d,%lf,%lf\n",i+1,xp,yp);
        x=xp;
        y=yp;
    }
}

double Heun(double x0,double y0,double h){
    double x=x0,y=y0;
    double xp,yp,k1,k2;
    for(int i=0;i<MAX_STEP;i++){
        xp = x+h;
        k1 = h*func(x,y);
        k2 = h*func(x+h,y+k1);
        yp = y+(k1+k2)/2;
        printf("t=%02d   x=%lf,y=%lf\n",i+1,xp,yp);
        x=xp;
        y=yp;
    }
}

double HeunCsv(double x0,double y0,double h){
    double x=x0,y=y0;
    double xp,yp,k1,k2;
    for(int i=0;i<MAX_STEP;i++){
        xp = x+h;
        k1 = h*func(x,y);
        k2 = h*func(x+h,y+k1);
        yp = y+(k1+k2)/2;
        printf("%d,%lf,%lf\n",i+1,xp,yp);
        x=xp;
        y=yp;
    }
}

int main(int argc,char *argv[]){
    double x0 = 0;
    double y0 = 1;
    double h = 0.1;
    /*
    printf("-----setting-----\n");
    printf("h=%lf\nt=00   x=%lf,y=%lf\n",h,x0,y0);
    printf("\n-----Euler method-----\n");
    Euler(x0,y0,h);
    printf("\n-----Heun method-----\n");
    Heun(x0,y0,h);
    */

    /* format for csv */
    printf("\n-----Euler method-----\n");
    printf("0,%lf,%lf\n",x0,y0);
    EulerCsv(x0,y0,h);

    printf("\n-----Heun method-----\n");
    printf("0,%lf,%lf\n",x0,y0);
    HeunCsv(x0,y0,h);
    
    return 0;
}