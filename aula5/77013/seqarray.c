/*******************************************************************************
 Ficheiro de implementação do Tipo de Dados Abstracto SEQ_ARRAY (seqarray.c).
 A estrutura de dados de suporte da sequência é um registo, constituída pelos
 campos de tipo inteiro Dim para indicar a capacidade de armazenamento da
 sequência e Size para indicar o número de elementos efectivamente armazenados na
 sequência e o campo de tipo ponteiro Seq, para representar a sequência (array)
 atribuída dinamicamente onde são armazenados os números inteiros.

 Autor : Diego Caldeira Hernandez                                NMEC :77013
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "seqarray.h"  /* Ficheiro de interface do TDA - ADT Interface file */

/************ Definição da Estrutura de Dados Interna da Sequência ************/

struct seqarray
{
  unsigned int Dim; /* capacidade de armazenamento - array's size */
  int Size; /* número de elementos - sequence's size */
  int *Seq; /* ponteiro para armazenar a sequencia - array to store the numbers */
};

/*********************** Controlo Centralizado de Error ************************/

static unsigned int Error = OK;  /* inicialização do erro */

static char *ErrorMessages[] = {
                                 "sem erro - Without Error",
                                 "sequencia(s) inexistente(s) - Sequence(s) do not exist",
                                 "memoria esgotada - Out of memory",
                                 "indice errado - Wrong index",
                                 "elemento inexistente - Element does not exist",
                                 "sequencia vazia - Empty sequence",
                                 "sequencia cheia - Full sequence",
                                 "dimensao da sequencia errada - Wrong size",
                                 "ficheiro inexistente - File does not exist"
                               };

static char *AbnormalErrorMessage = "erro desconhecido - Unknown error";

/************** Número de mensagens de erro previstas no módulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/*************************** Definição das Funções ****************************/

void SeqArrayClearError (void)
{ Error = OK; }

int SeqArrayError (void)
{ return Error; }

char *SeqArrayErrorMessage (void)
{
  if (Error < N) return ErrorMessages[Error];
  else return AbnormalErrorMessage;  /* sem mensagem de erro - no error message */
}

PtSeqArray SeqArrayCreate (unsigned int pdim)
{
	PtSeqArray SeqArray;
	if((SeqArray= malloc(sizeof(struct seqarray)))==NULL){
		Error=NO_MEM;
		return NULL;
	}	
	SeqArray->Dim=pdim;
	SeqArray->Size=0;
	if((SeqArray->Seq=(int *) calloc(pdim, sizeof(int)))==NULL){
		Error=NO_MEM;
		return NULL;
	}
	Error=OK;
	return SeqArray;
}

void SeqArrayDestroy (PtSeqArray *pseq)
{
	PtSeqArray TmpSeqArray= *pseq;
	if(TmpSeqArray==NULL){
		Error=NO_SEQ;
		return;
	}
	free(TmpSeqArray);
	Error=OK;
	*pseq=NULL;
}

PtSeqArray SeqArrayCopy (PtSeqArray pseq)
{
  PtSeqArray Copy; int I;

  /* verifica se a sequência existe - verifies if sequence exists */
  if (pseq == NULL) { Error = NO_SEQ; return NULL; }

  /* criação da sequência copia vazia - creating an empty sequence */
  if ((Copy = SeqArrayCreate (pseq->Dim)) == NULL) return NULL;

  /* fazer a copia dos elementos da sequência - copying the components */
  for (I = 0; I < pseq->Size; I++) Copy->Seq[I] = pseq->Seq[I];
  Copy->Size = pseq->Size;

  return Copy;  /* devolve a sequência copia - returning the new sequence */
}

PtSeqArray SeqArrayFileCreate (char *pfname)
{
  PtSeqArray Seq; FILE *PtF; unsigned int Dim, Size, I;

  /* abertura com validacao do ficheiro para leitura - opening the text file for reading */
  if ( (PtF = fopen (pfname, "r")) == NULL) { Error = NO_FILE; return NULL; }

  /* leitura da dimensão da sequência e do número de elementos armazenados */
  /* reading the sequence's dimension and the number of elements */
  fscanf (PtF, "%u %u", &Dim, &Size);
  if (Dim < 1) { Error = BAD_SIZE; fclose (PtF); return NULL; }

  /* criação da sequência com a dimensão pretendida - creating the sequence */
  if ((Seq = SeqArrayCreate (Dim)) == NULL) { fclose (PtF); return NULL; }

  /* leitura da sequência do ficheiro - reading the sequence's components from the text file */
  for (I = 0; I < Size; I++) fscanf (PtF, "%d", Seq->Seq+I);
  Seq->Size = Size;

  fclose (PtF);  /* fecho do ficheiro - closing the text file */
  Error = OK;
  return Seq;  /* devolve a sequência criada - returning the new sequence */
}

void SeqArrayStoreFile (PtSeqArray pseq, char *pfname)
{
  FILE *PtF; unsigned int I;

  /* verifica se a sequência existe - verifies if sequence exists */
  if (pseq == NULL) { Error = NO_SEQ; return ; }

  /* verifica se a sequência tem elementos - verifies if sequence has elements */
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return ; }

  /* abertura com validacao do ficheiro para escrita - opening the text file for writing */
  if ((PtF = fopen (pfname, "w")) == NULL) { Error = NO_FILE; return ; }

  /* escrita da dimensão da sequência e do número de elementos armazenados na sequência */
  /* writing the sequence's dimension and the number of elements */
  fprintf (PtF, "%u %u\n", pseq->Dim, pseq->Size);

  /* escrita da sequência - writing the sequence's components in the text file */
  for (I = 0; I < pseq->Size; I++) fprintf (PtF, "%d\n", pseq->Seq[I]);

  Error = OK;
  fclose (PtF);  /* fecho do ficheiro - closing the text file */
}

int  SeqArrayGetDimension (PtSeqArray pseq)
{
	if(pseq==NULL){
		Error=NO_SEQ;
		return 0;
	}
	Error=OK;
	return pseq->Dim;
}

int SeqArrayGetSize (PtSeqArray pseq)
{
  	if(pseq==NULL){
		Error=NO_SEQ;
		return 0;	
	}
	Error=OK;
	return pseq->Size;
}

int SeqArrayGetElement (PtSeqArray pseq, int pindex)
{
  	if(pseq==NULL){
		Error=NO_SEQ;
		return 0;
	}
	Error=OK;
	if(pindex<=-(pseq->Size) || pindex>=pseq->Size){
		Error=BAD_INDEX;
		return 0;
	}
	if((pindex)>=0){
		return pseq->Seq[pindex];
	}
	else if(pindex<0){
		int pos=(pseq->Size)-pindex;		
		return pseq->Seq[pos];
	}
}

void SeqArraySetElement (PtSeqArray pseq, int pindex, int pvalue)
{
	if(pseq==NULL){
		Error=NO_SEQ;
		return;
	}
	if(pindex<=-(pseq->Size) || pindex>=pseq->Size){
		Error=BAD_INDEX;
		return;
	}
	if(pindex>=0){
		pseq->Seq[pindex]=pvalue;
	}
	else if(pindex<0){
		int pos=(pseq->Size)-pindex;		
		pseq->Seq[pos]=pvalue;
	}
	Error=OK;
	return;
}

int SeqArrayEquals (PtSeqArray pseq1, PtSeqArray pseq2)
{
  	if(pseq1==NULL || pseq2==NULL){
  		Error=NO_SEQ;
		return 0;
  	}
  	Error=OK;
  	if(pseq1==pseq2){
  		return 1;
  	}
  	if(pseq1->Size==pseq2->Size){
  		for (int I = 0; I < pseq1->Size; I++){
			if(pseq1->Seq[I]!=pseq2->Seq[I]){
				return 0;
			}
		}
		return 1;
  	}
  	return 0;
}

void SeqArrayInsert (PtSeqArray pseq, int pvalue)
{
	if(pseq==NULL){
		Error=NO_SEQ;
		return;
	}
	if(pseq->Dim==pseq->Size){
		Error=SEQ_FULL;
		return;
	}
	pseq->Seq[pseq->Size]=pvalue;
	pseq->Size++;
	Error=OK;
	return;
}

void SeqArrayDelete (PtSeqArray pseq, int pvalue)
{
	if(pseq==NULL){
		Error=NO_SEQ;
		return;
	}
	if(pseq->Size==0){
		Error=SEQ_EMPTY;
		return;
	}
	int count=0;
	int *newSeq;
	if((newSeq=calloc(pseq->Dim, sizeof(int)))==NULL){
		Error=NO_MEM;
		return;
	}
	for(int I=0;I<pseq->Size;I++){
		if(pseq->Seq[I+count]==pvalue){
			count++;
			I--;
		}
		else{
			newSeq[I]=pseq->Seq[I+count];
		}
	}
	//no caso de ser o primeiro elemento a ser eliminado
	//int first_found=0;
	//for(int I=0;I<pseq->Size;I++){
	//	if(first_found==0 && pseq->Seq[I+count]==pvalue){
	//		count++;
	//		I--;
	//		first_found=1;
	//	}
	//	else{
	//		newSeq[I]=pseq->Seq[I+count];
	//	}
	//}
	if(count==0){
		Error=NO_NUMBER;
		return;
	}
	pseq->Size=pseq->Size-count;
	int *Tmp=pseq->Seq;
	pseq->Seq=newSeq;
	free(Tmp);
	Error=OK;
	return;
}

void SeqArrayDuplicate (PtSeqArray pseq)
{
  int *newSeq;
  /* verifica se a sequência existe - verifies if sequence exists */
  if (pseq == NULL) { Error = NO_SEQ; return; }

  /* verifica se a sequência não está vazia - verifies if sequence is not empty */
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return; }

  if ((newSeq = calloc (2*pseq->Size, sizeof (int))) == NULL)
  { Error = NO_MEM; return; }

  pseq->Dim = 2*pseq->Size;  /* armazenamento da nova dimensão - storing the new dimension */

  /* copiar os elementos - copying the elements */
  for (int I = 0; I < pseq->Size; I++) newSeq[I] = pseq->Seq[I];
  /* guardar o novo array e libertar o antigo - storing the new arry and freeing the old */
  int * Tmp = pseq->Seq; pseq->Seq = newSeq; free (Tmp);

  Error = OK;
}

int SeqArrayIsOrdered (PtSeqArray pseq)
{
	if(pseq==NULL){
		Error=NO_SEQ;
		return 0;
	}
	if(pseq->Size==0){
		Error=SEQ_EMPTY;
		return 0;
	}
	Error=OK;
	for(int I=1;I<pseq->Size;I++){
		if((pseq->Seq[I-1])>(pseq->Seq[I])){
			return 0;
		}
	}  
	return 1;
}

int SeqArrayIsEvenOdd (PtSeqArray pseq)
{
	if(pseq==NULL){
		Error=NO_SEQ;
		return 0;
	}
	if(pseq->Size==0){
		Error=SEQ_EMPTY;
		return 0;
	}
	int pair=0;
	if((pseq->Seq[0])%2==0){
		pair=1;
	}
	Error=OK;
	if(pseq->Size==1){
		return 0;//como nao e especificado se uma sequencia de um elemento e considerado sequencia alternada par e impar retorno falso
	}
  	for(int I=1; I<pseq->Size;I++){
		if(pair==1 && ((pseq->Seq[I])%2!=0)){//espera ser impar
			pair=0;
		}
		else if(pair==0 && ((pseq->Seq[I])%2==0)){//espera ser par
			pair=1;
		}
		else{
			return 0;
		}
	}
	return 1;
}

int SeqArrayNumberOfMultiples (PtSeqArray pseq, int pvalue)
{
 	if(pseq==NULL){
		Error=NO_SEQ;
		return 0;
	}
	if(pseq->Size==0){
		Error=SEQ_EMPTY;
		return 0;
	}
	int count=0;
	for(int I=0;I<pseq->Size;I++){
		if((pseq->Seq[I] % pvalue)==0){
			count++;
		}	
	}
	Error=OK;
	return count;
}

void SeqArraySmallerBigger (PtSeqArray pseq, int * psmall, int * pbig)
{
	int small=*psmall;
	int big=*pbig;
	if(pseq==NULL){
		Error=NO_SEQ;
		return;
	}
	if(pseq->Size==0){
		Error=SEQ_EMPTY;
		return;
	}
	big=pseq->Seq[0];
	small=big;
	for(int I=1;I<pseq->Size;I++){
		if(pseq->Seq[I]>big){
			big=pseq->Seq[I];
		}	
		if(pseq->Seq[I]<small){
			small=pseq->Seq[I];
		}
	}
	*psmall=small;
	*pbig=big;
	Error=OK;
	return;
}

int SeqArrayIsPalindromic (PtSeqArray pseq)
{
	if(pseq==NULL){
		Error=NO_SEQ;
		return 0;
	}
	if(pseq->Size==0){
		Error=SEQ_EMPTY;
		return 0;
	}
	Error=OK;
	for(int I=0;I<pseq->Size;I++){
		if(I==(pseq->Size-1-I)){
			break;
		}
		if(pseq->Seq[I]!=pseq->Seq[pseq->Size-1-I]){
			return 0;
		}	
			
	}
	return 1;
}

double SeqArrayAverage (PtSeqArray pseq)
{
	if(pseq==NULL){
		Error=NO_SEQ;
		return 0;
	}
	if(pseq->Size==0){
		Error=SEQ_EMPTY;
		return 0;
	}	
	Error=OK;
	double sum=0;
	for(int I=0;I<pseq->Size;I++){
		sum+=pseq->Seq[I];	
	}
	return (sum/(pseq->Size));
}
