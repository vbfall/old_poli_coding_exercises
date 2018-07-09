/***************************************************************************
 ***                                                                     ***
 ***   Vitor Bellissimo Falleiros          Numero USP: 2962011           ***
 ***   Exercicio-Programa 01 / MAP-121                                            ***
 ***   Professor: Alexandre                Turma: Mecƒnica - T98         ***
 ***   Computador: Pentium, 100 MHz                                      ***
 ***   Compilador: Turbo C++                                             ***
 ***                                                                     ***
 ***************************************************************************/


#include<stdio.h>
#include<math.h>


float VAR(float novo[], float velho[]);

float Gauss(float A[3][3], float x[], float b[]);

float Newton(float l1,float l2,float x,float y,float z,float ang[]);


void main ()
{
 float l1, l2, x, y, z, ang[3]; /* ang ‚ a matriz coluna que cont‚m os valores
											  dos angulos a1, a2 e b2, respectivamente*/
 float det;
 int n;
 char resp;

 do
 {
  printf("\nEntre os comprimentos de cada parte do bra‡o (em metros):\n"
			"L1= ");
  scanf("%f",&l1);
  printf("L2= ");
  scanf("%f",&l2);

  printf("\nDigite as coordenadas da extremidade livre do bra‡o:\n"
			"X= ");
  scanf("%f",&x);
  printf("Y= ");
  scanf("%f",&y);
  printf("Z= ");
  scanf("%f",&z);

  printf("\nDigite um chute inicial para a solu‡ao do sistema:\n"
			"a1= ");
  scanf("%f",&ang[0]);
  printf("a2= ");
  scanf("%f",&ang[1]);
  printf("b2= ");
  scanf("%f",&ang[2]);

  det=Newton(l1,l2,x,y,z,ang);

  if(det!=0.0)
  {
	for(n=0;n<3;n++)
	 if(ang[n]<0.0)
		ang[n]=ang[n]+6.28318530717958647*floor(fabs(ang[n]/6.28318530717958647));
	  else ang[n]=ang[n]-6.28318530717958547*floor(ang[n]/6.28318530717958647);
	/*para colocar o angulo na primeira volta da circunferˆncia trigonom‚trica*/

	printf("\nOs ƒngulos para essas coordenadas sao:\n"
			 "a1= %f\n"
			 "a2= %f\n"
			 "b2= %f\n",ang[0],ang[1],ang[2]);
  }/* fim if */

  printf("\nDeseja executar o programa mais uma vez? (s/n)\n");
  scanf("%c",&resp);
  scanf("%c",&resp); /* se nao pedir para ler duas vezes, ele pega o "enter"
								dado acima */

 }while(resp=='s' || resp=='s');

}/* fim main */



float VAR(float novo[], float velho[])
{
 int n;
 float v, vmax=0.0;

 for(n=0;n<3;n++)
 {
  if(novo[n]!=0.0) v=fabs((velho[n]-novo[n])/novo[n]);
	else
	{
	 if(velho[n]==0.0) v=0;
	  else v=1.0;
	}

  if(v>vmax) vmax=v;

 }/* fim for */

 return(vmax);
}/* fim VAR */


float Gauss(float A[3][3], float x[], float b[])
{
 int pivo, coluna, n;
 float aux, det;


 for(coluna=0;coluna<2;coluna++)/* escalonamento */
 {
  pivo=coluna;
  for(n=pivo+1;n<3;n++) /* calcula o piv“ */
	if(fabs(A[n][coluna])>fabs(A[pivo][coluna])) pivo=n;

  if(pivo>coluna) /* troca as linhas, se necess rio */
  {
	for(n=0;n<3;n++)
	{
	 aux=A[coluna][n];
	 A[coluna][n]=A[pivo][n];
	 A[pivo][n]=aux;
	}/* fim for */

	aux=b[coluna];
	b[coluna]=b[pivo];
	b[pivo]=aux;
  }/* fim if */

  for(n=coluna+1;n<3;n++)
  {
	A[n][coluna]=A[n][coluna]/A[coluna][coluna];
	A[n][coluna+1]=A[n][coluna+1]-A[coluna][coluna+1]*A[n][coluna];
	if(coluna==0)
	 A[n][coluna+2]=A[n][coluna+2]-A[coluna][coluna+2]*A[n][coluna];

	b[n]=b[n]-b[coluna]*A[n][coluna];
  }/* fim for interno */
 }/* fim for escalonamento */

 det=A[0][0]*A[1][1]*A[2][2];/* o verdadeiro sinal do det nao importa */

 if(det==0.0)
  printf("Os dados entrados resultam num sistema indeterminado ou imposs¡vel.\n"
			"Verifique as coordenadas e, se nao houver erros, troque os chutes"
			" iniciais.\n");

 if(det!=0.0)
 {
  x[2]=b[2]/A[2][2];
  x[1]=(b[1]-A[1][2]*x[2])/A[1][1];
  x[0]=(b[0]-A[0][1]*x[1]-A[0][2]*x[2])/A[0][0];
 }

 return(det);

}/* fim Gauss */



float Newton(float l1,float l2,float x,float y,float z,float ang[])
{
 float A[3][3], angnovo[3], b[3]; /* x e b sao matrizes coluna, b=Ak*xk-f(xk) */
 float v, det;
 int n;

 /*f1=x-l2*cos(a2)*cos(b2)
	f2=y-l1*cos(a1)-l2*cos(a2)*sin(b2)
	f3=z-l1*sin(a1)-l2*sin(a2) */

 do
 {
  A[0][0]=0;
  A[0][1]=l2*cos(ang[2])*sin(ang[1]);
  A[0][2]=l2*cos(ang[1])*sin(ang[2]);

  A[1][0]=l1*cos(ang[0]);
  A[1][1]=l2*sin(ang[2])*sin(ang[1]);
  A[1][2]=-l2*cos(ang[1])*cos(ang[2]);

  A[2][0]=-l1*cos(ang[0]);
  A[2][1]=-l2*cos(ang[1]);
  A[2][2]=0;

  b[0]=A[0][0]*ang[0]+A[0][1]*ang[1]+A[0][2]*ang[2]-x+l2*cos(ang[1])*cos(ang[2]);
  b[1]=A[1][0]*ang[0]+A[1][1]*ang[1]+A[1][2]*ang[2]-y+l1*cos(ang[0])+l2*cos(ang[1])*sin(ang[2]);
  b[2]=A[2][0]*ang[0]+A[2][1]*ang[1]+A[2][2]*ang[2]-z+l1*sin(ang[0])+l2*sin(ang[1]);

  det=Gauss(A,angnovo,b);

  if (det!=0.0)
  {
	v=VAR(angnovo,ang);
	for(n=0;n<3;n++)
	 ang[n]=angnovo[n];
  }

 }while(v>0.001 && det!=0.0);

 return(det);

}/* fim Newton */

