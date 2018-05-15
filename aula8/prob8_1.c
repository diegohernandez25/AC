#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int Schroder(int);
int Schroder_din(int);
int Num_mult=0;

int main(void){
	for(int i=0;i<=10000;i++){
		double Result=Schroder(i);
		fprintf(stdout, "Resultdo = %3f N. de Multiplicacoes = %3d\n",Result, Num_mult);
		Num_mult=0;
	}
}

int Schroder(int n){
	int sch=0;
	if(n==0){
		return 1;
	}
	for(int i=0; i<n;i++){
		Num_mult++;
		sch+=Schroder(i)+Schroder(n-i-1);
	}
	return sch+Schroder(n-1);
}

int Schroder_din(int n){
	int a[n+1];
	if(n==0){
		return 1;
	}
	a[0]=1;
	for (int i=1; i<=n;i++){
		int sch=0;
		for(int j=0;j<i;j++){
			sch+=a[j]+a[i-j-1];
			Num_mult++;	
		}
		a[i]=sch+a[i-1];
	}
	return a[n];
}

