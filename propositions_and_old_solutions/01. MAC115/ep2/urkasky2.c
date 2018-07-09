/***************************************************************************
 ***                                                                     ***
 ***  Vitor Bellissimo Falleiros            N£mero USP:2962011           ***
 ***  Exerc¡cio-Programa 02                                              ***
 ***  Professor: Routo Terada                                            ***
 ***  Computador: Pentium 100Mhz                                         ***
 ***  Compilador: Turbo c++                                              ***
 ***                                                                     ***
 ***************************************************************************/

/*  Objetivos: simular um ca‡a-n¡queis com trˆs rolos, cada um com cinco
  figuras. O resultado deve ser aleat¢rio. */

#include <stdio.h>
#include <math.h>

float seno(float y); /*header da fun‡ao seno*/

main() {
int premio;
char resposta;
float x,y; /* para gerar n£meros aleat¢rios*/
float conta; /*contador para v rias passagens*/
int r1, r2, r3; /* Um para cada rolo*/
int modo;/*modo de jogo*/
float fig;/* para sorteio de figuras*/
float aposta; /* quanto o jogador vai apostar */
int N,n,p1,p2,p3,p4; /*para o modo de aferi‡ao*/
int z; /*parƒmetro para que o n£mero seja mesmo aleatorio*/

printf("		 BEM-VINDO AO CA€A-NIQUEIS DA POLI!!!\n"
		 "\n"
		 "  H  cinco poss¡veis 'figuras' em cada rolo da m quina: Minerva, o\n"
		 "corvo, o rato, o bandejao e BAR. Se vocˆ tirar duas figuras iguais\n"
		 "e outra qualquer, leva a mesma quantia da sua aposta. Se conseguir\n"
		 "trˆs figuras iguais, leva o dobro, e se os trˆs rolos pararem em\n"
		 "Minerva, vocˆ leva quatro vezes o valor da aposta!!!\n"
		 "\n"
		 "DIVIRTA-SE, E BOA SORTE!!!\n");

conta=0;

do /*do-while principal*/
 {do
	{printf("\n"
	 "Escolha o modo de jogo:\n"
	 "1. apostar apenas em Minerva: qualquer outro prˆmio ser  desconsiderado;\n"
	 "2. apostar em trˆs figuras iguais: prˆmio correspondente a duas \n"
	 "   figuras iguais ser  desconsiderado;\n"
	 "3. apostar em qualquer prˆmio;\n"
	 "4. modo de aferi‡ao.\n"
	 "\n"
	 "Modo escolhido: ");

	 scanf("%d",&modo);
	}while (modo<1 || modo>4);

  if(conta==0) /*para pedir um numero apenas na primeira vez*/
	{printf("\n"
			  "Digite o seu ALGARISMO da sorte: ");
	 scanf("%d",&z);
	 y=0.2962011*(float)z/10.0;
	}

  aposta=0.0;
  while(modo!=4 && aposta==0.0)
	 {printf("\n"
				"Digite quanto quer apostar (em reais):\n"
				"R$ ");
	  scanf("%f",&aposta);}

  if(modo==4)
	{printf("\n"
			  "Digite um n£mero inteiro: ");
	 scanf("%d",&n);
	}
  else n=1;
  N=n; p1=0; p2=0; p3=0; p4=0;

  while (n>0)
  {conta=1.0;
	while(conta<=3.0) /*para gerar as figuras*/
	 {x=(9821.0*fabs(seno(y))+0.211327);
	  y=x-floor(x);
	  fig=(y*5.0)+1.0;/*n£mero REAL entre 1 e 6*/

	  if(conta==1.0) r1=fig;
	  if(conta==2.0) r2=fig;
	  if(conta==3.0) r3=fig;

	  conta=conta+1.0;/*passa para o pr¢ximo rolo*/
	 }/* fim da gera‡ao das figuras*/

	if(r1==1 && r2==1 && r3==1) {premio=1;p1++;}
	 else
	  {if(r1==r2 && r1==r3 && modo!=1) {premio=2;p2++;}
		 else
		  {if((r1==r2 || r1==r3 || r2==r3) && modo!=1 && modo!=2)
				{premio=3;p3++;}
			 else {premio=4;p4++;}
		  }
	  }
	/*acabou de determinar os premios*/

	n--;
  }/*fim while n>0*/

  if(modo!=4)
  {printf("\n"
			 "Rolo 1: ");
	if(r1==1) printf("Minerva.\n");
	if(r1==2) printf("o Corvo.\n");
	if(r1==3) printf("o Rato.\n");
	if(r1==4) printf("o Bandejao.\n");
	if(r1==5) printf("BAR.\n");
	/*para imprimir o resultado do primeiro rolo*/

	printf("Rolo 2: ");
	if(r2==1) printf("Minerva.\n");
	if(r2==2) printf("o Corvo.\n");
	if(r2==3) printf("o Rato.\n");
	if(r2==4) printf("o Bandejao.\n");
	if(r2==5) printf("BAR.\n");
	/*para imprimir o resultado do segundo rolo*/

	printf("Rolo 3: ");
	if(r3==1) printf("Minerva.\n");
	if(r3==2) printf("o Corvo.\n");
	if(r3==3) printf("o Rato.\n");
	if(r3==4) printf("o Bandejao.\n");
	if(r3==5) printf("BAR.\n");
	/*para imprimir o resultado do terceiro rolo*/

	if(premio==1)
	  printf("Parab‚ns!!! Vocˆ ganhou R$ %.2f!!!\n",(4.0*aposta));
	 else
	  {if(premio==2)
		  printf("Vocˆ ganhou R$ %.2f!!!\n",(2.0*aposta));
		 else
		  {if(premio==3)
			  printf("Vocˆ ganhou R$ %.2f.\n",aposta);
			 else
			  printf("Sinto muito, mas vocˆ ficou sem nada. Tente de novo!\n");
		  }
	  }
	 /*para o premio conseguido*/
  }

  if(modo==4) /*para imprimir os resultados do teste (modo 4) */
  {printf("\n"
			 "Prˆmio\n");
	printf("  1  ");
	for(conta=(float)p1*180.0/(float)N; conta>0.0; conta=conta-1.0)
	 {printf ("*");}

	printf("\n"
			 "  2  ");
	for(conta=(float)p2*180.0/(float)N; conta>0.0; conta=conta-1.0)
	 {printf ("*");}

	printf("\n"
			 "  3  ");
	for(conta=(float)p3*180.0/(float)N; conta>0.0; conta=conta-1.0)
	 {printf ("*");}

	printf("\n"
			 "  4  ");
	for(conta=(float)p4*180.0/(float)N; conta>0.0; conta=conta-1.0)
	 {printf ("*");}
	/*fim do histograma*/

	printf("\n"
			 "Esperado para 4X: %.4f.", (float)N/125.0);
	printf(" Obtido para 4X: %d.", p1);
	printf(" Diferen‡a: %.4f.", ((float)p1-(float)N/125.0));

	printf("\n"
			 "Esperado para 2X: %.4f.", (float)N*4.0/125.0);
	printf(" Obtido para 2X: %d.", p2);
	printf(" Diferen‡a: %.4f.", ((float)p2-(float)N*4.0/125.0));

	printf("\n"
			 "Esperado para X: %.4f.", (float)N*14.0/25.0);
	printf(" Obtido para X: %d.", p3);
	printf(" Diferen‡a: %.4f.", ((float)p3-(float)N*14.0/25.0));

	printf("\n"
			 "Esperado para NADA: %.4f.", (float)N*2.0/5.0);
	printf(" Obtido para NADA: %d.", p4);
	printf(" Diferen‡a: %.4f.", ((float)p4-(float)N*2.0/5.0));
  }/*acabou de imprimir os resultados do teste (modo 4) */

  printf("\n"
			"Deseja jogar novamente? (S/N)\n");
  resposta=getc(stdin);
  resposta=getc(stdin); /*duas vezes porque ele pega o "enter" da aposta*/
 }
 while((resposta!='n') && (resposta!='N')); /*fim do-while principal*/
}/*fim main*/

float seno(float y)
 {int k; float soma, membro, modulo;
  soma=y; k=2; membro=y;
  if (membro>0.0) modulo=membro;
	else modulo=-1.0*membro;
  while(modulo>=0.00000001)
	 {membro=-1.0*membro*y*y/((float)k*((float)k+1.0));
	  soma=soma+membro;
	  if(membro<0.0) modulo=-1.0*membro;
		else modulo=membro;
	  k=k+2;
	 }/*fim while*/
  return(soma);
 }/*fim seno*/