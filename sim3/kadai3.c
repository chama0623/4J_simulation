#include<stdio.h>
#include<stdlib.h>
#define MAX_STEP 10

double func(double x,double y){
    return y;
}

void Euler(double x0,double y0,double h){
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

int main(int argc,char *argv[]){
    double x0 = 0;
    double y0 = 1;
    double h = 0.1;
    /* format for stdout 
    printf("-----setting-----\n");
    printf("h=%lf\nt=0   x=%lf,y=%lf\n",h,x0,y0);
    Euler(x0,y0,h);
    */

    /* format for csv */
    printf("0,%lf,%lf\n",x0,y0);
    EulerCsv(x0,y0,h);

    return 0;
}