#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double func(double x){
    return 1/cos(x);
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
    int n_max = 1024;
    double ans = logf(3)/2;

    double result;
    for(int i=1;i<=n_max;i*=2){
        result = TrapezoidalRule(0,M_PI/6,i);
        printf("n =  %4d  result = %lf  error = %lf\n",i,result,fabs(result-ans));
        // output format for csv
        //printf("%d,%lf,%0.15lf\n",i,result,fabs(result-ans));
    }
    return 0;
}