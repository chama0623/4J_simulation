#include<stdio.h>
#include<stdlib.h>

//define STDOUT
#define CSVOUT

#define R 11
#define L 10.0
#define C 0.3
#define Q0 10.0
#define I0 0.0

#define H 0.001
#define MAX_STEP 32648 //326483

double fI(double Q,double I){
    return -(R/L)*I-Q/(C*L);
}

double fQ(double I){
    return I;
}

void Heun(){
    double t = 0;
    double tp;
    double Qp,Ip,k1,k2;
    double Q=Q0;
    double I=I0;
    for(int i=0;i<MAX_STEP;i++){
        tp = t+H;
        k1 = H*fI(Q,I);
        k2 = H*fI(Q+H,I+k1);
        Ip = I+(k1+k2)/2;

        k1 = H*fQ(I);
        k2 = H*fQ(I+k1);
        Qp = Q+(k1+k2)/2;
        #ifdef STDOUT
            printf("t=%lf  Q=%0.10lf,I=%0.10lf\n",tp,Qp,Ip);
        #else
            printf("%lf,%lf,%lf\n",tp,Qp,Ip);
        #endif
        t=tp;
        I=Ip;
        Q=Qp;
    }
}

int main(int argc,char *argv[]){
    #ifdef STDOUT
        printf("t=%3d  Q=%0.10lf,I=%0.10lf\n",0,Q0,I0);
    #else
        printf("%d,%lf,%lf\n",0,Q0,I0);
    #endif    
    Heun();
    
    return 0;
}