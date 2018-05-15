#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int fibonacci_rec(int);
int fibonacci_din(int);
int Num_mult=0;

int main(void){ 
	for(int i=0;i<=12;i++){	
		//double Result=(double) fibonacci_rec(i);
		double Result=(double) fibonacci_din(i);
		fprintf(stdout, "Resultdo = %3f N. de Multiplicacoes = %3d\n",Result, Num_mult);
		Num_mult=0;
	}
}

int fibonacci_rec(int n){
	if(n<2){
		return n;
	}
	else{
		Num_mult+=2;
		return 3*fibonacci_rec(n-1)+2*fibonacci_rec(n-2);
	}
}
int fibonacci_din(int n){
	if(n<2){
		return n;
	}
	int f[n];
	f[0]=0;
	f[1]=1;
	for(int i=2;i<=n;i++){
		f[i]=3*f[i-1]+2*f[i-2];
		Num_mult+=2;
	}
	return f[n];
}
