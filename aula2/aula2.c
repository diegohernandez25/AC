#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "elapsed_time.h"


/* definition of the 64-bit unsigned integer type */
typedef unsigned long long u64;

/* allusion to the functions that implement the required algorithms */
u64 fib (u64);
u64 _fib(u64);
u64 fib1(u64);
u64 fib2(u64);
u64 fib3(u64);
/* global variable for counting the arithmetic operations executed by the algorithm */
u64 Count;

int main (void)
{
	//int Result, NLines, N, Test;
	int NLines, N, Test;
	unsigned long long int Result;
	double dt;
	/* reading the limit value for the table */
	do
	{
		printf ("N de elementos da tabela? "); Test = scanf ("%d", &NLines);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (Test == 0);

	(void)elapsed_time();
    /* impression of the table values for the algorithm's execution */
	for (N = 1; N <= NLines; N++)
	{
        /* initialization of the global variable for counting the arithmetic operations */
		Count = 0;

		/* invocation of the pretended algorithm */
		Result = _fib(N);

		/* presenting the result and the number of arithmetic operations executed by the algorithm */
		fprintf (stdout, "Fibonacci de %2d = %10lld e executou %10lld somas\n", N, Result, Count);
	}
	dt=elapsed_time();
	fprintf(stdout,"ellapsed time:%10.3f\n",dt);
	exit (EXIT_SUCCESS);
}


/* implementation of the pretended algorithms */
/* do not forget to count the arithmetic operations using the global variable */

u64 fib (u64 n)
{
	//assert(n>=0);
	if(n==0){
		return 0;
	}
	if(n==1){
		return 1;
	}
	Count++;
	return fib(n-1)+fib(n-2);

}
u64 _fib(u64 n){
	u64 aa=0;
	u64 a=1;
	u64 atual=0;
	if(n==0){
		return 0;
	}
	if(n==1){
		return 1;
	}
	for(u64 i=0;i<n;i++){
		atual=aa+a;
		aa=a;
		a=atual;
		Count++;
	}
	return atual;
}
u64 fib1(u64 n)
{
	double c=((1+sqrt(5))/2);
	Count++;
	return (unsigned long long)((pow(c,(double)n)-pow(1-c,(double)n))/sqrt(5));
}
u64 fib2(u64 n)
{
	double c=((1+sqrt(5))/2);
	Count++;
	return (unsigned long long int)round(pow(c,(double)n)/sqrt(5));
	
}

u64 fib3(u64 n)
{
	double c1=0.44721357549995773928;
	double c2=0.48121182505960344750;
	Count++;
	return (unsigned long long int)round(c1*exp((double)n*c2));

}
