/***************************************************************************
 ***                                                                     ***
 ***   Vitor Bellissimo Falleiros          Numero USP: 2962011           ***
 ***   Exercicio-Programa 01                                             ***
 ***   Professor: Routo Terada                                           ***
 ***   Computador: Pentium, 100 MHz                                      ***
 ***   Compilador: Turbo C++                                             ***
 ***                                                                     ***
 ***************************************************************************/

/*Objetivos do programa: dadas a data atual e a data de nascimento de certa
  pessoa, dizer o dia da semana naquela data e quantos dias ela viveu ate'
  hoje, incluindo hoje.*/


#include<stdio.h>

void main()
{
int DIA_HOJE, MES_HOJE, ANO_HOJE, DIA_NASC, MES_NASC, ANO_NASC;
	/* Variáveis para as datas de hoje e de nascimento da pessoa */
int VAI_HOJE, VAI_NASC;	/* Se data entrada existir, vira 0 */
long TOTAL;
int MESES, ANOS; /* Para contar os dias */
long SEMANA; /* Para calcular o dia da semana */
VAI_HOJE=1;VAI_NASC=1;
DIA_NASC=1;/* para que o programa entre no "while principal" */

printf("Benvindo ao programa DataNasc!!!\n");

while(VAI_HOJE==1)
 {printf("Digite o dia de hoje: "); scanf("%d",&DIA_HOJE);
  printf("Digite o mes atual: "); scanf("%d",&MES_HOJE);
  printf("Digite o ano atual: "); scanf("%d",&ANO_HOJE);

  if ((DIA_HOJE>31) || (DIA_HOJE>28 && MES_HOJE==2 && (ANO_HOJE%4!=0 ||
	  (ANO_HOJE%4==0 && ANO_HOJE%100==0 && ANO_HOJE%400!=0))) || (DIA_HOJE>29
	  && MES_HOJE==2) || (DIA_HOJE>30 && (MES_HOJE==4 || MES_HOJE==6 ||
	  MES_HOJE==9 || MES_HOJE==11)) || (MES_HOJE>12) || (MES_HOJE<1) ||
	  (DIA_HOJE<1))
	 printf("Esta data esta' incorreta.\n");
	 /*Verifica se a data entrada existe.*/
	else
	 {if(ANO_HOJE<1870)
		 printf("CUIDADO!!! Este programa so' funciona a partir de 1870.\n");
	  else {printf("Esta data esta' correta.\n"); VAI_HOJE=0;}
	 }
 }/* fim while */

while(DIA_NASC!=0) /*"while principal"*/
{
while(VAI_NASC==1)
 {printf("Digite o dia de seu nascimento: "); scanf("%d",&DIA_NASC);
  if(DIA_NASC==0) break;
  printf("Digite o mes de seu nascimento: "); scanf("%d",&MES_NASC);
  printf("Digite o ano de seu nascimento: "); scanf("%d",&ANO_NASC);

  if ((DIA_NASC>31) || (DIA_NASC>28 && MES_NASC==2 && (ANO_NASC%4!=0 ||
	  (ANO_NASC%4==0 && ANO_NASC%100==0 && ANO_NASC%400!=0))) || (DIA_NASC>29
	  && MES_NASC==2) || (DIA_NASC>30 && (MES_NASC==4 || MES_NASC==6 ||
	  MES_NASC==9 || MES_NASC==11)) || (MES_NASC>12) || (MES_NASC<1) ||
	  (DIA_NASC<1))
	 printf("Esta data esta' incorreta.\n");
	 /*Verifica se a data entrada existe.*/
	else{
		 if ((ANO_HOJE<ANO_NASC) || (ANO_HOJE==ANO_NASC && MES_HOJE<MES_NASC) ||
			 (ANO_HOJE==ANO_NASC && MES_HOJE==MES_NASC && DIA_HOJE<DIA_NASC))
			printf ("Voce ainda nao nasceu!!!\n");
		  else
			{if (ANO_NASC<1870)
			  printf("CUIDADO!!! Este programa s¢ funciona a partir de 1870.\n");
			else {printf("Esta data esta' correta.\n");VAI_NASC=0;}
			}
		 }
 }/* fim while */

if (DIA_NASC==0)
 {printf("Obrigado por usar nossos servicos. Volte sempre!!!\n");break;}

if(ANO_NASC==ANO_HOJE && MES_NASC==MES_HOJE)
  {TOTAL=DIA_HOJE-DIA_NASC;};
  /*Para o caso de a pessoa ter nascido no ano e mes atuais.*/

if(ANO_NASC==ANO_HOJE && MES_NASC<MES_HOJE)
  {if(MES_NASC==1 || MES_NASC==3 || MES_NASC==5 || MES_NASC==7 || MES_NASC==8
		|| MES_NASC==10)
	  {TOTAL=31-DIA_NASC;
		if (((ANO_NASC%4==0 && ANO_NASC%100!=0) || (ANO_NASC%400==0)) &&
			(MES_NASC==1 && MES_HOJE>2))
		  TOTAL=TOTAL+1;
		/* ano bissexto, com dia 29 entre data de nascimento e data atual*/
	  } /* fim do "if" dos meses de 31 dias */

	if(MES_NASC==2)
	  {TOTAL=28-DIA_NASC;
		if((ANO_NASC%4==0 && ANO_NASC%100!=0) || (ANO_NASC%400==0))
		  TOTAL=TOTAL+1; /* ano bissexto */
	  } /* fim do "if" do mes de fevereiro */

	if(MES_NASC==4 || MES_NASC==6 || MES_NASC==9 || MES_NASC==11)
	  TOTAL=30-DIA_NASC;

	MESES=MES_NASC+1;
	while(MESES<MES_HOJE)
	 {if(MESES==3 || MESES==5 || MESES==7 || MESES==8 || MESES==10)
		 TOTAL=TOTAL+31;
	  if(MESES==2) TOTAL=TOTAL+28;
	  if(MESES==4 || MESES==6 || MESES==9 || MESES==11) TOTAL=TOTAL+30;
	  MESES=MESES+1;
	 } /* fim while*/

	TOTAL=TOTAL+DIA_HOJE; /* para somar os dias do mes atual */

  } /* fim do "if" dos nascidos no ano atual mas nao no mes atual */

if (ANO_NASC<ANO_HOJE)
 {if (MES_NASC==1 || MES_NASC==3 || MES_NASC==5 || MES_NASC==7 ||
	  MES_NASC==8 || MES_NASC==10 || MES_NASC==12)
	 TOTAL=31-DIA_NASC;
  if (MES_NASC==2) TOTAL=28-DIA_NASC;
  if (MES_NASC==4 || MES_NASC==6 || MES_NASC==9 || MES_NASC==11)
	 TOTAL=30-DIA_NASC;
	 /*Dias do mes de nascimento*/
  if (((ANO_NASC%4==0 && ANO_NASC%100!=0) || (ANO_NASC%400==0)) && MES_NASC<3)
	 TOTAL=TOTAL+1; /*para nascimento em ano bissexto*/

  MESES=MES_NASC+1;
  while(MESES<13)
	{if(MESES==3 || MESES==5 || MESES==7 || MESES==8 || MESES==10 || MESES==12)
		TOTAL=TOTAL+31;
	 if(MESES==2) TOTAL=TOTAL+28;
	 if(MESES==4 || MESES==6 || MESES==9 || MESES==11) TOTAL=TOTAL+30;
	 MESES=MESES+1;
	}/*fim while*/

  ANOS=ANO_NASC+1;
  while(ANOS<ANO_HOJE)
	{TOTAL=TOTAL+365;
	 if ((ANOS%4==0 && ANOS%100!=0) || (ANOS%400==0)) TOTAL=TOTAL+1;
	 ANOS=ANOS+1;
	}/*fim while*/

  MESES=1; /*reinicializa o MESES para contar os dias do ano atual*/
  while(MESES<MES_HOJE)
	{if(MESES==1 || MESES==3 || MESES==5 || MESES==7 || MESES==8 || MESES==10)
	  TOTAL=TOTAL+31;
	 if(MESES==2) TOTAL=TOTAL+28;
	 if(MESES==4 || MESES==6 || MESES==9 || MESES==11) TOTAL=TOTAL+30;
	 MESES=MESES+1;
	}/*fim while*/

  TOTAL=TOTAL+DIA_HOJE; /*para somar os dias do mes atual*/

  if(((ANO_HOJE%4==0 && ANO_HOJE%100!=0) || (ANO_HOJE%400==0)) && MES_HOJE>2)
	 TOTAL=TOTAL+1;
	  /*para somar o dia 29 do ano atual se esse for bissexto*/
 }/*fim "if" das pessoas nascidas em anos anteriores ao atual*/

TOTAL=TOTAL+1; /*esse e' o dia do nascimento, que ainda nao foi contado*/

SEMANA=0;ANOS=1870;MESES=1;/*para calcular o dia da semana*/
while(ANOS<ANO_NASC)
 {SEMANA=SEMANA+365;
  if((ANOS%4==0 && ANOS%100!=0) || (ANOS%400==0)) SEMANA=SEMANA+1;
  ANOS=ANOS+1;
 }
while(MESES<MES_NASC)
 {if(MESES==1 || MESES==3 || MESES==5 || MESES==7 || MESES==8 || MESES==10)
	 SEMANA=SEMANA+31;
  if(MESES==2) SEMANA=SEMANA+28;
  if(MESES==4 || MESES==6 || MESES==9 || MESES==11) SEMANA=SEMANA+30;
  MESES=MESES+1;
 }
if(((ANO_NASC%4==0 && ANO_NASC%100!=0) || (ANO_NASC%400==0)) && MES_NASC>2)
	 SEMANA=SEMANA+1;
SEMANA=SEMANA+DIA_NASC;
 /*Essa parte calcula o dia da semana na data do nascimento, tomando como
	base uma sexta-feira, 31 de dezembro de 1869.*/

if(SEMANA%(long)7==0)
printf("Parabens: voce nasceu em uma sexta-feira, e ja' viveu %ld dia(s) ate' hoje.\n", TOTAL);
if(SEMANA%(long)7==1)
printf("Parabens: voce nasceu em um sabado, e ja' viveu %ld dia(s) ate' hoje.\n", TOTAL);
if(SEMANA%(long)7==2)
printf("Parabens: voce nasceu em um domingo, e ja' viveu %ld dia(s) ate' hoje.\n", TOTAL);
if(SEMANA%(long)7==3)
printf("Parabens: voce nasceu em uma segunda-feira, e ja' viveu %ld dia(s) ate' hoje.\n", TOTAL);
if(SEMANA%(long)7==4)
printf("Parabens: voce nasceu em uma terca-feira, e ja' viveu %ld dia(s) ate' hoje.\n", TOTAL);
if(SEMANA%(long)7==5)
printf("Parabens: voce nasceu em uma quarta-feira, e ja' viveu %ld dia(s) ate' hoje.\n", TOTAL);
if(SEMANA%(long)7==6)
printf("Parabens: voce nasceu em uma quinta-feira, e ja' viveu %ld dia(s) ate' hoje.\n", TOTAL);

VAI_NASC=1; /*para pedir a data de nascimento de novo*/
} /* fim do "while principal" */
} /* fim main */