/***************************************************************************
 ***                                                                     ***
 ***   Vitor Bellissimo Falleiros          Numero USP: 2962011           ***
 ***   Exercicio-Programa 02 / MAP-121                                   ***
 ***   Professor: Alexandre Roma           Turma: Mecƒnica - T98         ***
 ***   Computador: Pentium, 100 MHz                                      ***
 ***   Compilador: Turbo C++                                             ***
 ***                                                                     ***
 ***************************************************************************/


#include<stdio.h>
#include<math.h>


void Gauss(float A[10][10], float x[], float b[]);
	  /*resolve sistemas lineares pelo m‚todo de Gauss, com condesa‡ao
		  pivotal */

float G(int indice, float x, float y);
	 /* fun‡oes aproximadoras */



void main()
{
 int larg, alt, div, figura[20][600], branco, n, k, l, c, i;
 float normal[10][10], coef[10], normresp[10], fig[100][10];
 char resp, arquivo[50];
 FILE *gravar; FILE *ler;


 do
 {
  printf("\n\nO que vocˆ deseja?\n"
			"(a) compactar uma imagem PGM;\n"
			"(b) descompactar uma imagem.\n\n"
			"Digite sua resposta (a/b): ");
  scanf("%c",&resp);

 }while(resp!='A' && resp!='a' && resp!='B' && resp!='b');

 if(resp=='A' || resp=='a')
 {
  do
  {
	printf("\nDigite o nome do arquivo que cont‚m a figura: ");
	scanf("%s",arquivo);

	ler=fopen(arquivo,"r");

	if(ler==NULL)
	{
	 printf("Arquivo %s nao encontrado\n",arquivo);
	 n=0;
	}/* fim if*/
	 else
	 {
	  fscanf(ler,"%s",&arquivo);
	  fscanf(ler,"%d",&larg);
	  fscanf(ler,"%d",&alt);
	  fscanf(ler,"%d",&branco);
	  n=1;
	 }/*fim else*/
  }while(n==0);

  do
  {
	printf
	 ("\nVocˆ deseja dividir o arquivo em matrizes de que tamanho? (1-20) ");
	scanf("%d",&div);
  }while(div<1 || div>20);

  do
  {
	printf("\nCom que nome vocˆ deseja gravar o arquivo? ");
	scanf("%s",arquivo);

	gravar=NULL;
	gravar=fopen(arquivo,"w");
	if (gravar==NULL)
	 {
	  printf("\n\n\n\nERRO: arquivo nao pode ser gravado!\n"
				"Verifique o nome do arquivo e tente de novo.\n");
	  n=0;
	 }/* fim if */
	  else
	  {
		n=1;
		fprintf(gravar,"%d\n",div);
		fprintf(gravar,"%d\n",larg);
		fprintf(gravar," %d\n",alt);
		fprintf(gravar,"%d\n",branco);
	  }/*fim else*/
  }while(n==0);

  for(l=0;l<10;l++)
	for(c=0;c<10;c++)
	 normal[l][c]=0;

  for(l=0;l<10;l++)
	for(c=0;c<10;c++)
	 for(i=0;i<div;i++)
	  for(k=0;k<div;k++)
  normal[l][c]=normal[l][c]+G(l,i/(div-1),k/(div-1))*G(c,i/(div-1),k/(div-1));
	 /*monta sist normal */

  for(n=0;n<=(alt/div);n++)
  {
	for(l=0;l<div;l++)
	 for(c=0;c<larg;c++)
	  fscanf(ler,"%d",&figura[l][c]);

	for(k=0;k<=(larg/div);k++)
	{
	 for(l=0;l<10;l++)
	 {
	  normresp[l]=0;

	  for(i=0;i<div;i++)
		for(c=0;c<div;c++)
		 normresp[l]=normresp[l]+G(l,i/(div-1),c/(div-1))*figura[i][k*div+c];
	  }/* fim for (l) */

	 Gauss(normal,coef,normresp);

	 fprintf(gravar,"\n");
	 for(l=0;l<10;l++)
	  fprintf(gravar,"%f ",coef[l]);
	 /*anexa resultados ao arquivo */

	}/*fim for interno (k)*/
  }/*fim for externo (n)*/
  fclose(ler);
  fclose(gravar);

  printf("Figura compactada!! Obrigado pela preferˆncia!!\n\n");
 }/*fim if compactar*/


 if(resp=='B' || resp=='b')
 {
  do
  {
	printf("\nDigite o nome do arquivo que cont‚m a figura compactada: ");
	scanf("%s",arquivo);

	ler=fopen(arquivo,"r");
	if(ler==NULL)
	{
	 printf("Arquivo %s nao encontrado\n",arquivo);
	 n=0;
	}
	 else
	 {
	  fscanf(ler,"%d",&div);
	  fscanf(ler,"%d",&larg);
	  fscanf(ler,"%d",&alt);
	  fscanf(ler,"%d",&branco);
	  n=1;
	 }
  }while(n==0);


  do
  {
	printf("\nCom que nome vocˆ deseja gravar o arquivo? ");
	scanf("%s",arquivo);

	gravar=NULL;

	gravar=fopen(arquivo,"w");
	if(gravar==NULL)
	{
	 printf("\n\n\n\nERRO: arquivo nao pode ser gravado!\n"
			  "Verifique o nome do arquivo e tente de novo.\n");
	 n=0;
	}
	 else
	 {
	  fprintf(gravar,"P2\n");
	  fprintf(gravar,"%d ",larg);
	  fprintf(gravar,"%d\n",alt);
	  fprintf(gravar,"%d",branco);
	  n=1;
	 }
  }while(n==0);

  for(n=0;n<=(alt/div);n++)
  {
	for(l=0;l<=(larg/div);l++)
	 for(c=0;c<10;c++)
	  fscanf(ler,"%f",&fig[l][c]);

	for(l=0;l<div;l++)
	{
	 for(c=0;c<larg;c++)
	  figura[l][c]=0;

	 for(c=0;c<(larg-(larg%div));c++)
	 {
	  for(k=0;k<10;k++)
	figura[l][c]=figura[l][c]
			 +floor((fig[floor(c/div)][k])*(G(k,(l/(div-1)),((c%div)/(div-1)))));

	  if(figura[l][c]>branco) figura[l][c]=branco;
	  if(figura[l][c]<0) figura[l][c]=0;
	 }/*fim for-montagem interno (c)*/

	 fprintf(gravar,"\n");
	 for(c=0;c<larg;c++)
	  fprintf(gravar,"%d ",figura[l][c]);
	}/*fim for-montagem externo (l)*/
  }/* fim for externo (n) */

  for(n=0;n<(alt%div);n++)
  {
	fprintf(gravar,"\n");
	for(k=0;k<larg;k++)
	 fprintf(gravar,"0");
  }/*fim for-completa (n)*/

  fclose(ler);
  fclose(gravar);

  printf("Figura descompactada!! Obrigado pela preferˆncia!!\n\n");
 }/*fim if descompactar*/


}/*fim main*/



void Gauss(float A[10][10], float x[], float b[])
{
 int pivo, coluna, n;
 float aux, det;


 for(coluna=0;coluna<=9;coluna++)/* escalonamento */
 {
  pivo=coluna;
  for(n=pivo+1;n<10;n++) /* calcula o piv“ */
	if(fabs(A[n][coluna])>fabs(A[pivo][coluna])) pivo=n;

  if(pivo>coluna) /* troca as linhas, se necess rio */
  {
	for(n=0;n<10;n++)
	{
	 aux=A[coluna][n];
	 A[coluna][n]=A[pivo][n];
	 A[pivo][n]=aux;
	}/* fim for */

	aux=b[coluna];
	b[coluna]=b[pivo];
	b[pivo]=aux;
  }/* fim if-troca-de-linhas */

  for(n=coluna+1;n<10;n++)
  {
	A[n][coluna]=A[n][coluna]/A[coluna][coluna];

	for(aux=1;aux<(9-coluna);aux++)
	 A[n][coluna+aux]=A[n][coluna+aux]-A[coluna][coluna+aux]*A[n][coluna];

	b[n]=b[n]-b[coluna]*A[n][coluna];
  }/* fim for interno */
 }/* fim for escalonamento */


 for(n=9;n>=0;n--)
 {
  x[n]=b[n];
  for(aux=9;aux>n;aux--)
	x[n]=x[n]-A[n][aux]*x[aux];
  x[n]=x[n]/A[n][n];
 }/*fim for-calcula-ra¡zes*/

}/* fim Gauss */




float G(int indice, float x, float y)
{
 if(indice==0)
  return(1.0);
 if(indice==1)
  return(x);
 if(indice==2)
  return(y);
 if(indice==3)
  return(x*x);
 if(indice==4)
  return(x*y);
 if(indice==5)
  return(y*y);
 if(indice==6)
  return(x*x*x);
 if(indice==7)
  return(x*x*y);
 if(indice==8)
  return(x*y*y);
 if(indice==9)
  return(y*y*y);
}/* fim G */