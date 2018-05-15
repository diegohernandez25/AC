#include <stdio.h>
#include <stdlib.h>

/* allusion to the function that implements the algorithm */
int CountElements (int [], int);

/* global variable for counting the arithmetic operations executed by the algorithm */
int Comp = 0;

int main (void)
{
	/* declaration of the test arrays - use each one for each execution */
	
	 //int Array[] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 }; 
//	int Array[] = { 4, 3, 3, 3, 3, 3, 3, 3, 3, 3 }; 
//	 int Array[] = { 4, 5, 3, 3, 3, 3, 3, 3, 3, 3 }; 
//	 int Array[] = { 4, 5, 1, 3, 3, 3, 3, 3, 3, 3 }; 
//	 int Array[] = { 4, 5, 1, 2, 3, 3, 3, 3, 3, 3 }; 
//	 int Array[] = { 4, 5, 1, 2, 6, 3, 3, 3, 3, 3 }; 
//	 int Array[] = { 4, 5, 1, 2, 6, 8, 3, 3, 3, 3 }; 
//	 int Array[] = { 4, 5, 1, 2, 6, 8, 7, 3, 3, 3 }; 
//	 int Array[] = { 4, 5, 1, 2, 6, 8, 7, 9, 3, 3 }; 
	int Array[] = { 4, 5, 1, 2, 6, 8, 7, 9, 3, 0 }; 

	//int Array[] = { };
	int NElem = sizeof (Array) / sizeof (int); int Result;

	/* algorithm invocation */
	Result = CountElements (Array, NElem);

	/* presenting the result and the number of arithmetic operations executed by the algorithm */
	fprintf (stdout, "Resultado = %3d N. de operacoes = %3d\n", Result, Comp);

    exit (EXIT_SUCCESS);
}

/* implementation of the pretended algorithm */
/* do not forget to count the arithmetic operations using the global variable */

int CountElements (int array[], int n)
{
	int count=0;
	if(n<2){
		exit(EXIT_FAILURE);
	}
	for(int i=1;i<n;i++){
		if(array[i]!=array[i-1]){
			count++;	
		}
		Comp++;
	}
	return count;
}
