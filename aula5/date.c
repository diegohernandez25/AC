/************************************************************************
 Ficheiro de implementação do Tipo de Dados Abstracto Data (date.c).
 A estrutura de dados de suporte do tempo é um registo constituído pelos
 três campos de tipo inteiro Day, Month e Year.

 Autor : DIEGO CALDEIRA HERNANDEZ                          NMEC :77013
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date.h" /* Ficheiro de interface do TDA - ADT Interface file */

/*************** Definição da Estrutura de Dados da Data ***************/

struct date
{
	unsigned int Day; unsigned int Month; unsigned int Year;
};

/******************** Controlo Centralizado de Erro ********************/

static unsigned int Error = OK;	/* inicialização do erro */

static char *ErrorMessages[] = { "sem erro", "data inexistente",
                                 "memoria esgotada", "data invalida",
				 "ponteiro inexistente" };

static char *AbnormalErrorMessage = "erro desconhecido";

/*********** Número de mensagens de erro previstas no módulo ***********/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/***************** Protótipos dos Subprogramas Internos ****************/

static int LeapYear (int); /* ano bissexto */
static int ValidDate (int, int, int); /* validar data */

/********************** Definição dos Subprogramas *********************/

void DateClearError (void)
{ Error = OK; }

int DateError (void)
{ return Error; }

char *DateErrorMessage (void)
{
	if (Error < N) return ErrorMessages [Error];
	else return AbnormalErrorMessage; /* sem mensagem de erro */
}

PtDate DateCreate (int pday, int pmonth, int pyear) /* construtor inicializador */
{
	if(!ValidDate(pday, pmonth, pyear)) return NULL;
		// typedef struct date *PtDate;
		PtDate Date;
  	if ((Date = malloc (sizeof (struct date))) == NULL){
		Error = NO_MEM;
		return NULL;
	}
  	Date->Day = pday; Date->Month = pmonth; Date->Year = pyear;
  	Error = OK;
  	return Date;
}

void DateDestroy (PtDate *pdate) /* destrutor */
{
	PtDate TmpDate=*pdate;
	if(TmpDate == NULL){
		Error=NO_DATE;
		return;
	}
	free(TmpDate);
	Error=OK;
	*pdate=NULL;
}

PtDate DateStringCreate (char *pstrdate) /* construtor a partir de uma string */
{
	if (pstrdate == NULL) { Error = NULL_PTR; return NULL; }
	if (strlen (pstrdate) != 10) { Error = INVALID; return NULL; }

	char * date[4]; int i = 0;

	date[i] = strtok (pstrdate, "-");
	while (date[i] != NULL) date[++i] = strtok (NULL, "-");

	if (i != 3) { Error = INVALID; return NULL; }

	int Year, Month, Day;
	sscanf (date[0], "%d", &Year);
	sscanf (date[1], "%d", &Month);
	sscanf (date[2], "%d", &Day);

	return DateCreate (Day, Month, Year);
}

PtDate DateCopy (PtDate pdate)	/* construtor cópia */
{
	if (pdate == NULL) { Error = NO_DATE; return NULL; }
	else return DateCreate (pdate->Day, pdate->Month, pdate->Year);
}

int  DateGetYear (PtDate pdate) /* observador do ano */
{
	if(pdate==NULL){
		Error=NO_DATE;
		return 0;
	}
	Error=OK;
	return pdate->Year;
}

int DateGetMonth (PtDate pdate) /* observador do mês */
{
	if (pdate == NULL) { Error = NO_DATE; return 0; }
	else { Error = OK; return pdate->Month; }
}

int DateGetDay (PtDate pdate) /* observador do dia */
{
	if(pdate==NULL){
		Error=NO_DATE;
		return 0;
	}
	Error=OK;
	return pdate->Day;

}

void DateSet (PtDate pdate, int pday, int pmonth, int pyear) /* modificador da data */
{
	//verifies if date exists
	if(pdate==NULL){
		Error=NO_DATE;
		return;
	}
	//DateSetDay
	if(pyear>=0 && pmonth>0 && pmonth<=12){
			switch(pmonth){
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					if(pday>0 && pday<=31){
						pdate->Month=pmonth;pdate->Year=pyear;pdate->Day=pday;
					}
					else{
						Error=INVALID;
					}
					break;
				case 4:
				case 6:
				case 9:
				case 11:
					if(pday>0 && pday<=30){
						pdate->Month=pmonth;pdate->Year=pyear;pdate->Day=pday;
					}
					else{
						Error=INVALID;
					}
					break;
				case 2:
					if(LeapYear(pyear)){
						if(pday>0 && pday<=29){
						pdate->Month=pmonth;pdate->Year=pyear;pdate->Day=pday;

						}
						else{
							Error=INVALID;
						}
					}
					else{
						if(pday>0 && pday<29){
							pdate->Month=pmonth;pdate->Year=pyear;pdate->Day=pday;
						}
						else{
							Error=INVALID;
						}
					}
					break;
			}
	}
	else{
		Error=INVALID;
	}
	return;
}

int DateEquals (PtDate pdate1, PtDate pdate2)  /* comparador de igualdade */
{
	if(pdate1==pdate2){
		return 1;
	}
	return DateCompareTo(pdate1,pdate2)==0;
}

int DateCompareTo (PtDate pdate1, PtDate pdate2)  /* operador relacional (> == <) */
{
	int res=DateGetYear(pdate1)-DateGetYear(pdate2);
	if(res==0){
		res=DateGetMonth(pdate1)-DateGetMonth(pdate2);
		if(res==0){
			return DateGetDay(pdate1)-DateGetDay(pdate2);
		}
	}
	return res;
}

int DateDayMonth (int pmonth, int pyear) /* dias de um mês */
{
	if(pmonth<1 || pmonth>12 || pyear<0){
		Error=INVALID;
		return 0;
	}
	int MonthDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if(pmonth!=2){
		return MonthDays[pmonth];
	}
	else{
		if(!LeapYear(pyear)){
			return MonthDays[pmonth];
		}
		else{
			return 29;
		}
	}
}

char * DateToString (PtDate pdate)  /* data no formato dd/mm/yyyy */
{
	/* verifica se a data existe - verifies if date exists */
	if (pdate == NULL) { Error = NO_DATE; return NULL; }

	char * Str;
	/* cria a sequência de caracteres - allocating the string */
	if ((Str = calloc (11, sizeof (char))) == NULL)
	{ Error = NO_MEM; return NULL; }

	sprintf (Str, "%02d/%02d/%04d", pdate->Day, pdate->Month, pdate->Year);
	Error = OK;
	return Str;
}

char * DateToFullString (PtDate pdate)  /* data por extenso */
{
	char* FullMonth[] = {"janeiro", "fevereiro", "março", "abril",
						 "maio", "junho", "julho", "agosto",
						 "setembro", "outubro", "novembro", "dezembro"};

	/* verifica se a data existe - verifies if date exists */
	if (pdate == NULL) { Error = NO_DATE; return NULL; }

	char * Str;
	/* cria a sequência de caracteres - allocating the string */
	if ((Str = calloc (23, sizeof (char))) == NULL)
	{ Error = NO_MEM; return NULL; }

	sprintf (Str, "%02d de %s de %04d", pdate->Day, FullMonth[pdate->Month-1], pdate->Year);
	Error = OK;
	return Str;
}

PtDate DateTomorrow (PtDate pdate)  /* nova data com o dia seguinte */
{
	if(pdate == NULL){
		Error = NO_DATE;
		return NULL;
	}
	int Day= DateGetDay(pdate);
	int Month= DateGetMonth(pdate);
	int Year= DateGetYear(pdate);

	if(Day<28){
		Day++;
	}
	else{
		switch(Month){
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				if(Day>0 && Day<31){
					Day++;
				}
				else{//Day31
					if(Month!=12){
						Month++;
					}
					else{
						Month=1;
						Year++;
					}
					Day=1;
				}
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				if(Day>0 && Day<30){
					Day++;
				}
				else{//Day30
					Month++;
					Day=1;
				}
				break;
			case 2:
				if(LeapYear(Year)){
					if(Day>0 && Day<29){
						Day++;
					}
					else{
						Day=1;
						Month++;
					}
				}
				else{
					if(Day>0 && Day<28){
						Day++;
					}
					else{
						Day=1;
						Month++;
					}
				}
				break;
		}
	}
	return DateCreate(Day,Month,Year);
}

PtDate DateYesterday (PtDate pdate)  /* nova data com o dia anterior */
{
	if(pdate==NULL){
		Error=NO_DATE;
		return NULL;
	}

	int Day= DateGetDay(pdate);
	int Month= DateGetMonth(pdate);
	int Year= DateGetYear(pdate);

	if(Day>1){
		Day--;
	}
	else{//DAY1
		switch(Month){
			case 1:
				Year--;
				Month=12;
				Day=31;
				break;
			case 2:
			case 4:
			case 6:
			case 8:
			case 9:
			case 11:
				Month--;
				Day=31;
				break;
			case 5:
			case 7:
			case 10:
			case 12:
				Month--;
				Day=30;
				break;
			case 3:
				if(LeapYear(Year)){
					Day=29;
				}
				else{
					Day=28;
				}
				Month--;
				break;
		}

	}
	return DateCreate(Day,Month,Year);
}

/*************** Implementação dos Subprogramas Internos ***************/

/*******************************************************************************
 Função auxiliar que verifica se um ano é bissexto. Devolve 1 em caso afirmativo
  e 0 em caso contrário. Valores de erro: OK.

 Auxiliary function to verify if a year is a leap year. Returns 1 in affirmative
 case and 0 otherwise. Error codes: OK.
*******************************************************************************/
static int LeapYear (int pyear)
{
	Error = OK;
	return ((pyear % 4 == 0) && (pyear % 100 != 0)) || (pyear % 400 == 0);
}

/*******************************************************************************
 Função auxiliar que verifica se uma data definida por dia, mês e ano é válida.
 Devolve 1 em caso afirmativo e 0 em caso contrário. Valores de erro: OK ou INVALID.

 Auxiliary function to verify if a date defined by day, month and year is valid.
 Returns 1 in affirmative case and 0 otherwise. Error codes: OK or INVALID.
*******************************************************************************/

static int ValidDate (int pday, int pmonth, int pyear)
{
	int leapyear;
	Error = OK;
	switch (pmonth)
	{
		case  1:
		case  3:
		case  5:
		case  7:
		case  8:
		case 10:
    		case 12: if (pday < 1 || pday > 31) Error = INVALID;
			 break;
    		case  4:
    		case  6:
    		case  9:
    		case 11: if (pday < 1 || pday > 30) Error = INVALID;
			 break;
    		case  2: leapyear = LeapYear (pyear);
                	 if (pday < 1 || (pday > 29 && leapyear) || (pday > 28 && !leapyear))
				Error = INVALID;
                	 break;
	}
	if (Error == OK) return 1; else return 0;
}
