#include<stdio.h>
#include<stdlib.h>

//#define STDOUT
#define CSVOUT

#define QBM 2.0
#define X0 0.0
#define V0 1.0

#define H 0.01
#define MAX_STEP 100

double displacemant(double v){
    return QBM*v;
}

double velocity(double v){
    return v;
}

void Heun(){
    double t = 0;
    double tp;
    double Xp,Vp,k1,k2,l1,l2;
    double x=X0;
    double v=V0;
    for(int i=0;i<MAX_STEP;i++){
        tp = t+H;
        k1 = H*displacemant(v);
        l1 = H*velocity(v);
        k2 = H*displacemant(x+k1);
        l2 = H*velocity(v+l1);
        Xp = x+(k1+k2)/2;

        #ifdef STDOUT
            printf("t=%d  X=%0.10lf,V=%0.10lf\n",i+1,Xp,Vp);
        #else
            printf("%d,%lf,%lf\n",i+1,Xp,v);
        #endif
        t=tp;
        x=Xp;
    }
}

int main(int argc,char *argv[]){
    #ifdef STDOUT
        printf("t=%3d  X=%0.10lf,V=%0.10lf\n",0,X0,V0);
    #else
        printf("%d,%lf,%lf\n",0,X0,V0);
    #endif    
    Heun();
    
    return 0;
}