#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define	NUM_OF_ELEMES 10
int main(void){
	int sum;
	int i;
	for(i=100;i<1000;i++){
		sum=0;
		int score=i;
		while(score){
			int d=score%10;
			sum+=(int)pow((float)d,3);
			score/=10;
		}
		if(i==sum) fprintf(stdout,"%2d\n",i);
	}

}

