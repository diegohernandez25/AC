#include <stdio.h>
#include <stdlib.h>

/* allusion to the functions that implement the required algorithms */
int f1 (int);
int f2 (int);
int f3 (int);
/* global variable for counting the arithmetic operations executed by the algorithm */
int Count;

int main (void)
{
	int Result, Line, NLines, Test;
	int i=0;
	/* reading the limit value for the table */
	do
	{
		printf ("N de elementos da tabela? "); Test = scanf ("%d", &NLines);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (Test == 0);

    /* impression of the table values for the algorithm's execution */
	for(i=1;i<=3;i++){
		printf("\n");
		for (Line = 1; Line <= NLines; Line++)
		{
        	/* initialization of the global variable for counting the arithmetic operations */
			Count = 0;

			/* invocation of the pretended algorithm */
			if(i==1){
				Result = f1 (Line);
			}
			if(i==2){
				Result = f2 (Line);
			}
			if(i==3){
				Result = f3 (Line);
			}

			/* presenting the result and the number of arithmetic operations executed by the algorithm */
			fprintf (stdout, "F%1d(%2d) = %10d e executou %10d somas\n",i, Line, Result, Count);
		}
	}
	exit (EXIT_SUCCESS);
}

/* implementation of the pretended algorithms */
/* do not forget to count the arithmetic operations using the global variable */

int fx (int n)
{
	return 0;	
}
int f1(int n){

	int i,j,r=0;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			r+=1;
			Count++;
		}
	}
	return r;
}

int f2(int n){
	int i,j,r=0;
	for(i=1;i<=n;i++){
		for(j=1;j<=i;j++){
			r+=1;
			Count++;
		}
	}
	return r;
}

int f3(int n){
	int i,j,r=0;
	for(i=1;i<=n;i++){
		for(j=i;j<=n;j++){
			r+=j;
			Count++;
		}
	}
	return r;
}















