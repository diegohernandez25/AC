#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

int main(void){
	int Result,Test;
	int sum,mult,i,d,score;
	int array[6]={0,0,0,0,0,0};
	do{
		printf("factoriao de: ");
		Test=scanf("%d", &score);
		scanf("%*[^\n]");
		scanf("%*c");
	}while(Test==0);
	assert(score<1000000);
	fprintf(stdout,"Factoriao de %d =",score);
	while(score){
		d=score%10;
		mult=1;
		while(d){
			mult*=(int)d;
			d--;
		}
		sum+=mult;
		score/=10;
	}
	fprintf(stdout,"%d\n",sum);
	exit(0);
}
