/***************************************************************************
 ***                                                                     ***
 ***   PMC 394 - Laboratório de Computação II                            ***
 ***                                                                     ***
 ***   Tiago Naviskas Lippi                Número USP: 2947938           ***
 ***   Vitor Bellissimo Falleiros          Número USP: 2962011           ***
 ***   Exercicio-Programa 03 - Grafos                                    ***
 ***   Prof. Dr. José Reinaldo                                           ***
 ***                                                                     ***
 ***************************************************************************/



/* Bibliotecas */
#include<stdio.h>



/* Definições */

enum tipo_de_operacao {cria_grafo, destroi_grafo, insere_aresta, destroi_aresta};

typedef struct vertice
{
	int nome;
	struct vertice *proximo; /* indica proximo vertice do grafo */
	struct aresta *p_aresta; /* indica primeira aresta que parte desse vertice */
} vertice; /* fim da definição de vertice */


typedef struct aresta
{
	int peso;
	struct vertice *destino;
	struct aresta *proxima;
} aresta; /* fim da definição de aresta */


typedef struct operacao
{
	tipo_de_operacao realizada;
	int p1, p2, p3;
	struct operacao *anterior;
} operacao; /* fim da definição de operação */



/* Headers das funções */

vertice *Cria_grafo_min(int n); /* cria um grafo de n vertices, sem arestas */

void Destroi_grafo_min(vertice *grafo); /* destrói um grafo sem arestas */

vertice *Acha_vertice(vertice *grafo, int procurado); /* retorna um ponteiro para o
															 nó procurado */
void Acrescenta_aresta(vertice *grafo, int origem, int destino, int peso);
							/* cria uma aresta com as características passadas */
void Remove_aresta(vertice *grafo, int origem, int destino);
							/* remove a aresta entre os dois nós passados */
void Salvar_grafo(vertice *grafo); /* salva o grafo num arquivo, na forma de matriz
								      de adjacências  */
vertice *Recupera_grafo(void); /* lê um grafo de um arquivo */

int Verifica_aresta(vertice *grafo, int i, int j); /* retorna peso de uma aresta, ou zero
													  se ela não existe */
void Remover_grafo(vertice *grafo); /* libera a memória ocupada por um grafo qualquer */

operacao *Desfazer(vertice *grafo, operacao *pilha); /* desfaz a última operação */

operacao *Prepara_desfazer(operacao *pilha, int n1, int n2, int n3, tipo_de_operacao feita);
			/* altera a pilha de operações realizadas cada vez que uma operação é feita */
void Mostrar_grafo(vertice *grafo); /* mostra o grafo na tela para o usuário */



/* Programa */

void main()
{
	vertice *grafo; /* aponta para o início do grafo */
	operacao *pilha; /* aponta uma pilha de operações realizadas, para poder desfazê-las */
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
			   "9. Sair do programa.\n\n"
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
						printf("\nNão há mais operações para desfazer!\n");
					break;
				} /* fim do case resp == 8 */
		} /* fim do switch(resp) */
	} while(resp != 9);

	if(grafo != NULL)
		Remover_grafo(grafo);
} /* fim do 'main' */



/* Funções */

vertice *Cria_grafo_min(int n)
{
	vertice *grafo; /* indicará o primeiro vértice do grafo a ser criado */
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

	/* último vertice: */
	no_atual->nome = n;
	no_atual->proximo = NULL;
	no_atual->p_aresta = NULL;

	return(grafo);
} /* fim da função Cria_grafo_min */


void Destroi_grafo_min(vertice *grafo)
{
	if(grafo->proximo != NULL)
		Destroi_grafo_min(grafo->proximo);

	delete(grafo);
} /* fim da função Destroi_grafo_min */


vertice *Acha_vertice(vertice *grafo, int procurado)
{
	vertice *atual;
	atual = grafo;
	while(atual->nome != procurado)
		atual = atual->proximo;

	return(atual);
} /* fim da função Acha_vertice */


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

	/* inicialização da nova aresta: */
	aresta_atual->peso = peso;
	aresta_atual->destino = no_atual;
	aresta_atual->proxima = NULL;
} /* fim da função Acrescenta_aresta */


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

} /* fim da função Remove_aresta */


void Salvar_grafo(vertice *grafo)
{
	FILE *gravar;
	char arquivo[20];
	vertice *temp;
	int n, i, j, p; /* n guardará a ordem do grafo, p guardará pesos de arestas */

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
} /* fim da função Salvar_grafo */


vertice *Recupera_grafo(void)
{
	FILE *ler;
	vertice *grafo;
	char arquivo[20];
	int n, p, i, j; /* n guardará a ordem do grafo, p guardará pesos de arestas */

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
} /* fim da função Recupera_grafo */


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
} /* fim da função Verifica_aresta */


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
} /* fim da função Remover_grafo */


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
} /* fim da função desfazer */


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
} /* fim da função Prepara_desfazer */


void Mostrar_grafo(vertice *grafo)
{
	vertice *temp;
	int n, i, j, p; /* n guardará a ordem do grafo, p guardará pesos de arestas */

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

} /* fim da função Mostrar_grafo */