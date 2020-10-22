#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double func(double x){
    return 4/(1+x*x);
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
    // printf("TrapezoidalRule : %1.16lf\n",TrapezoidalRule(0,1,8));
    // printf("SimpsonRule : %1.16lf\n",SimpsonRule(0,1,8));
    printf("-----Trapesoidal Rule's result-----\n");
    printf("n =  1  result = %.10lf  error = %.10lf\n",TrapezoidalRule(0,1,1),fabs(TrapezoidalRule(0,1,1)-M_PI));
    printf("n =  2  result = %.10lf  error = %.10lf\n",TrapezoidalRule(0,1,2),fabs(TrapezoidalRule(0,1,2)-M_PI));
    printf("n =  8  result = %.10lf  error = %.10lf\n",TrapezoidalRule(0,1,8),fabs(TrapezoidalRule(0,1,8)-M_PI));
    printf("n = 16  result = %.10lf  error = %.10lf\n",TrapezoidalRule(0,1,16),fabs(TrapezoidalRule(0,1,16)-M_PI));
    printf("n = 32  result = %.10lf  error = %.10lf\n",TrapezoidalRule(0,1,32),fabs(TrapezoidalRule(0,1,32)-M_PI));
    printf("\n-----Simpson Rule's result-----\n");
    printf("n =  1  result = %.10lf  error = %.10lf\n",SimpsonRule(0,1,1),fabs(SimpsonRule(0,1,1)-M_PI));
    printf("n =  2  result = %.10lf  error = %.10lf\n",SimpsonRule(0,1,2),fabs(SimpsonRule(0,1,2)-M_PI));
    printf("n =  8  result = %.10lf  error = %.10lf\n",SimpsonRule(0,1,8),fabs(SimpsonRule(0,1,8)-M_PI));
    printf("n = 16  result = %.10lf  error = %.10lf\n",SimpsonRule(0,1,16),fabs(SimpsonRule(0,1,16)-M_PI));
    printf("n = 32  result = %.10lf  error = %.10lf\n",SimpsonRule(0,1,32),fabs(SimpsonRule(0,1,32)-M_PI));

    return 0;
}