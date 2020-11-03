#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.141592

double func(double x){
    return sin(x);
} 

// cal simple Trapezoidal
double Trapezoidal(double a,double b){
    return (b-a)*(func(a)+func(b))/2;
}

// integral of f(x) from a to b (split n)
// method : Trapezoidal Rule
double TrapezoidalRule(double a,double b,int n){
    if(n<=0){
        printf("Incorrect value of n");
        exit(0);
    }

    double sum=0;
    for(double i=0;i<n;i++){
        sum+=Trapezoidal(a+i*(b/n),a+(i+1)*(b/n));
    }
    return sum;
}

// cal simple Simpson
double Simpson(double a,double b){
    double h = (b-a)/2;
    double c = (a+b)/2;
    return h*(func(a)+4*func(c)+func(b))/3;
}

// integral of f(x) from a to b (split n)
// method : Simposon Rule
double SimpsonRule(double a,double b,int n){
    if(n<=0){
        printf("Incorrect value of n");
        exit(0);
    }
    double sum=0;
    for(double i=0;i<n;i++){
        sum+=Simpson(a+i*(b/n),a+(i+1)*(b/n));
    }
    return sum;
}

int main(int argc,char *argv[]){
    int n_max = 65536;
    printf("\n");
    for(int i=1; i<=n_max; i*=2){
        double result = SimpsonRule(0,M_PI/2,i);
        printf(" split = %5d   result = %1.16lf   error = %1.16lf\n",i,result,fabs((double)1-result));
    }
    printf("\n");
    return 0;
}