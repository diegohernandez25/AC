/*******************************************************************************
 Ficheiro de implementação do Tipo de Dados Abstracto SEQ_LIST (seqlist.c).
 A estrutura de dados de suporte da sequência é uma estrutura, constituída pelos
 campos de tipo inteiro Size para indicar o número de elementos armazenados na
 sequência e os campos de tipo ponteiro para nós de lista biligada Head e Tail,
 para representar, respectivamente, a cabeça e a cauda da lista biligada onde
 são armazenados os números inteiros.

 Autor : Diego Caldeira Hernandez                               NMEC :77013
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "seqlist.h"  /* Ficheiro de interface do TDA - ADT Interface file */

/************ Definição da Estrutura de Dados Interna da Sequência ************/

typedef struct binode *PtBiNode;
struct binode /* definição do nó da lista biligada */
{
	int Elem; /* o elemento da lista */
	PtBiNode PtPrev, PtNext; /* ponteiros para o nós anterior e seguinte */
};

struct seqlist
{
  int Size; /* número de elementos - sequence's size */
  PtBiNode Head; /* ponteiro para o início da lista (cabeça da lista) - list head */
  PtBiNode Tail; /* ponteiro para o fim da lista (cauda da lista) - list tail */
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
                                 "ficheiro inexistente - File does not exist",
                                 "ponteiro nulo - Null pointer"
                               };

static char *AbnormalErrorMessage = "erro desconhecido - Unknown error";

/************** Número de mensagens de erro previstas no módulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/******************** Protótipos dos Subprogramas Internos ********************/

PtBiNode BiNodeCreate (int);
void BiNodeDestroy (PtBiNode *);
void DoubleListDestroy (PtBiNode *);

/*************************** Definição das Funções ****************************/

void SeqListClearError (void)
{ Error = OK; }

int SeqListError (void)
{ return Error; }

char *SeqListErrorMessage (void)
{
  if (Error < N) return ErrorMessages[Error];
  else return AbnormalErrorMessage;  /* sem mensagem de erro - no error message */
}

PtSeqList SeqListCreate ()
{
	PtSeqList SeqList;
	if((SeqList= malloc(sizeof(struct seqlist)))==NULL){
		Error=NO_MEM;
		return NULL;
	}
	SeqList->Size=0;
	SeqList->Head=NULL;
	SeqList->Tail=NULL;
	Error=OK;
	return SeqList;
}

void SeqListDestroy (PtSeqList *pseq)
{
	PtSeqList TmpSeqList= *pseq;
	if(TmpSeqList==NULL){
		Error=NO_SEQ;
		return;
	}
	if(TmpSeqList->Head!=NULL){
		PtBiNode TmpHead=TmpSeqList->Head;
		DoubleListDestroy(&TmpHead);
	}
	free(TmpSeqList);
	Error=OK;
	*pseq=NULL;
	return;
}

PtSeqList SeqListCopy (PtSeqList pseq)
{
  PtSeqList Copy;

  /* verifica se a sequência existe - verifies if sequence exists */
  if (pseq == NULL) { Error = NO_SEQ; return NULL; }

  /* criação da sequência copia nulo - creating an empty sequence */
  if ((Copy = SeqListCreate ()) == NULL) return NULL;

  /* fazer a copia da sequência - copying the components */
  for (PtBiNode Node = pseq->Head; Node != NULL; Node = Node->PtNext)
  {
    SeqListInsert (Copy, Node->Elem);
    if (Error == NO_MEM) break;
  }

  if (Error == NO_MEM) { SeqListDestroy (&Copy); return NULL; }

  Copy->Size = pseq->Size;
  Error = OK;
  return Copy;  /* devolve a sequência copia - returning the new sequence */
}

PtSeqList SeqListFileCreate (char *pfname)
{
  PtSeqList Seq; FILE *PtF; unsigned int Size, I; int Elem;

  /* abertura com validacao do ficheiro para leitura - opening the text file for reading */
  if ( (PtF = fopen (pfname, "r")) == NULL) { Error = NO_FILE; return NULL; }

  /* leitura da dimensão da sequência e do número de elementos */
  /* reading the sequence's dimension and the number of elements */
  fscanf (PtF, "%u", &Size);
  if (Size < 1) { Error = BAD_SIZE; fclose (PtF); return NULL; }

  /* criação da sequência vazia - creating an empty sequence */
  if ((Seq = SeqListCreate ()) == NULL) { fclose (PtF); return NULL; }

  Error = OK;
  /* leitura da sequência do ficheiro - reading the sequence's components from the text file */
  for (I = 0; I < Size; I++)
  {
    fscanf (PtF, "%d", &Elem);
    SeqListInsert (Seq, Elem);
    if (Error == NO_MEM) break;
  }

  if (Error == NO_MEM) { SeqListDestroy (&Seq); return NULL; }

  fclose (PtF);  /* fecho do ficheiro - closing the text file */
  return Seq;  /* devolve a sequência criada - returning the new sequence */
}

void SeqListStoreFile (PtSeqList pseq, char *pfname)
{
  FILE *PtF;

  /* verifica se a sequência existe - verifies if sequence exists */
  if (pseq == NULL) { Error = NO_SEQ; return ; }

  /* verifica se a sequência tem elementos - verifies if sequence has elements */
  if (pseq->Size == 0) { Error = SEQ_EMPTY; return ; }

  /* abertura com validacao do ficheiro para escrita - opening the text file for writing */
  if ((PtF = fopen (pfname, "w")) == NULL) { Error = NO_FILE; return ; }

  /* escrita do número de elementos armazenados na sequência */
  /* writing the number of elements */
  fprintf (PtF, "%u\n", pseq->Size);

  /* escrita da sequência - writing the sequence's components in the text file */
  for (PtBiNode Node = pseq->Head; Node != NULL; Node = Node->PtNext)
	fprintf (PtF, "%d\n", Node->Elem);

  Error = OK;
  fclose (PtF);  /* fecho do ficheiro - closing the text file */
}

int SeqListGetSize (PtSeqList pseq)
{
	if(pseq==NULL){
		Error=NO_SEQ;
		return 0;
	}
	Error=OK;
	return pseq->Size;
}

int SeqListGetElement (PtSeqList pseq, int pindex)
{
  	if(pseq==NULL){
		Error=NO_SEQ;
		return 0;
	}
	if((pindex <= -(pseq->Size)) || (pindex>=pseq->Size)){
		Error=BAD_INDEX;
		return 0;
	}
	Error=OK;
	int i;
	PtBiNode Node;
	if(pindex>=0){
		Node=pseq->Head;
		for(i=0;i<pindex;i++){
			Node=Node->PtNext;
		}
	}
	else{
		Node=pseq->Tail;
		for(i=0;i<(-pindex)-1;i++){
			Node=Node->PtPrev;
		}
	}
	return Node->Elem;
}

void SeqListSetElement (PtSeqList pseq, int pindex, int pvalue)
{
	if(pseq==NULL){
		Error=NO_SEQ;
		return;
	}
	if((pindex <= -(pseq->Size)) || (pindex>=pseq->Size)){
		Error=BAD_INDEX;
		return;
	}
	Error=OK;
	int i;
	PtBiNode Node;
	if(pindex>=0){
		Node=pseq->Head;
		for(i=0;i<pindex;i++){
			Node=Node->PtNext;
		}
	}
	else{
		Node=pseq->Tail;
		for(i=0;i<((-pindex)-1);i++){
			Node=Node->PtPrev;
		}
	}
	Node->Elem=pvalue;
	return;
}

int SeqListEquals (PtSeqList pseq1, PtSeqList pseq2)
{
	if((pseq1==NULL) && (pseq2==NULL)){
		Error=NO_SEQ;
		return 0;
	}
	Error=OK;
	if(pseq1==pseq2){
		return 1;
	}
	PtBiNode Node1=pseq1->Head;
	PtBiNode Node2=pseq2->Head;
	if((pseq1->Size)==(pseq2->Size)){
		//for(int i=0;i<=(pseq1->Size);i++){
		while(Node1!=NULL && Node2!=NULL){
			if(Node1->Elem!=Node2->Elem){
				return 0;
			}
			Node1=Node1->PtNext;
			Node2=Node2->PtNext;
		}
		return 1;
	}
	return 0;
	
}

void SeqListInsert (PtSeqList pseq, int pvalue)
{
	if(pseq==NULL){
		Error=NO_SEQ;
		return;
	}
	if((pseq->Size==0) && (pseq->Head==NULL) && (pseq->Tail==NULL)){
		PtBiNode Node= BiNodeCreate(pvalue);
		pseq->Head=Node;
		pseq->Tail=Node;
		Node->PtNext=NULL;
		Node->PtPrev=NULL;	
	}
	else{
		PtBiNode Node=pseq->Tail;
		PtBiNode Copy=pseq->Tail;
		Node->PtNext=BiNodeCreate(pvalue);
		if((Node=Node->PtNext)==NULL){
			Error=NO_MEM;
			return;
		}
		pseq->Tail=Node;
		Node->PtPrev=Copy;
	}
	pseq->Size++;
	Error=OK;
	return;
}

void SeqListDelete (PtSeqList pseq, int pvalue)
{
	
	if(pseq==NULL){
		Error=NO_SEQ;
		return;
	}
	if(pseq->Size==0){
		Error=SEQ_EMPTY;
		return;
	}
	PtBiNode Node=pseq->Head;
	int count=0;
	//for(int i=0;i<(pseq->Size);i++){
	while(Node!=NULL){
		if(Node->Elem==pvalue){
			PtBiNode Copy=Node;
			PtBiNode Previous=Copy->PtPrev;
			PtBiNode Next=Copy->PtNext;	
			if(Next==NULL){
				pseq->Tail=Previous;
			}
			else{
				Next->PtPrev=Previous;
				if(Next->PtNext==NULL){
					pseq->Tail=Next;
				}
			}
			if(Previous==NULL){
				pseq->Head=Next;
			}
			else{
				Previous->PtNext=Next;
				if(Previous->PtPrev==NULL){
					pseq->Head=Previous;
				}
			}
			Node=Node->PtNext;
			BiNodeDestroy(&Copy);
			count++;
		}
		else{
			Node=Node->PtNext;
		}
	}
	if(count==0){
		Error=NO_NUMBER;
		return;
	}
	pseq->Size-=count;
	Error=OK;
	return;
}

int SeqListIsOrdered (PtSeqList pseq)
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
	if(pseq->Size==1){
		return 1;
	}
	PtBiNode Node1=pseq->Head;
	PtBiNode Node2=Node1->PtNext;
	//for(int i=0;i<(pseq->Size-1);i++){
	while(Node2!=NULL){
		if((Node1->Elem)>(Node2->Elem)){
			return 0;
		}
		Node1=Node1->PtNext;
		Node2=Node2->PtNext;
	}
	return 1;

}

int SeqListIsEvenOdd (PtSeqList pseq)
{
  	if(pseq==NULL){
		Error=NO_SEQ;
		return 0;
	}
	if(pseq->Size==0){
		Error=SEQ_EMPTY;
		return 0;
	}
	PtBiNode Node=pseq->Head;
	int pair=0;
	if((Node->Elem)%2==0){
		pair=1;
	}
	Error=OK;
	if(pseq->Size==1){
		return 0;//como nao e especificado se uma sequencia de um elemento e considerado sequencia alternada par e impar retorno falso pois so existe um numero de um tipo (par ou impar e nao os dois ao mesmo tempo)
	}
	//for(int i=1;i<pseq->Size;i++){
	Node=Node->PtNext;
	while(Node!=NULL){
		if(pair==1 && ((Node->Elem)%2!=0)){
			pair=0;
		}
		else if(pair==0 && ((Node->Elem)%2==0)){
			pair=1;
		}
		else{
			return 0;
		}
		Node=Node->PtNext;
	}
	return 1;
}

int SeqListNumberOfMultiples (PtSeqList pseq, int pvalue)
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
	PtBiNode Node=pseq->Head;
	//for(int i=0;i<pseq->Size;i++){
	while(Node!=NULL){
		if(((Node->Elem) % pvalue)==0){
			count++;
		}	
		Node=Node->PtNext;
	}
	Error=OK;
	return count;
}

void SeqListSmallerBigger (PtSeqList pseq, int * psmall, int * pbig)
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
	PtBiNode Node=pseq->Head;
	big=Node->Elem;
	small=Node->Elem;
	//for(int i=1; i<pseq->Size;i++){
	while(Node!=NULL){
		if((Node->Elem) > big){
			big=Node->Elem;
		}
		if((Node->Elem) < small){
			small=Node->Elem;
		}
		Node=Node->PtNext;
	}
	*psmall=small;
	*pbig=big;
	Error=OK;
	return;

}

int SeqListIsPalindromic (PtSeqList pseq)
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
	PtBiNode Node_Head=pseq->Head;
	PtBiNode Node_Tail=pseq->Tail;
	for(int i=0;i<pseq->Size;i++){
		if(i==(pseq->Size-1-i)){
			break;
		}
		if(Node_Head->Elem!=Node_Tail->Elem){
			return 0;
		}
		Node_Head=Node_Head->PtNext;
		Node_Tail=Node_Tail->PtPrev;
	}
	return 1;
}

double SeqListAverage (PtSeqList pseq)
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
	PtBiNode Node=pseq->Head;
	while(Node!=NULL){
		sum+=Node->Elem;
		Node=Node->PtNext;
	}
	return (sum/(pseq->Size));
}

/*******************************************************************************
 Função auxiliar para criar um nó da lista biligada. Valores de erro: OK ou NO_MEM.

 Auxiliary function to create a binode. Error codes: OK or NO_MEM.
*******************************************************************************/

PtBiNode BiNodeCreate (int pelem)	/* alocação do nó */
{
	PtBiNode Node;

	if ((Node = (PtBiNode) malloc (sizeof (struct binode))) == NULL)
	{ Error = NO_MEM; return NULL; }

	Node->Elem = pelem;	/* copiar a informação */
	Node->PtPrev = NULL;	/* apontar para detrás para NULL */
	Node->PtNext = NULL;	/* apontar para a frente para NULL */

	Error = OK;
	return Node;
}

/*******************************************************************************
 Função auxiliar para libertar um nó da lista biligada. Valores de erro: OK ou NULL_PTR.

 Auxiliary function to free a binode. Error codes: OK or NULL_PTR.
*******************************************************************************/
void BiNodeDestroy (PtBiNode *pnode)	/* libertação do nó */
{
	if (*pnode == NULL) { Error = NULL_PTR; return; }
	free (*pnode);	/* libertação do nó */
	*pnode = NULL;	/* colocar o ponteiro a nulo */
	Error = OK;
}

/*******************************************************************************
 Função auxiliar para destruir uma lista biligada. Valores de erro: OK ou NULL_PTR.

 Auxiliary function to destroy a double link list. Error codes: OK or NULL_PTR.
*******************************************************************************/
void DoubleListDestroy (PtBiNode *phead)
{
	PtBiNode TmpHead = *phead; PtBiNode Node;

	if (TmpHead == NULL) { Error = NULL_PTR; return; }
	while (TmpHead != NULL)
	{
		Node = TmpHead; TmpHead = TmpHead->PtNext;
		BiNodeDestroy (&Node);
	}
	Error = OK;
}
