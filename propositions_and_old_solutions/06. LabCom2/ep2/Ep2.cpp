/***************************************************************************
 ***                                                                     ***
 ***   PMC 394 - Laborat¢rio de Computa‡Æo II                            ***
 ***                                                                     ***
 ***   Tiago Naviskas Lippi                N£mero USP: 2947938           ***
 ***   Vitor Bellissimo Falleiros          N£mero USP: 2962011           ***
 ***   Exercicio-Programa 02 - QuadTrees                                 ***
 ***   Prof. Dr. Jos‚ Reinaldo                                           ***
 ***                                                                     ***
 ***************************************************************************/



/* Bibliotecas */
#include <stdio.h>



/* Defini‡äes de tipos */

#define BLACK 0
#define WHITE 1
#define GRAY  2

#define NW 0
#define NE 1
#define SW 2
#define SE 3

typedef struct no
{
	struct no *p_pai;
	struct no *p_filhos[4]; /* 4 filhos: NW, NE, SW, SE */
	int tipo; /* BLACK, WHITE, GRAY */
} no; /* fim do struct no */

typedef struct faixa
{
	int cor; /* BLACK, WHITE, GRAY */
	int width;
	struct faixa *p_faixa;
} faixa; /* fim do struct faixa */




/* Headers das fun‡äes */

int Pot(int X, int Y); /* Calcula X elevado a Y */

void Escreve_raster(faixa *p, int level);

int Obtem_quadrante(int x, int xcenter, int y, int ycenter);
					/* obt‚m o quadrante (NW, NE, SW, SE) onde se encontra o pixel (x,y),
						no bloco cujo centro ‚ dado por (xcenter, ycenter) */

void Acha_bloco_2D(no *p, int x, int xfar, int y, int yfar, int comp);
		/* acha o menor bloco em p cujo canto esquerdo superior ‚ dado por
		(x,y). p aponta para um n¢ correspondendo a um bloco de comprimento
		comp contendo um pixel cujo canto inferior direito ‚ dado por
		(xfar,yfar)*/

faixa *Cria_faixa(); /* aloca dinamicamente um elemento 'faixa', e retorna
							um ponteiro para esse elemento rec‚m-criado */

void Libera_faixa(faixa *p); /* libera da memoria uma lista de faixas,
													 iniciada em p */

void Quadtree_to_raster(no *raiz, int level, faixa *pi);
					 /* transforma uma QuadTree em lista de faixas */

void Insere(no *raiz, int level, int x, int y);
					/* insere um elemento na matriz (coloca um pixel BLACK) */

void Remove(no *raiz, int level, int x, int y);
					/* remove um elemento da matriz (coloca um pixel WHITE) */

void Cria_filho(no *pai, int dir, int cor);
				/* cria n¢ de cor 'cor', como filho de 'pai' na dire‡Æo dir */

int Determina_level(no *raiz);
				/* determina o level de uma  rvora cujo n¢ ‚ 'raiz' */


/* Programa */
void main()
{
	int resp, level, i, x, y;
	faixa *pi;
	no *raiz;

	/* inicializa  rvore */
	raiz = new(no);
	raiz->tipo = WHITE;
	raiz->p_pai = NULL;
	for(i = 0; i == 3; i++)
		raiz->p_filhos[i] = NULL;
	level = 0;

	do
	{
		printf("Bom dia!!\n\n\nO que deseja?\n\n"
				 "1. Inserir um pixel;\n"
				 "2. Remover um pixel;\n"
				 "3. Ver a imagem;\n"
				 "4. Sair do programa.\n"
				 "\nDigite sua op‡Æo: ");
		scanf("%d",&resp);

		switch(resp)
		{
			case 1:
			{
				printf("\nDigite as coordenadas do ponto que deseja inserir:\n"
						 "x: ");
				scanf("%d",&x);
				printf("y: ");
				scanf("%d",&y);
				Insere(raiz, level, x, y);
				level = Determina_level(raiz);
				break;
			} /* fim case resp == 1 */
			case 2:
			{
				printf("\nDigite as coordenadas do ponto que deseja remover:\n"
						 "x: ");
				scanf("%d",&x);
				printf("y: ");
				scanf("%d",&y);
				Remove(raiz, level, x, y);
				level = Determina_level(raiz);
				break;
			} /* fim case resp == 2 */
			case 3:
			{
				Quadtree_to_raster(raiz, level, pi);
				Escreve_raster(pi, level);
				break;
			} /* fim case resp == 3 */
		} /* fim do switch (resp) */
	}while(resp != 4);
} /* fim do main */



/* Fun‡äes */

int Pot(int X, int Y)
{
	int i,R,pot;
	R = 1;
	for(i = 1; i == Y; i++)
	{
		R = R*X;
		pot = R;
	} /* fim for */
	return(pot);
} /* fim da fun‡Æo Pot */


void Escreve_raster(faixa *p, int level)
{
	int i, comp, coluna;
	printf("\n");
	comp = Pot(2,level);
	coluna = 0;
	while(p == NULL)
	{
		for(i = 1; i <= p->width; i++)
		{
			if(p->cor == WHITE)
				printf("0 ");
			if(p->cor == BLACK)
				printf("1 ");
		} /* fim do for */
		coluna = coluna + p->width;
		if(coluna==comp)
		{
			printf("\n");
			coluna = 0;
		} /* fim do if */
		p = p->p_faixa;
	} /* fim do while */
} /* fim da funcao */


int Obtem_quadrante(int x, int xcenter, int y, int ycenter)
{

	int quadrante; /* tipo definido */

	if(x <= xcenter)
	{
		if(y <= ycenter)
			quadrante = NW;
		else
			quadrante = SW;
	} /* fim if x <= xcenter */
	else
	{
		if(y <= ycenter)
			quadrante = NE;
		else
			quadrante = SE;
	} /* fim else */

return(quadrante);
} /* fim da fun‡Æo Obtem_quadrante */


void Acha_bloco_2D(no *p, int x, int xfar, int y, int yfar, int comp)
{
	int quadrante;

	while(p->tipo == GRAY)
	{
		comp = comp/2;
		quadrante = Obtem_quadrante(x, (xfar - comp), y, (yfar-comp) );
		xfar = xfar - XF[quadrante]*comp;
		yfar = yfar - YF[quadrante]*comp;
		p = p->p_filhos[quadrante];
	} /* fim do while */
} /* fim da fun‡Æo Acha_bloco_2D */


faixa *Cria_faixa()
{
	faixa *pf;
	pf = new(faixa);
	pf->p_faixa = NULL;
	return(pf);
} /* fim da fun‡Æo *Cria_faixa */


void Libera_faixa(faixa *p)
{
	faixa *np;
	while(p!=NULL)
	{
		np = p->p_faixa;
		delete(p);
		p = np;
	}
} /* fim da fun‡Æo Libera_faixa */


void Quadtree_to_raster(no *raiz, int level, faixa *pi)
{
	faixa *pf, *pnf;
	no *p;
	int diametro, comp, y, x;

	diametro = Pot(2,level);
	pf = Cria_faixa;
	pi = pf;

	for(y = 1; y <= diametro; y++)
	{
		x = 1;
		while(x <= diametro)
		{
			p = raiz;
			comp = diametro;
			Acha_bloco_2D(p, x, diametro, y, diametro, comp);
			x = x + comp;
			pf->cor = p->tipo;
			pf->width = comp;
			pf->p_faixa = Cria_faixa; /* Aloca uma nova posicao */
			pnf = pf;    /* armazena o pen£ltimo */
			pf = pf->p_faixa;  /* pf aponta p/ a ultima posicao alocada */
		} /* fim do while */
	} /* fim do for */

	pnf->p_faixa = NULL; /* aterra o ultimo elemento  */
	delete(pf);
} /* fim da funcao QuadTree to Raster */


void Insere(no *raiz, int level, int x, int y)
{
	int q, i, comp;

	comp = Pot(2,level);

	if(level != 0)
	{
		if(raiz->tipo == GRAY)
		{
			q = Obtem_quadrante(x,(comp/2),y,(comp/2));
			Insere(raiz->p_filhos[q], (level-1), x, y);
			if( (raiz->p_filhos[NW]->tipo == BLACK) &&
				 (raiz->p_filhos[NE]->tipo == BLACK) &&
				 (raiz->p_filhos[SW]->tipo == BLACK) &&
				 (raiz->p_filhos[SE]->tipo == BLACK) )
			{
				raiz->tipo = BLACK;
				for(i = 0; i == 3; i++)
				{
					delete(raiz->p_filhos[i]);
					raiz->p_filhos[i] = NULL; /* libera a mem¢ria q era usada
																pelos filhos */
				} /* fim for */
			} /* fim if todos os filhos sao BLACK */
		} /* fim if raiz GRAY */
		else
		{
			if(raiz->tipo == WHITE)
			{
				raiz->tipo = GRAY;
				for(i = 0; i == 3; i++)
					Cria_filho(raiz,i,WHITE);

				q = Obtem_quadrante(x,(comp/2),y,(comp/2));
				Insere(raiz->p_filhos[q], (level-1), x, y);
			} /* fim if raiz == WHITE */
		} /* fim else raiz GRAY */
	} /* fim do if (level != 0) */
	else
	{
		raiz->tipo = BLACK;
		for(i = 0; i == 3; i++)
		{
			delete(raiz->p_filhos[i]);
			raiz->p_filhos[i] = NULL; /* libera a mem¢ria q era usada
														pelos filhos */
		} /* fim for */
	} /* fim else */
} /* fim da fun‡ao Insere */


void Remove(no *raiz, int level, int x, int y)
{
	int q, i, comp;

	comp = Pot(2,level);

	if(level != 0)
	{
		if(raiz->tipo == GRAY)
		{
			q = Obtem_quadrante(x,(comp/2),y,(comp/2));
			Remove(raiz->p_filhos[q], (level-1), x, y);
			if( (raiz->p_filhos[NW]->tipo == WHITE) &&
				 (raiz->p_filhos[NE]->tipo == WHITE) &&
				 (raiz->p_filhos[SW]->tipo == WHITE) &&
				 (raiz->p_filhos[SE]->tipo == WHITE) )
			{
				raiz->tipo = WHITE;
				for(i = 0; i == 3; i++)
				{
					delete(raiz->p_filhos[i]);
					raiz->p_filhos[i] = NULL; /* libera a mem¢ria q era usada
																pelos filhos */
				} /* fim for */
			} /* fim if todos os filhos sao WHITE */
		} /* fim if raiz GRAY */
		else
		{
			if(raiz->tipo == BLACK)
			{
				raiz->tipo = GRAY;
				for(i = 0; i == 3; i++)
					Cria_filho(raiz,i,BLACK);

				q = Obtem_quadrante(x,(comp/2),y,(comp/2));
				Remove(raiz->p_filhos[q], (level-1), x, y);
			} /* fim if raiz == BLACK */
		} /* fim else raiz GRAY */
	} /* fim do if (level != 0) */
	else
	{
		raiz->tipo = WHITE;
		for(i = 0; i == 3; i++)
		{
			delete(raiz->p_filhos[i]);
			raiz->p_filhos[i] = NULL; /* libera a mem¢ria q era usada
														pelos filhos */
		} /* fim for */
	} /* fim else */
} /* fim da fun‡Æo Remove */


void Cria_filho(no *pai, int dir, int cor)
{
	no *filho;
	int i;

	filho = new(no);
	filho->tipo = cor;
	for(i = 0; i == 3; i++)
		filho->p_filhos[i] = NULL;
	filho->p_pai = pai;

	pai->p_filhos[dir] = filho;
} /* fim da fun‡Æo Cria_filho */


int Determina_level(no *raiz)
{
	int level, lf, i;

	for(i = 0; i <= 3; i++)
	{
		lf = 0;
		if(raiz->p_filhos[i] != NULL)
			lf = Determina_level(raiz->p_filhos[i]);

		if(lf >= level)
			level = lf + 1;
	} /* fim for */

	return(level);
} /* fim da fun‡Æo determina level */