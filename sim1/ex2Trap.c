#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.141592

double func(double x){
    return 4/(1+x*x);
} 

double Trapezoidal(double a,double b){
    return (b-a)*(func(a)+func(b))/2;
}

// integral of f(x) from a to b (split n)
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

int main(int argc,char *argv[]){
    printf("n =  1  result = %lf  error = %lf\n",TrapezoidalRule(0,1,1),fabs(TrapezoidalRule(0,1,1)-PI));
    printf("n =  2  result = %lf  error = %lf\n",TrapezoidalRule(0,1,2),fabs(TrapezoidalRule(0,1,2)-PI));
    printf("n =  8  result = %lf  error = %lf\n",TrapezoidalRule(0,1,8),fabs(TrapezoidalRule(0,1,8)-PI));
    printf("n = 16  result = %lf  error = %lf\n",TrapezoidalRule(0,1,16),fabs(TrapezoidalRule(0,1,16)-PI));
    printf("n = 32  result = %lf  error = %lf\n",TrapezoidalRule(0,1,32),fabs(TrapezoidalRule(0,1,32)-PI));
    return 0;
}