#include <stdio.h>
#include <stdlib.h>

/* allusion to the function that implements the algorithm */
int BiggerThanPred (int [], int);

/* global variable for counting the arithmetic operations executed by the algorithm */
int Comp = 0;

int main (void)
{
	/* declaration of the test arrays - use each one for each execution */

	//int Array[] = { 1, 9, 2, 8, 3, 4, 5, 3, 7, 2 }; 
	 //int Array[] = { 1, 7, 4, 6, 5, 2, 3, 2, 1, 0 }; 
	int Array[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
	//int Array[]={4,5,1,2,6,8,7,9,3,10};
	//int Array[] = { };
	int NElem = sizeof (Array) / sizeof (int); int Result;

	/* invocação do algoritmo pretendido - algorithm invocation */
	Result = BiggerThanPred (Array, NElem);

	/* presenting the result and the number of comparation operations executed by the algorithm */

	fprintf (stdout, "Resultado = %3d N. de operacoes = %3d\n", Result, Comp);

	exit (EXIT_SUCCESS);
}


/* implementation of the pretended algorithm */
/* do not forget to count the arithmetic operations using the global variable */

int BiggerThanPred (int array[], int n)
{
//pretende-se determinar qual e o primeiro elemento da sequencia que tem mais elementos menores do que ele atras de si, indicando a posicao (indice do array) onde ele se encontra.
	if(n<2){
		return 0;
	}
	int res=0;
	int ind=-1;
	for(int i=1;i<n;i++){
		int count=0;
		for(int j=0;j<i;j++){
			Comp++;
			if(array[j]<array[i]){
				count++;
			}
		}
		if(count>res){
			ind=i;
			res=count;
		}
	}
	return ind;

}
