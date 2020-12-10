#include<stdio.h>
#include<stdlib.h>

//#define STDOUT
#define CSVOUT

#define M 1.0
#define Q 1.0
#define B0 2.0
#define E 2.0
#define X0 0.1
#define Y0 0.0
#define V0X 0.0
#define V0Y 0.1
#define Z0 0.0
#define V0Z 0.0

#define H 0.01
#define MAX_STEP 1000

double velocity(double v){
    return Q/M*B0*v;
}

double velocityz(){
    return Q/M*E;
}

double displacemant(double v){
    return v;
}

void Heun(){
    double t = 0;
    double tp;
    double Xp,Yp,Vxp,Vyp,Zp,Vzp,k1,k2,l1,l2;
    double x=X0;
    double vx=V0X;
    double y=Y0;
    double vy=V0Y;
    double z=Z0;
    double vz=V0Z;
    for(int i=0;i<MAX_STEP;i++){
        tp = t+H;
        k1 = H*displacemant(vx);
        l1 = H*velocity(vy);

        k2 = H*displacemant(vx+k1);
        l2 = H*velocity(vy+l1);

        Xp = x+(k1+k2)/2;
        Vxp = vx+(l1+l2)/2;

        k1 = H*displacemant(vy);
        l1 = -H*velocity(vx);

        k2 = H*displacemant(vy+k1);
        l2 = -H*velocity(vx+l1);

        Yp = y+(k1+k2)/2;
        Vyp = vy+(l1+l2)/2;

        k1 = H*displacemant(vz);
        l1 = H*velocityz();

        k2 = H*displacemant(vz+k1);
        l2 = H*velocityz();

        Zp = z+(k1+k2)/2;
        Vzp = vz+(l1+l2)/2;

        #ifdef STDOUT
            printf("t=%lf  X =%0.10lf,Y =%0.10lf  Vx =%0.10lf,Vy =%0.10lf\n",tp,Xp,Yp,Vxp,Vyp);
        #else
            printf("%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",tp,Xp,Yp,Zp,Vxp,Vyp,Vzp);
        #endif
        t=tp;
        x=Xp;
        y=Yp;
        z=Zp;
        vx=Vxp;
        vy=Vyp;
        vz=Vzp;
    }
}

int main(int argc,char *argv[]){
    #ifdef STDOUT
        printf("t=%3d  X =%0.10lf,Y =%0.10lf  Vx =%0.10lf,Vy =%0.10lf\n",0.0,X0,Y0,V0X,V0Y);
    #else
        printf("%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",0.0,X0,Y0,Z0,V0X,V0Y,V0Z);
    #endif    
    Heun();
    
    return 0;
}