/******************************************************************************
 ***																		***
 ***	PMC 394 - Laboratório de Computação II								***
 ***																		***
 ***	Tiago Naviskas Lippi                Número USP: 2947938				***
 ***	Vitor Bellissimo Falleiros          Número USP: 2962011				***
 ***	Exercicio-Programa 06 - Filas: Simulação de eventos discretos		***
 ***	Prof. Dr. José Reinaldo												***
 ***																		***
 ******************************************************************************/



/* Bibliotecas */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>



/* Definições */

#define tam_max 20
#define NMAX_Filas 5

enum boolean {V, F}; /* verdadeiro ou falso */
enum TiposDeEventos {ev1, ev2, ev3};

typedef struct FilaEstudante
{
	long estudantes[tam_max];
	int inicio, fim; /* indicam inicio e fim da fila */
	boolean cheia; /* indica se fila está cheia ou não */
} FilaEstudante; /* fim da definição de FilaEstudante */

typedef struct evento
{
	TiposDeEventos tipo; /* tipo de evento */
	long Tocorre; /* tempo em que o evento ocorre */
	int Fila; /* fila à qual o evento está associado */
	struct evento *proximo; /* proximo evento da fila */
} evento; /* fim da definição de evento */

typedef struct estatisticas
{
	int nt; /* quantidade total de alunos em todas as filas, ao longo do tempo */
	long T; /* tempo de espera acumulado */
	int N; /* número de alunos atendidos */
	float tm; /* tempo médio de espera por estudante */
	float nm; /* número médio de estudantes no sistema */
} estatisticas; /* fim da definição de estatisticas */



/* Headers das funções */

void InicializaEstudantes(FilaEstudante FE[NMAX_Filas], int N);

void InicializaEventos(evento *&fila, long Ci, long Cf, long TMAX);

void InicializaEstatistica(estatisticas &e);

void Trata1(FilaEstudante FEst[NMAX_Filas], evento *&fila, boolean FilaEspecial,
			int NFilas, float ideal, int Cf, boolean ServidorLivre[NMAX_Filas]);
			/* opera filas quando há um evento tipo 1 (chegada de um aluno) */
void Trata2(FilaEstudante FEst[NMAX_Filas], evento *&fila, boolean FilaEspecial,
			int Di, int Df, int DT, boolean ServidorLivre[NMAX_Filas]);
			/* opera filas quando há um evento tipo 2 (início de atendimento) */
void Trata3(evento *&fila, boolean ServidorLivre[NMAX_Filas]);
			/* opera filas quando há um evento tipo 3 (fim de atendimento) */
void TrataEstat(estatisticas &e, evento *fila, long relogio);
			/* atualiza as estatísticas a cada evento */
void InsQ(FilaEstudante &f, int chegada);
			/* insere um estudante numa fila de estudantes */
void RetQ(FilaEstudante &f);
			/* retira um estudante de uma fila de estudantes */
void InsFE(evento *&fila, TiposDeEventos k, int Tempo, int FilaRelac);
			/* insere um evento na fila de eventos */
int TamanhoFila(FilaEstudante F); /* retorna o tamanho da fila dada */

void CalculaMedias(estatisticas &e, int TMAX); /* calcula nm e tm, ao final da simulação */

void MostraEstat(estatisticas e); /* mostra na tela as estatísticas da simulação */



/* Programa */

void main()
{
	FilaEstudante FEst[NMAX_Filas];
	evento *fila; /* indica fila de eventos, de forma dinâmica */
	estatisticas e; /* armazena estatísticas */
	int i, rint;
	char rchar;
	int NFilas = 0; /* quantidade de filas */
	long Ci, Cf; /* limites de tempo para chegada de alunos */
	int Di, Df; /* limites de tempo para o intervalo de atendimento do servidor */
	int DT; /* tempo de atendimento na fila especial */
	float ideal = 0; /* porcentagem de alunos no semestre ideal */
	long relogio; /* relogio de simulação */
	long TMAX = 0; /* tempo máximo de simulação */
	boolean FilaEspecial = F; /* indica se existe a fila especial */
	boolean ServidorLivre[NMAX_Filas]; /* indica se o servidor está livre */


	printf("\n\nBom dia!\n\n");
	
	do
	{
		printf("\nDeseja alterar alguma variável da simulação?\n\n"
			   "1. Quantidade de filas de alunos;\n"
			   "2. Tempo máximo de simulação;\n"
			   "3. Limites de chegada dos alunos;\n"
			   "4. Limites do intervalo de atendimento;\n"
			   "5. Existência de fila especial;\n"
			   "6. Porcentagem de alunos no semestre ideal;\n"
			   "7. Iniciar simulação;\n"
			   "8. Sair do programa.\n\n"
			   "Digite sua escolha: ");
		scanf("%d",&rint);

		switch(rint)
		{
			case 1:
				{
					do
					{
						printf("\nDigite o número de filas: ");
						scanf("%d", &NFilas);
					} while (NFilas > NMAX_Filas && NFilas < 1);
					break;
				} /* fim do case rint == 1 */
			case 2:
				{
					printf("\nDigite o tempo máximo de simulação: ");
					scanf("%ld", &TMAX);
					break;
				} /* fim do case rint == 2 */
			case 3:
				{
					if(TMAX != 0)
						do
						{
							printf("\nDigite o limite inferior de chegada de alunos: ");
							scanf("%ld", &Ci);
							printf("\nDigite o limite superior de chegada de alunos: ");
							scanf("%ld", &Cf);
						} while (Cf < Ci || Cf > TMAX);
					else
						printf("\nEntre um tempo máximo de simulação primeiro.\n\n");
					break;
				} /* fim do case rint == 3 */
			case 4:
				{
					do
					{
						printf("\nDigite o limite inferior do atendimento: ");
						scanf("%d", &Di);
						printf("\nDigite o limite superior do atendimento: ");
						scanf("%d", &Df);
						printf("\nDigite o tempo de atendimento no terminal especial: ");
						scanf("%d", &DT);
					} while (Df < Di);
					break;
				} /* fim do case rint == 4 */
			case 5:
				{
					printf("\nDeseja designar uma fila apenas "
						   "para alunos do semestre ideal? (s/n)\n");
					scanf("%c", &rchar);
					scanf("%c", &rchar);
					if(rchar == 's')
						FilaEspecial = V;
					else
						FilaEspecial = F;
					break;
				} /* fim do case rint == 5 */
			case 6:
				{
					do
					{
						printf("\nDigite a porcentagem de alunos no semestre ideal (0-100): ");
						scanf("%f", &ideal);
					} while (ideal < 0 || ideal > 100);
					break;
				} /* fim do case rint == 6 */
			case 7:
				{
					randomize(); /* inicializa gerador de números aleatórios */

					relogio = 0;
					InicializaEstudantes(FEst, NFilas);
					for(i = 0; i < NMAX_Filas; i++)
						ServidorLivre[i] = V;
					fila = NULL;
					InicializaEventos(fila, Ci, Cf, TMAX);
					InicializaEstatistica(e);

					while(relogio <= TMAX && fila != NULL) /* tempo de simulação */
					{
						switch(fila->tipo)
						{
							case ev1:
								{
									TrataEstat(e, fila, relogio);
									Trata1(FEst, fila, FilaEspecial, NFilas, ideal, Cf,
											ServidorLivre);
									break;
								} /* fim case tipo == ev1 */
							case ev2:
								{
									TrataEstat(e, fila, relogio);
									Trata2(FEst, fila, FilaEspecial, Di, Df, DT,
											ServidorLivre);
									break;
								} /* fim case tipo == ev2 */
							case ev3:
								{
									TrataEstat(e, fila, relogio);
									Trata3(fila, ServidorLivre);
									break;
								} /* fim case tipo == ev3 */
						} /* fim switch(atual->tipo) */

						relogio = fila->Tocorre;
						fila = fila->proximo;			
					} /* fim while tempo */

					CalculaMedias(e, TMAX);
					MostraEstat(e);
				} /* fim do case rint == 7 */
		} /* fim do switch(rint) */
	} while(rint != 8);

} /* fim do 'main' */



/* Funções */

void InicializaEstudantes(FilaEstudante FE[NMAX_Filas], int N)
{
	int i, j;

	for(i = 0; i < N; i++)
	{
		FE[i].inicio = 0;
		FE[i].fim = 0;
		FE[i].cheia = F;
		for(j = 0; j < tam_max; j++)
			FE[i].estudantes[j] = 0;
	} /* fim for i */
} /* fim da função InicializaEstudantes */


void InicializaEventos(evento *&fila, long Ci, long Cf, long TMAX)
{
	long t = 0;

	t = random((TMAX - Ci)*10);
	t = (t/10) + Ci;

	if(t < Cf)
	{
		fila = new(evento);
		fila->tipo = ev1;
		fila->Tocorre = t;
		fila->proximo = NULL;

		InicializaEventos(fila->proximo, t, Cf, TMAX);
	} /* fim if */

} /* fim da função InicializaEventos */


void InicializaEstatistica(estatisticas &e)
{
	e.nt = 0;
	e.N = 0;
	e.T = 0;
	e.nm = 0;
	e.tm = 0;
} /* fim da função InicializaEstatistica */


void Trata1(FilaEstudante FEst[NMAX_Filas], evento *&fila, boolean FilaEspecial,
			int NFilas, float ideal, int Cf, boolean ServidorLivre[NMAX_Filas])
{
	float p;
	int temp;
	int n = NFilas; /* número da menor fila */
	int tam = tam_max; /* tamanho da menor fila */
	int i = 0; /* contador */
	boolean AlunoEspecial = F; /* indica se o aluno em questão é ideal ou não */

	if(FilaEspecial == V) /* existe fila especial? */
	{
		p = random(10000);
		p = p/100;
		if(p < ideal)
			AlunoEspecial = V;
	} /* fim if existe fila especial */

	if(AlunoEspecial == V)
	{
		n = 0;
		if(FEst[0].cheia == F)
			InsQ(FEst[0], fila->Tocorre);
		else
		{
			p = random(Cf - fila->Tocorre);
			p = p + fila->Tocorre;
			InsFE(fila, ev1, p, 0);
		} /* fim else */
	}
	else
	{
		if(FilaEspecial == V)
			i = 1;
		while(i < NFilas)
		{
			temp = TamanhoFila(FEst[i]);
			if(temp < tam)
			{
				tam = temp;
				n = i;
			} /* fim if */
			i++;
		} /* fim while */

		if(n < NFilas)
			InsQ(FEst[n], fila->Tocorre);
		else
		{
			p = random(Cf - fila->Tocorre);
			p = p + fila->Tocorre;
			InsFE(fila, ev1, p, 0);
		} /* fim else */
	} /* fim else */

	if(n < NFilas && ServidorLivre[n] == V)
		InsFE(fila, ev2, fila->Tocorre, n);

} /* fim da função Trata1 */


void Trata2(FilaEstudante FEst[NMAX_Filas], evento *&fila, boolean FilaEspecial,
			int Di, int Df, int DT, boolean ServidorLivre[NMAX_Filas])
{
	int t;

	if(FilaEspecial == V && fila->Fila == 0)
	{
		t = DT + fila->Tocorre;
	} /* fim if */
	else
	{
		t = random(Df - Di);
		t = t + Di;
		t = t + fila->Tocorre;
	} /* fim else */

	InsFE(fila, ev3, t, fila->Fila);

	t = fila->Fila;
	RetQ(FEst[t]);
	ServidorLivre[t] = F;
} /* fim da função Trata2 */


void Trata3(evento *&fila, boolean ServidorLivre[NMAX_Filas])
{
	InsFE(fila, ev2, fila->Tocorre, fila->Fila);
	ServidorLivre[fila->Fila] = V;
} /* fim da função Trata3 */


void TrataEstat(estatisticas &e, evento *fila, long relogio)
{
	e.T = e.T + e.nt * (fila->Tocorre - relogio);

	switch(fila->tipo)
	{
		case ev1:
			{
				e.N++;
				e.nt++;
				break;
			} /* fim case tipo == ev1 */
		case ev2:
			{
				e.nt--;
				break;
			} /* fim case tipo == ev2 */
	} /* fim switch(fila->tipo) */
} /* fim da função TrataEstat */


void InsQ(FilaEstudante &f, int chegada)
{
	f.estudantes[f.fim] = chegada;
	f.fim++;
	if(f.fim == tam_max)
		f.fim = 0;
	if(f.fim == f.inicio) /* encheu? */
		f.cheia = V;
} /* fim da função InsQ */


void RetQ(FilaEstudante &f)
{
	f.estudantes[f.inicio] = 0;
	if(f.inicio == f.fim) /* estava cheia? */
		f.cheia = F;
	f.inicio++;
	if(f.inicio == tam_max)
		f.inicio = 0;
} /* fim da função RetQ */


void InsFE(evento *&fila, TiposDeEventos k, int Tempo, int FilaRelac)
{
	evento *temp, *atual;

	temp = new(evento);
	temp->tipo = k;
	temp->Tocorre = Tempo;
	temp->Fila = FilaRelac;

	if(Tempo < fila->Tocorre)
	{
		temp->proximo = fila;
		fila = temp;
	} /* fim if */
	else
	{
		atual = fila;
		while(atual->proximo->Tocorre < Tempo)
			atual = atual->proximo;
		temp->proximo = atual->proximo;
		atual->proximo = temp;
	} /* fim if */

} /* fim da função InsFE */


int TamanhoFila(FilaEstudante F)
{
	int t, i;

	if(F.cheia == V)
		t = tam_max;
	else
	{
		t = 0;
		i = F.inicio;
		while(i != F.fim)
		{
			t++;
			i++;
			if(i == tam_max)
				i = 0;
		} /* fim while */
	} /* fim else */
	return(t);
} /* fim da função TamanhoFila */


void CalculaMedias(estatisticas &e, int TMAX)
{
	e.nm = e.T/TMAX;
	e.tm = e.T/e.N;
} /* fim da função CalculaMedias */


void MostraEstat(estatisticas e)
{
	printf("\n\nEstatísticas da simulação:\n");
	printf("\nNúmero total de estudantes atendidos: %d;", e.N);
	printf("\nTempo acumulado de N: %ld minutos;", e.T);
	printf("\nNúmero médio de alunos no sistema: %.2f;", e.nm);
	printf("\nTempo médio gasto por aluno: %.2f minutos.\n", e.tm);		   
} /* fim da função MostraEstat */