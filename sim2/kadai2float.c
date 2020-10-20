#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.141592

float func(float x){
    return sin(x);
} 

// cal simple Trapezoidal
float Trapezoidal(float a,float b){
    return (b-a)*(func(a)+func(b))/2;
}

// integral of f(x) from a to b (split n)
// method : Trapezoidal Rule
float TrapezoidalRule(float a,float b,int n){
    if(n<=0){
        printf("Incorrect value of n");
        exit(0);
    }

    float sum=0;
    for(float i=0;i<n;i++){
        sum+=Trapezoidal(a+i*(b/n),a+(i+1)*(b/n));
    }
    return sum;
}

// cal simple Simpson
float Simpson(float a,float b){
    float h = (b-a)/2;
    float c = (a+b)/2;
    return h*(func(a)+4*func(c)+func(b))/3;
}

// integral of f(x) from a to b (split n)
// method : Simposon Rule
float SimpsonRule(float a,float b,int n){
    if(n<=0){
        printf("Incorrect value of n");
        exit(0);
    }
    float sum=0;
    for(float i=0;i<n;i++){
        sum+=Simpson(a+i*(b/n),a+(i+1)*(b/n));
    }
    return sum;
}

int main(int argc,char *argv[]){
    for(int i=1; i<=1024; i*=2){
        float result = SimpsonRule(0,M_PI/2,i);
        printf("split =%4d   result = %1.14f   error = %1.14f\n",i,result,fabs(1-result));
    }
    return 0;
}