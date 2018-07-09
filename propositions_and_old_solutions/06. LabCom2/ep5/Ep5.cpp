/***************************************************************************
 ***                                                                     ***
 ***   PMC 394 - Laborat�rio de Computa��o II                            ***
 ***                                                                     ***
 ***   Tiago Naviskas Lippi                N�mero USP: 2947938           ***
 ***   Vitor Bellissimo Falleiros          N�mero USP: 2962011           ***
 ***   Exercicio-Programa 05 - Busca em grafos: M�todo PERT/CPM          ***
 ***   Prof. Dr. Jos� Reinaldo                                           ***
 ***                                                                     ***
 ***************************************************************************/



/* Bibliotecas */
#include<stdio.h>



/* Defini��es */

#define tam_max 20

enum tipo_de_operacao {cria_grafo, destroi_grafo, insere_aresta, destroi_aresta};

typedef struct pilha
{
	int nome; /* nome do v�rtice */
	struct pilha *anterior; /* aponta struct com nome do v�rtice anterior */
} pilha; /* fim da defini��o de pilha */

typedef struct vertice
{
	int nome;
	struct vertice *proximo; /* indica proximo vertice do grafo */
	struct aresta *p_aresta; /* indica primeira aresta que parte desse vertice */
} vertice; /* fim da defini��o de vertice */

typedef struct aresta
{
	int peso;
	struct vertice *destino;
	struct aresta *proxima;
} aresta; /* fim da defini��o de aresta */

typedef struct operacao
{
	tipo_de_operacao realizada;
	int p1, p2, p3;
	struct operacao *anterior;
} operacao; /* fim da defini��o de opera��o */



/* Headers das fun��es */

vertice *Cria_grafo_min(int n); /* cria um grafo de n vertices, sem arestas */

void Destroi_grafo_min(vertice *grafo); /* destr�i um grafo sem arestas */

vertice *Acha_vertice(vertice *grafo, int procurado); /* retorna um ponteiro para o
															 n� procurado */
void Acrescenta_aresta(vertice *grafo, int origem, int destino, int peso);
							/* cria uma aresta com as caracter�sticas passadas */
void Remove_aresta(vertice *grafo, int origem, int destino);
							/* remove a aresta entre os dois n�s passados */
void Salvar_grafo(vertice *grafo); /* salva o grafo num arquivo, na forma de matriz
								      de adjac�ncias  */
vertice *Recupera_grafo(void); /* l� um grafo de um arquivo */

int Verifica_aresta(vertice *grafo, int i, int j); /* retorna peso de uma aresta, ou zero
													  se ela n�o existe */
void Remover_grafo(vertice *grafo); /* libera a mem�ria ocupada por um grafo qualquer */

operacao *Desfazer(vertice *grafo, operacao *pilha); /* desfaz a �ltima opera��o */

operacao *Prepara_desfazer(operacao *pilha, int n1, int n2, int n3, tipo_de_operacao feita);
			/* altera a pilha de opera��es realizadas cada vez que uma opera��o � feita */
void Mostrar_grafo(vertice *grafo); /* mostra o grafo na tela para o usu�rio */

void PERT(vertice *grafo); /* calcula e, l, ee, le e criticalidades */

int Calc_ee(vertice *grafo, pilha *&topo, int ee[tam_max]); /* calcula o primeiro prazo de
	ocorr�ncia de cada evento (v�rtices), retorna tamanho do grafo, a ser usado em seguida */
void Calc_le(vertice *grafo, pilha *topo, int le[tam_max], int le_n, int n);
	/* calcula o �ltimo prazo de ocorr�ncia de cada evento (v�rtices). le_n � le[n] */
int Calc_e(vertice *grafo, int e[2*tam_max], int ee[tam_max]);
	/* calcula o primeiro prazo de in�cio de cada atividade */
void Calc_l(vertice *grafo, int l[2*tam_max], int le[tam_max]);
	/* calcula o �ltimo prazo de in�cio de cada atividade */
void Mostra_PERT(int ee[tam_max], int le[tam_max], int e[2*tam_max], int l[2*tam_max], int n, int m);
			/* mostra na tela os resultados obtidos com o PERT */
void CPM(vertice *grafo, int e[2*tam_max], int l[2*tam_max], int ee[tam_max]);
					/* encontra atividades cr�ticos */



/* Programa */

void main()
{
	vertice *grafo; /* aponta para o in�cio do grafo */
	operacao *pilha; /* aponta uma pilha de opera��es realizadas, para poder desfaz�-las */
	int resp;
	int n, i, j, p;

	pilha = NULL;
	grafo = NULL;

	printf("\n\nBom dia!\n\n");
	
	do
	{
		printf("\nO que deseja?\n"
			   "1. Criar um novo grafo;\n"
			   "2. Inserir uma aresta no grafo;\n"
				"3. Remover uma aresta no grafo;\n"
			   "4. Ler um grafo de um arquivo;\n"
			   "5. Gravar o grafo num arquivo;\n"
			   "6. Ver o grafo na tela;\n"
			   "7. Destruir um grafo sem aresta;\n"
			   "8. Desfazer o passo anterior;\n"
			   "9. Executar o PERT\n"
			   "10. Sair do programa.\n\n"
			   "Digite sua escolha: ");
		scanf("%d",&resp);

		switch(resp)
		{
			case 1:
				{
					printf("\nQual o tamanho do grafo que deseja criar?\n"
						   "n = ");
					scanf("%d",&n);
					grafo = Cria_grafo_min(n);
					pilha = Prepara_desfazer(pilha, n, 0, 0, cria_grafo);
					break;
				} /* fim do case resp == 1 */
			case 2:
				{
					printf("\nDigite os dados da aresta que deseja colocar:\n"
						   "Origem: ");
					scanf("%d",&i);
					printf("Destino: ");
					scanf("%d",&j);
					printf("Peso: ");
					scanf("%d",&p);

					Acrescenta_aresta(grafo,i,j,p);
					pilha = Prepara_desfazer(pilha, i, j, 0, insere_aresta);
					break;
				} /* fim do case resp == 2 */
			case 3:
				{
					printf("\nQue aresta deseja remover?\n"
						   "Origem: ");
					scanf("%d",&i);
					printf("Destino: ");
					scanf("%d",&j);

					p = Verifica_aresta(grafo, i, j);
					if( p != 0)
					{
						pilha = Prepara_desfazer(pilha, i, j, p, destroi_aresta);
						Remove_aresta(grafo,i,j);
					} /* fim do if aresta existe */
					break;
				} /* fim do case resp == 3 */
			case 4:
				{
					grafo = Recupera_grafo();
					break;
				} /* fim do case resp == 4 */
			case 5:
				{
					Salvar_grafo(grafo);
					break;
				} /* fim do case resp == 5 */
			case 6:
				{
					Mostrar_grafo(grafo);
					break;
				} /* fim do case resp == 6 */
			case 7:
				{
					if(grafo != NULL)
					{
						Prepara_desfazer(pilha, n, 0, 0, destroi_grafo);
						Destroi_grafo_min(grafo);
					} /* fim if */
					break;
				} /* fim do case resp == 7 */
			case 8:
				{
					if(pilha != NULL)
						pilha = Desfazer(grafo, pilha);
					else
						printf("\nN�o h� mais opera��es para desfazer!\n");
					break;
				} /* fim do case resp == 8 */
			case 9:
				{
					if(grafo != NULL)
						PERT(grafo);
					else
						printf("\n\n!!!Construa um grafo antes!!!\n\n");
				} /* fim do case resp == 9 */
		} /* fim do switch(resp) */
	} while(resp != 10);

	if(grafo != NULL)
		Remover_grafo(grafo);
} /* fim do 'main' */



/* Fun��es */

vertice *Cria_grafo_min(int n)
{
	vertice *grafo; /* indicar� o primeiro v�rtice do grafo a ser criado */
	vertice *no_atual;
	int i;

	grafo = new(vertice);
	no_atual = grafo;

	for(i = 1; i < n; i++)
	{
		no_atual->nome = i;
		no_atual->proximo = new(vertice);
		no_atual->p_aresta = NULL;
		no_atual = no_atual->proximo;
	}

	/* �ltimo vertice: */
	no_atual->nome = n;
	no_atual->proximo = NULL;
	no_atual->p_aresta = NULL;

	return(grafo);
} /* fim da fun��o Cria_grafo_min */


void Destroi_grafo_min(vertice *grafo)
{
	if(grafo->proximo != NULL)
		Destroi_grafo_min(grafo->proximo);

	delete(grafo);
} /* fim da fun��o Destroi_grafo_min */


vertice *Acha_vertice(vertice *grafo, int procurado)
{
	vertice *atual;
	atual = grafo;
	while(atual->nome != procurado)
		atual = atual->proximo;

	return(atual);
} /* fim da fun��o Acha_vertice */


void Acrescenta_aresta(vertice *grafo, int origem, int destino, int peso)
{
	vertice *no_atual;
	aresta *aresta_atual;

	no_atual = Acha_vertice(grafo,origem);

	if(no_atual->p_aresta == NULL)
	{
		no_atual->p_aresta = new(aresta);
		aresta_atual = no_atual->p_aresta;
	} /* fim if no_atual->aresta == NULL */
	else
	{
		aresta_atual = no_atual->p_aresta;
		while(aresta_atual->proxima != NULL)
			aresta_atual = aresta_atual->proxima;
		aresta_atual->proxima = new(aresta);
		aresta_atual = aresta_atual->proxima;
	} /* fim else */

	no_atual = Acha_vertice(grafo,destino);

	/* inicializa��o da nova aresta: */
	aresta_atual->peso = peso;
	aresta_atual->destino = no_atual;
	aresta_atual->proxima = NULL;
} /* fim da fun��o Acrescenta_aresta */


void Remove_aresta(vertice *grafo, int origem, int destino)
{
	vertice *no_atual;
	aresta *aresta_atual, *temp;

	no_atual = Acha_vertice(grafo,origem);

	aresta_atual = no_atual->p_aresta;
	if(aresta_atual->destino->nome == destino)
	{
		if(aresta_atual->proxima == NULL)
		{
			delete(aresta_atual);
			no_atual->p_aresta = NULL;
		} /* fim if menor */
		else
		{
			no_atual->p_aresta = aresta_atual->proxima;
			delete(aresta_atual);
		} /* fim else menor */
	} /* fim if maior */
	else
	{
		while(aresta_atual->proxima->destino->nome != destino)
			aresta_atual = aresta_atual->proxima;
		if(aresta_atual->proxima->proxima == NULL)
		{
			delete(aresta_atual->proxima);
			aresta_atual->proxima = NULL;
		} /* fim if menor */
		else
		{
			temp = aresta_atual->proxima->proxima;
			delete(aresta_atual->proxima);
			aresta_atual->proxima = temp;
		} /* fim else menor */
	} /* fim else maior */

} /* fim da fun��o Remove_aresta */


void Salvar_grafo(vertice *grafo)
{
	FILE *gravar;
	char arquivo[20];
	vertice *temp;
	int n, i, j, p; /* n guardar� a ordem do grafo, p guardar� pesos de arestas */

	printf("\n\nDigite o nome com que deseja gravar o arquivo: ");
	scanf("%s",&arquivo);
	gravar = fopen(arquivo,"w");
	if (gravar == NULL)
		printf("\n\n\n\nERRO: arquivo nao pode ser gravado!\n"
			   "Verifique o nome do arquivo e tente de novo.\n");
	else
	{
		n = 0;
		temp = grafo;
		while(temp != NULL)
		{
			n++;
			temp = temp->proximo;
		} /* fim do while(temp != NULL) */
		fprintf(gravar,"%d\n",n);

		for(i = 1; i <= n; i++)
		{
			for(j = 1; j <= n; j++)
			{
				p = Verifica_aresta(grafo,i,j);
				fprintf(gravar," %d ",p);
			} /* fim for j */
			fprintf(gravar,"\n");
		} /* fim for i */
	} /* fim do else */

	fclose(gravar);
} /* fim da fun��o Salvar_grafo */


vertice *Recupera_grafo(void)
{
	FILE *ler;
	vertice *grafo;
	char arquivo[20];
	int n, p, i, j; /* n guardar� a ordem do grafo, p guardar� pesos de arestas */

	printf("\n\nDigite o nome do arquivo que deseja abrir: ");
	scanf("%s",&arquivo);
	ler = fopen(arquivo,"r");
	if(ler == NULL)
		printf("\n\nArquivo nao encontrado!!\n\n");
	else /* arquivo encontrado */
	{
		fscanf(ler,"%d",&n);
		grafo = Cria_grafo_min(n);

		for(i = 1; i <= n; i++)
		{
			for(j = 1; j <= n; j++)
			{
				fscanf(ler,"%d",&p);
				if(p != 0)  /* se a aresta existe */
					Acrescenta_aresta(grafo,i,j,p);
			} /* fim for j */
		} /* fim for i */
	} /* fim else */

	fclose(ler);
	return(grafo);
} /* fim da fun��o Recupera_grafo */


int Verifica_aresta(vertice *grafo, int origem, int destino)
{
	vertice *temp;
	aresta *aresta_atual;

	temp = Acha_vertice(grafo, origem);

	if( (temp->p_aresta != NULL) && (temp->p_aresta->destino->nome == destino) )
		return(temp->p_aresta->peso);

	else
	{
		aresta_atual = temp->p_aresta;
		while( (aresta_atual != NULL) && (aresta_atual->destino->nome != destino) )
			aresta_atual = aresta_atual->proxima;
		if(aresta_atual == NULL)
			return(0);
		else
			return(aresta_atual->peso);
	} /* fim do else maior */
} /* fim da fun��o Verifica_aresta */


void Remover_grafo(vertice *grafo)
{
	int n, i, j;
	vertice *temp;
	temp = grafo;

	n = 0;
	while(temp != NULL)
	{
		n++;
		temp = temp->proximo;
	} /* fim while */

	for(i = 1; i <= n; i++)
		for(j = 1; j <= n; j++)
			if( Verifica_aresta(grafo, i, j) != 0 )
				Remove_aresta(grafo, i, j);

	Destroi_grafo_min(grafo);		
} /* fim da fun��o Remover_grafo */


operacao *Desfazer(vertice *grafo, operacao *pilha)
{
	operacao *temp;

	switch(pilha->realizada)
	{
		case cria_grafo:
			{
				Destroi_grafo_min(grafo);
				break;
			} /* fim case realizada == cria_grafo */
		case destroi_grafo:
			{
				grafo = Cria_grafo_min(pilha->p1);
				break;
			} /* fim case realizada == destroi_grafo */
		case insere_aresta:
			{
				Remove_aresta(grafo, pilha->p1, pilha->p2);
				break;
			} /* fim case realizada == insere_aresta */
		case destroi_aresta:
			{
				Acrescenta_aresta(grafo, pilha->p1, pilha->p2, pilha->p3);
				break;
			} /* fim case realizada == destroi_aresta */
	} /* fim do switch(pilha->realizada) */

	temp = pilha->anterior;
	return(temp);
} /* fim da fun��o desfazer */


operacao *Prepara_desfazer(operacao *pilha, int n1, int n2, int n3, tipo_de_operacao feita)
{
	operacao *temp;
	temp = new(operacao);

	temp->anterior = pilha;
	temp->p1 = n1;
	temp->p2 = n2;
	temp->p3 = n3;
	temp->realizada = feita;

	return(temp);
} /* fim da fun��o Prepara_desfazer */


void Mostrar_grafo(vertice *grafo)
{
	vertice *temp;
	int n, i, j, p; /* n guardar� a ordem do grafo, p guardar� pesos de arestas */
	char continua;

	n = 0;
	temp = grafo;
	while(temp != NULL)
	{
		n++;
		temp = temp->proximo;
	} /* fim while */

	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= n; j++)
		{
			p = Verifica_aresta(grafo,i,j);
			printf(" %d ",p);
		} /* fim for j */
		printf("\n");
	} /* fim for i */

	printf("\nPressione qualquer tecla para continuar.\n");
	scanf("%c",&continua); scanf("%c",&continua);
} /* fim da fun��o Mostrar_grafo */


void PERT(vertice *grafo)
{
	int ee[tam_max];
	int le[tam_max];
	int e[2*tam_max];
	int l[2*tam_max];
	int n, m;
	pilha *topo; /* guarda ordem topol�gica dos eventos (v�rtices) */

	topo = NULL;
	n = Calc_ee(grafo, topo, ee);
	Calc_le(grafo, topo, le, ee[(topo->nome - 1)], n);
	m = Calc_e(grafo, e, ee);
	Calc_l(grafo, l, le);

	Mostra_PERT(ee, le,  e, l, n, m);

	CPM(grafo, e, l, ee);

} /* fim da fun��o PERT */


int Calc_ee(vertice *grafo, pilha *&topo, int ee[tam_max])
{
	int n, i, adj, t;
	int count[tam_max];
	vertice *no_atual;
	aresta *a_atual;
	pilha *p, *temp; /* a pilha p cont�m os v�rtices sem predecessores, ou cujos
							predecessores j� foram avaliados */

	/* determinar tamanho do grafo */
	n = 0;
	no_atual = grafo;
	while(no_atual != NULL)
	{
		n++;
		no_atual = no_atual->proximo;
	} /* fim while */

	/* inicializar vetores ee e count */
	for(i = 0; i < n; i++)
	{
		count[i] = 0;
		ee[i] = 0;
	} /* fim for de inicializa��o de vetores */

	/* determinar quantidade de predecessores de cada v�rtice (count) */
	no_atual = grafo;
	while(no_atual != NULL) /* while maior */
	{
		a_atual = no_atual->p_aresta;
		while(a_atual != NULL) /* while menor */
		{
			adj = (a_atual->destino->nome - 1); /* (-1) pq vetor em C come�a com 0 */
			count[adj]++; /* aumenta count do v�rtice de destino */
			a_atual = a_atual->proxima;
		} /* fim while menor */
		no_atual = no_atual->proximo;
	} /* fim while maior */

	/* inicializar pilhas (supondo que s� existe um v�rtice de partida) */
	topo = NULL;
	p = new(pilha);
	p->anterior = NULL;
	i = 0;
	while(count[i] != 0)
		i++;
	p->nome = (i + 1);
	temp = p;

	/* c�lculo de ee */
	for(i = 1; i <= n; i++)
	{
		/* retira um v�rtice da pilha e coloca na de ordem topol�gica */
		no_atual = Acha_vertice(grafo, p->nome);
		temp = topo;
		topo = new(pilha);
		topo->nome = p->nome;
		topo->anterior = temp;
		p = p->anterior;

		a_atual = no_atual->p_aresta;
		while(a_atual != NULL)
		{
			adj = (a_atual->destino->nome - 1); /* (-1) pq vetor em C come�a com 0 */
			count[adj]--; /* diminui o count do v�rtice apontado */
			if(count[adj] == 0) /* atualiza pilha */
			{
				temp = new(pilha);
				temp->nome = adj + 1;
				temp->anterior = p;
				p = temp;
			} /* fim if atualiza pilha */

			t = ee[(no_atual->nome - 1)] + a_atual->peso;
			if(t > ee[adj])
				ee[adj] = t;

			a_atual = a_atual->proxima;
		} /* fim while */
	} /* fim for i */

	return(n);
} /* fim da fun��o Calc_ee */


void Calc_le(vertice *grafo, pilha *topo, int le[tam_max], int le_n, int n)
{
	int i, adj, t;
	vertice *no_atual;
	pilha *temp;
	aresta *a_atual;

	for(i = 0; i < n; i++)
		le[i] = le_n;

	temp = topo;

	while(temp != NULL) /* while maior */
	{
		/* pega na pilha o �ltimo v�rtice da ordem topol�gica */
		i = temp->nome;
		temp = temp->anterior;

		no_atual = Acha_vertice(grafo, i);
		a_atual = no_atual->p_aresta;

		while(a_atual != NULL) /* while menor */
		{
			adj = (a_atual->destino->nome - 1); /* (-1) pq vetor em C come�a com 0 */
			t = le[adj] - a_atual->peso;
			if(t < le[i - 1])
				le[i - 1] = t;
			a_atual = a_atual->proxima;
		} /* fim while menor */
	} /* fim while maior */

} /* fim da fun��o Calc_le */


int Calc_e(vertice *grafo, int e[2*tam_max], int ee[tam_max])
{
	int i, k;
	vertice *no_atual;
	aresta *a_atual;

	/* inicializar vari�veis */
	i = 0;
	no_atual = grafo;
 
	while(no_atual->proximo != NULL) /* while maior - n�o precisa fazer para o �ltimo v�rtice,
										pois ele n�o � o in�cio de nenhuma atividade */
	{
		k = (no_atual->nome - 1); /* (-1) pq vetor em C come�a com 0 */
		a_atual = no_atual->p_aresta;
 
		while(a_atual != NULL) /* while menor */
		{
			e[i] = ee[k];
			i++;
			a_atual = a_atual->proxima;
		} /* fim while menor */
		no_atual = no_atual->proximo;
	} /* fim while maior */

	return(i);
} /* fim da fun��o Calc_e */


void Calc_l(vertice *grafo, int l[2*tam_max], int le[tam_max])
{
	int i, k;
	vertice *no_atual;
	aresta *a_atual;

	/* inicializar vari�veis */
	i = 0;
	no_atual = grafo;

	while(no_atual->proximo != NULL) /* while maior - n�o precisa fazer para o �ltimo v�rtice,
										pois ele n�o � o in�cio de nenhuma atividade */
	{
		a_atual = no_atual->p_aresta;

		while(a_atual != NULL) /* while menor */
		{
			k = (a_atual->destino->nome - 1); /* (-1) pq vetor em C come�a com 0 */
			l[i] = le[k] - (a_atual->peso);
			i++;
			a_atual = a_atual->proxima;
		} /* fim while menor */
		no_atual = no_atual->proximo;
	} /* fim while maior */

} /* fim da fun��o Calc_l */


void Mostra_PERT(int ee[tam_max], int le[tam_max], int e[2*tam_max], int l[2*tam_max], int n, int m)
{
	int i;
	char continua;

	printf("Evento   ee   le\n\n");
	for(i = 0; i < n; i++)
		printf("  %d      %d    %d\n", (i + 1), ee[i], le[i]);
	printf("\nPressione qualquer tecla para continuar.\n");
	scanf("%c",&continua); scanf("%c",&continua);
	printf("\nAtividade   e      l   criticalidade\n\n");
	for(i = 0; i < m; i++)
		printf("    %d       %d      %d         %d\n", (i + 1), e[i], l[i], (l[i] - e[i]));
	printf("\nPressione qualquer tecla para continuar.\n");
	scanf("%c",&continua);
} /* fim da fun��o Mostra_PERT */


void CPM(vertice *grafo, int e[2*tam_max], int l[2*tam_max], int ee[tam_max])
{
	int i, k, marca; /* a vari�vel 'marca' serve para marcar bifurca��es */
	int crit[2*tam_max]; /* guardar� n�meros das atividades cr�ticas */
	vertice *no_atual;
	aresta *a_atual;
	pilha *bif, *temp; /* marca bifurca��es no caminho */

	for(i = 0; i < 2*tam_max; i++)
		crit[i] = 0;
	i = 0;
	k = 0;
	no_atual = grafo;
	bif = NULL;

	while(no_atual != NULL) /* while menor */
	{
		a_atual = no_atual->p_aresta;
		marca = 0;

		while(a_atual != NULL) /* while menor */
		{
			if( (l[i] - e[i]) == 0 ) /* se atividade � cr�tica */
			{
				crit[k] = i + 1;
				k++;
				if(marca != 0) /* se houver bifurca��o */
				{
					temp = new(pilha);
					temp->nome = no_atual->nome;
					temp->anterior = bif;
					bif = temp;
				} /* fim if bifurca��o */
				else
					marca = 1;
			} /* fim if atividade cr�tica */
			i++;
			a_atual = a_atual->proxima;
		} /* fim while menor */
		no_atual = no_atual->proximo;
	} /* fim while maior */

} /* fim da fun��o CPM */