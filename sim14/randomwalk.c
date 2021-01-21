#include<stdio.h>
#include <stdlib.h>
#include <time.h>

//#define ALLSTEP
#define TRIAL 30
//#define N 1000

int randomWalk(int n,double p,int L){
    int S=0;
    double E,V,rnd;
    int i;
    #ifdef ALLSTEP
        //printf("%d,%d\n",0,S);
    #endif
    for(i=0;i<n;i++){
        rnd = 1 + (rand()%100);
        rnd/=100;
        if(rnd<=p){
            S+=L;
        }else{
            S-=L;
        }
        #ifdef ALLSTEP
            //printf("%d,%d\n",i+1,S);
        #endif
    }
    return S;
}

int main(void){
    int i,j,r;
    double p=0.5;
    int L=1;
    double S1,S2,V,Vmean;
    srand((unsigned) time(NULL));
    Vmean=0;
    for(i=0;i<TRIAL;i++){
        S1=0;
        S2=0;
        #ifdef ALLSTEP
        printf("\n%d回目の試行\nr(%d) = ",i+1,N);
        #endif
        for(j=0;j<TRIAL;j++){
            r=randomWalk(N,p,L);
            #ifdef ALLSTEP
            printf("%d, ",r);
            #endif
            S1+=r;
            S2+=r*r;
        }
        #ifdef ALLSTEP
        printf("\n");
        #endif

        V=(S2/TRIAL) - (S1/TRIAL)*(S1/TRIAL);
        Vmean+=V;
        #ifdef ALLSTEP
        printf("V = %lf\n",V);
        printf("----------\n");
        #endif  
    }
    Vmean/=(TRIAL);
    //printf("Vmean = %lf\n",Vmean);  
    printf("%d,%lf\n",N,Vmean);  
    return 0;
}