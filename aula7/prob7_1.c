#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double first_method(double, int);
double second_method(double, int);
int is_pow(int,int);
int Num_mult=0;

int main(void){ 	
	for(int i=1;i<=16;i++){
		double Result=second_method(0.5,i);
		//double Result=(double) is_pow(32,2);
		fprintf(stdout, "Resultdo = %3f N. de Multiplicacoes = %3d\n",Result, Num_mult);
		Num_mult=0;
	}
}

double first_method(double x, int n){
	if(n==0){
		return 1;
	}
	Num_mult++;	
	return x*first_method(x, n-1);
}
double second_method(double x,int n){
	if(n==0){
		return 1;
	}
	else if((n%2)==0){
		Num_mult++;
		return pow(second_method(x,n/2),2);
	}
	else{
		Num_mult+=2;
		return x*pow(second_method(x,n/2),2);
	}

}

int is_pow(int a, int b){
	if(a==b || a==1){
		return 1;
	}
	else if(a%b==0){
		Num_mult++;
		return 1*is_pow(a/b,b);
	}
	else{
		return 0;
	}
}

