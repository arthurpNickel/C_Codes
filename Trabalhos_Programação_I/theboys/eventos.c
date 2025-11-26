//posso ir criando novos campos? -> heroi vivo, missao cumprida, 
//acesso de herois em missao
//Verificar se tem que fazer casos de erro
//Enquanto o herói está viajando ele carrega na sua struct o id da base antiga?
//Prorrogar o evento missão -> mudar tempo ou criar novo evento?


//TO DO:
//Mudar todo o vetor de missões para estrutura dinâmica
//Criar um estrutura para a ordenação de bases por distância!!
//Modular criação dos eventos e inserção na LEF
//Arrumar evento avisa -> ?
//Modular cálculo de distância
//Verificar se as variáveis do evento missão estão liberadas e aterradas
//Verificar se o laço que eu fiz no evento missão para encontrar a BPM está bom

//QUESTION:
//Verificar se as minhas soluções sobre missões são válidas
//Vetor de structs dentro da struct missão já?
//Como marco missão como cumprida -> novo campo?
//O jeito que eu fiz para acessar os heróis de uma base está bom? (e consequentemente suas habilidades)
//Verficar herói morto -> novo campo ou conjunto de vivos?
//Primeiro if do evento chega?
//Verificar se tem que fazer casos de erro
//Enquanto o herói está viajando ele carrega na sua struct o id da base antiga?
//Decremento número de heróis em evento morre?
//Como identifico o evento missão? M, m, mi, ...
//Prorrogar o evento missão -> mudar tempo ou criar novo evento?

/* Implementação dos eventos */

#include "eventos.h"

/*
#include "sorts.h"
*/

/*double???
double distancia(int x1, int y1, int x2, int y2) 
{
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}
*/

/* Função de troca */
static void troca(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

/* Calcula distância */
static int calcula_distancia(struct Mundo *m, struct Missao *M, int id_base)
{
    int dx = m->bases[id_base].local.x - M->local.x;
    int dy = m->bases[id_base].local.y - M->local.y;
    return dx*dx + dy*dy; /* distância ao quadrado (evita sqrt) */
}

/* Partição */
void Particao(struct Mundo *m, struct Missao *M, int v[], int ini, int fim, int *pos_pivo)
{
    int i = ini + 1, j = fim;
    int pospivo = ini;
    int pivo = calcula_distancia(m, M, v[pospivo]);

    troca(&v[ini], &v[pospivo]);

    while (i < j)
    {
        while (i <= fim && calcula_distancia(m, M, v[i]) <= pivo)
            i++;

        while (j > ini && calcula_distancia(m, M, v[j]) > pivo)
            j--;

        if (i < j)
            troca(&v[i], &v[j]);
    }

    troca(&v[ini], &v[j]);
    *pos_pivo = j;
}

//usar static???!!!!!!!!!!!!!!!!!!!!!
/* QuickSort */
void QuickSort(struct Mundo *m, struct Missao *M, int v[], int ini, int fim)
{
    int pos_pivo;

    if (ini < fim)
    {
        Particao(m, M, v, ini, fim, &pos_pivo);
        QuickSort(m, M, v, ini, pos_pivo - 1);
        QuickSort(m, M, v, pos_pivo + 1, fim);
    }
}  

/* Cria evento chega e insere na LEF */
void cria_evento_chega(struct Mundo *m, int heroi, int base, int tempo)
{
	struct chega *c;
	if (!(c = malloc(sizeof(struct chega))))
		return;

	c->heroi = heroi;
	c->base = base;
	c->tempo = tempo;

	fprio_insere(m->LEF, c, CHEGA, c->tempo);
}

/* Cria evento espera e insere na LEF */
void cria_evento_espera(struct Mundo *m, int heroi, int base, int tempo)
{
	struct espera *e;
	if (!(e = malloc(sizeof(struct espera))))
		return;

	e->heroi = heroi;
	e->base = base;
	e->tempo = tempo;

	fprio_insere(m->LEF, e, ESPERA, e->tempo);
}

/* Cria evento desiste e insere na LEF */
void cria_evento_desiste(struct Mundo *m, int heroi, int base, int tempo)
{
	struct desiste *d;
	if (!(d = malloc(sizeof(struct desiste))))
		return;

	d->heroi = heroi;
	d->base = base;
	d->tempo = tempo;

	fprio_insere(m->LEF, d, DESISTE, d->tempo);
}

/* Cria evento avisa e insere na LEF */
void cria_evento_avisa(struct Mundo *m, int base, int tempo)
{
	struct avisa *a;
	if (!(a = malloc(sizeof(struct avisa))))
		return;

	a->base = base;
	a->tempo = tempo;

	fprio_insere(m->LEF, a, AVISA, a->tempo);
}

/* Cria evento viaja e insere na LEF */
void cria_evento_viaja(struct Mundo *m, int heroi, int destino, int tempo)
{
	struct viaja *v;
	if (!(v = malloc(sizeof(struct viaja))))
		return;

	v->heroi = heroi;
	v->destino = destino;
	v->tempo = tempo;

	fprio_insere(m->LEF, v, VIAJA, v->tempo);
}

/* Cria evento sai e insere na LEF */
void cria_evento_sai(struct Mundo *m, int heroi, int base, int tempo)
{
	struct sai *s;
	if (!(s = malloc(sizeof(struct sai))))
		return;

	s->heroi = heroi;
	s->base = base;
	s->tempo = tempo;

	fprio_insere(m->LEF, s, SAI, s->tempo);
}

/* Cria evento entra e insere na LEF */
void cria_evento_entra(struct Mundo *m, int heroi, int base, int tempo)
{
	struct entra *in;
	if (!(in = malloc(sizeof(struct entra))))
		return;

	in->heroi = heroi;
	in->base = base;
	in->tempo = tempo;

	fprio_insere(m->LEF, in, ENTRA, in->tempo);
}

/* Cria evento morre e insere na LEF */
void cria_evento_morre(struct Mundo *m, int heroi, int base, int tempo)
{
	struct morre *mo;
	if (!(mo = malloc(sizeof(struct morre))))
		return;

	mo->base = base;
	mo->heroi = heroi;
	mo->tempo = tempo;

	fprio_insere(m->LEF, mo, MORRE, mo->tempo);
}

/* Verifica se o herói está morto */
int heroi_morto(struct Mundo *m, int heroi)
{
	if (cjto_pertence(m->vivos, heroi))
		return 0;
	return 1;
}

/*Herói h chegando na base b no instante t. Ao chegar, o
herói analisa o tamanho da fila e decide se espera para entrar ou desiste*/
void evento_chega(struct Mundo *m, struct chega *c)
{
	int espera;
	struct espera *e;
	struct desiste *d;

	if (heroi_morto(m, c->heroi))
		return;

	printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ",
	c->tempo, c->heroi, c->base, fila_tamanho(m->bases[c->base].fila_espera), m->bases[c->base].lotacao);

	m->herois[c->heroi].base = c->base; /* Muda ID da base que herói se encontra no momento*/

	if (fila_tamanho(m->bases[c->base].fila_espera) < m->bases[c->base].lotacao && //Q: precisa dessa primeira verificação???!!!!!!!!!!!!!!!!!!!!!!
		fila_tamanho(m->bases[c->base].fila_espera) == 0)
		espera = 1;

	else //Q: return? !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		espera =  m->herois[c->heroi].paciencia > 10 * fila_tamanho(m->bases[c->base].fila_espera);
    
    if (espera)
    {
		printf("ESPERA\n");
		cria_evento_espera(m, c->heroi, c->base, c->tempo);
    }

	printf("DESISTE\n");
	cria_evento_desiste(m, c->heroi, c->base, c->tempo);
}

/* O herói H entra na fila de espera da base B. Assim que H entrar na fila, o
porteiro da base B deve ser avisado para verificar a fila: */
void evento_espera(struct Mundo *m, struct espera *e)
{
	struct avisa *a;

	if (heroi_morto(m, e->heroi))
		return;

	printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",
			e->tempo, e->heroi, e->base, fila_tamanho(m->bases[e->base].fila_espera));
	
	fila_insere(m->bases[e->base].fila_espera, e->heroi); //algum caso de erro???!!!!!!!!

	cria_evento_avisa(m, e->base, e->tempo);
}

/*O herói H desiste de entrar na base B, escolhe uma base aleatória D e viaja
para lá*/
void evento_desiste(struct Mundo *m, struct espera *d)
{
	struct viaja *v;
	int destino; //Q: precisa?!!!!!!!!!!!!!!!!!!!!!!!!!!

	if (heroi_morto(m, d->heroi))
		return;

	destino = rand() % m->nbases; /* Escolhe uma base aleatória */

	cria_evento_viaja(m, d->heroi, destino, d->tempo);

	printf("%6d: DESISTE HEROI %2d BASE %d\n",
			d->tempo, d->heroi, d->base);
}

/* O porteiro da base B trata a fila de espera: */
void evento_avisa(struct Mundo *m, struct avisa *a)
{
	struct entra *in;
	int h;
	
	//T: arrumar aqui
	printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", 
			a->tempo, a->base, fila_tamanho(m->bases[a->base].fila_espera), m->bases[a->base].lotacao);
	
	fila_imprime(m->bases[a->base].fila_espera); //verificar se deu boa!!!!!!!!!!!!!!!!!!!!!!!!!!
	printf (" ]\n");

	//m->bases[a->base].lotacao ou m->bases[a->base].presentes->cap???!!!!!!!!!!!!!!!!!!!!!!!
	while (m->bases[a->base].lotacao > cjto_card(m->bases[a->base].presentes) 
			&& fila_tamanho(m->bases[a->base].fila_espera) != 0)
	{
		fila_retira(m->bases[a->base].fila_espera, &h);
		cjto_insere(m->bases[a->base].presentes, h);

		cria_evento_entra(m, h, a->base, a->tempo);

		printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n",
				a->tempo, a->base, h);
	}
}

/*O herói H entra na base B. Ao entrar, o herói decide quanto tempo vai ficar e
agenda sua saída da base*/
void evento_entra(struct Mundo *m, struct entra *in)
{
	struct sai *s;
	int TPB;

	if (heroi_morto(m, in->heroi))
		return;

	/* Calcula tempo de permanência na base (TPM) */
	TPB = 15 + m->herois[in->heroi].paciencia * (1 + rand() % 20); //1 a 20

	cria_evento_sai(m, in->heroi, in->base, in->tempo + TPB);

	printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n",
		in->tempo, in->heroi, in->base, cjto_card(m->bases[in->base].presentes), //ver se errei isso em outro lugar!!!!!!!!!!!!!!!
		m->bases[in->base].lotacao, s->tempo);
}

/*O herói H sai da base B. Ao sair, escolhe uma base de destino para viajar; o
porteiro de B é avisado, pois uma vaga foi liberada*/
void evento_sai(struct Mundo *m, struct sai *s)
{
	struct viaja *v;
	struct avisa *a;
	int destino, status;

	if (heroi_morto(m, s->heroi))
		return;

	status = cjto_retira(m->bases[s->base].presentes, s->heroi);

	//Q: if (status == -1) ????!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	destino = rand() % m->nbases; /* Escolhe uma base aleatória */

	cria_evento_viaja(m, s->heroi, destino, s->tempo);

	cria_evento_avisa(m, s->base, s->tempo);

	printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n",
			s->tempo, s->heroi, s->base, cjto_card(m->bases[s->base].presentes), m->bases[s->base].lotacao);
}

//Q: qual o sentido disso?????!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
/*O herói H se desloca para uma base D (que pode ser a mesma onde já está)*/
void evento_viaja(struct Mundo *m, struct viaja *v)
{
	struct chega *c;
	int distancia, duracao;

	if (heroi_morto(m, v->heroi))
		return;

	/* Cálculo da distância e da duração */
	//T: modular distância??!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	distancia = (int) sqrt((double)(pow((m->bases[v->destino].local.x - m->bases[m->herois[v->heroi].base].local.x), 2)
	 						+ pow((m->bases[v->destino].local.y - m->bases[m->herois[v->heroi].base].local.y), 2)));

	duracao = distancia / m->herois[v->heroi].velocidade; //arredondar para cima?? -> viagens instantâneas

	cria_evento_chega(m, v->heroi, v->destino, v->tempo + duracao);

	printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",
			v->tempo, v->heroi, m->herois[v->heroi].base, v->destino, 
			distancia, m->herois[v->heroi].velocidade, c->tempo);
}

//Q: Decrementar número de heróis!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*O herói H morre no instante T.*/
void evento_morre(struct Mundo *m, struct morre *mo)
{
	struct avisa *a;

	if (heroi_morto(m, mo->heroi)) //será??!!!!!!!!!!!!!!!!!!!!!
		return;

	cjto_retira(m->bases[mo->base].presentes, mo->heroi); /* Retira herói da base em que se encontra */

	//Q: Como mudo status do herói??!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//por enquanto assim:
	cjto_retira(m->vivos, mo->heroi);

	cria_evento_avisa(m, mo->base, mo->tempo);

	printf("%6d: MORRE HEROI %2d MISSAO %d\n", mo->tempo, mo->heroi, 0);
}

//T: verificar aterramentos
//T: manipulação de ponteiro de bases e etc!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/*Uma missão M é disparada no instante T*/
void evento_missao(struct Mundo *m, struct Missao *M) //Q: Manter esse m maiusculo????!!!!!!!!!!!!!!
{
	struct cjto_t *habilidades_base;
	struct morre *mo;
	int i, j, distancia, BMP, b, primeira_id, id_base, escolhido, xp_atual; //T: verificar
	int distancia_missao[NBASES]; /* Cria vetor ordenado pela distância */

	M->tentativas++;

	printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", M->tempo, M->id, M->tentativas);
	cjto_imprime(M->habilidades_m);
	printf(" ]\n");

	/* Inicializa vetor de bases ordenado pela distância a missão */
	for (i = 0; i < m->nbases; i++)
		distancia_missao[i] = i;

    /* Ordena as bases pelo critério de distância */
    QuickSort(m, M, distancia_missao, 0, m->nbases - 1);	
	
	//T: avaliar retorno de tipo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//T: modular distância??!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//distancia = sqrt(pow(m->bases[i].local.x - M->local.x, 2) + pow(m->bases[i].local.y - M->local.y, 2));

	//DEBUG: verficar se ordenação está dando certo
	for (i = 0; i < m->nbases; i++)
	{
		printf("%6d: MISSAO %d BASE %d DIST %d HEROIS [ ", M->tempo, M->id, i, calcula_distancia(m, M, distancia_missao[i]));
		cjto_imprime(m->bases[i].presentes);
		printf(" ]\n");
	}

	BMP = 0; /* "Base mais próxima com heróis capazes" <- Falso */

	/* Verifica se existe alguma base com todas as habilidades necessárias para a missão */
	i = 0; /* Inicializa indice do vetor de bases ordenada por distância */
	while (!BMP && i < m->nbases)
	{
		/* Criação do conjunto de habilidades da base retirada*/
		habilidades_base = cjto_cria();

		for (j = 0; j < m->nherois; j++)
		{
			/* Se o herói j pertecente a base da vez, então suas habilidades são unidas as da base*/
			if (cjto_pertence(m->bases[distancia_base[i]].presentes, j))
			{
				printf("%6d: MISSAO %d HAB HEROI %2d: [ ", M->tempo, M->id, j);
				cjto_imprime(m->herois[j].habilidades);
				printf(" ]\n");

				habilidades_base = cjto_uniao(habilidades_base, m->herois[j].habilidades);

				printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ", M->tempo, M->id, distancia_missao[i]);
				cjto_imprime(habilidades_base);
				printf(" ]\n");
			}
		}

		//Q: guardar a primeira base aqui!!!!!!!!!!!!!!!!!!!!!!!!! 

		/* Verifica se as habilidades da missão estão contidas no conjunto de habilidades da base*/
		if (cjto_contem(habilidades_base, M->habilidades_m))
			BMP = 1; /* Base é marcada como BMP (o id dela está na variável id) */
		else
			cjto_destroi(habilidades_base); //Q: ou colocar um break no if de cima???!!!!!!!!!!!!!!!!!!!!!!!

		i++;
	}

	/* Se existe base cujos heróis conseguem cumprir a missão: */
	//id dessa base está salvo
	if (BMP)
	{
		//Q: marcar missão como cumprida?!!!!!!!!!!!!!!!!!!!

		printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", M->tempo, M->id, id_base);
		cjto_imprime(habilidades_base);
		printf(" ]\n");
		cjto_destroi(habilidades_base);

		for (i = 0; i < m->nherois; i++)
			/* Se o herói pertecente a base e não está morto, então sua experiência aumenta*/
			if (cjto_pertence(m->bases[id_base].presentes, i) && !heroi_morto(m, i))
				m->herois[i].xp++;

		return;
	}

	/* Se não, verifica se é possível usar composto V*/
	if (m->ncompostos != 0 && M->tempo % 2500 == 0)
	{
		m->ncompostos--;

		//Q: marcar missão como cumprida?!!!!!!!!!!!!!!!!!!!

		//Q: Tá bom essa criação do conjunto??!!!!!!!!!!!!!!!!!!!!!!!!!!!

		/* Criação do conjunto de habilidades da base mais próxima mais as habilidades do herói com composto V*/
		habilidades_base = cjto_cria(NHABILIDADES);
		for (i = 0; i < m->nherois; i++) //Q: Ta bom acessar os herois da base desse jeito??!!!!!!!!!!!!!!!!!!
			/* Se o herói pertecente a base, então suas habilidades são unidas as da base*/
			if (cjto_pertence(m->bases[primeira_id].presentes, i))
				habilidades_base = cjto_uniao(habilidades_base, m->herois[i].habilidades);
		
		habilidades_base = cjto_uniao(habilidades_base, M->habilidades_m); /* Adiciona ao conjunto de habilidades da base as habilidades da missão*/

		printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", M->tempo, M->id, primeira_id);
		cjto_imprime(habilidades_base);
		printf(" ]\n");
		cjto_destroi(habilidades_base);

		/* Procura herói mais experiente da base mais próxima */
		//base mais próxima tem heróis presentes
		//Q: isso tá com cara de gambiarra!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		xp_atual = -1;	/* Variável para buscar maior xp */
		for (i = 0; i < m->nherois; i++) //Q: Ta bom acessar os herois da base desse jeito??!!!!!!!!!!!!!!!!!!
		{
			/* Se o herói pertecente a base e tem xp maior que o atual escolhido, então ele passa a ser o escolhido*/
			if (cjto_pertence(m->bases[primeira_id].presentes, i) && m->herois[i].xp > xp_atual && !heroi_morto(m, i))
			{
				xp_atual = m->herois[i].xp;
				escolhido = i;
			}
		}

		for (i = 0; i < m->nherois; i++) //Q: Ta bom acessar os herois da base desse jeito??!!!!!!!!!!!!!!!!!!
		{
			/* Se o herói pertecente a base, então sua experiência aumenta*/
			if (cjto_pertence(m->bases[primeira_id].presentes, i) && !heroi_morto(m, i))
				m->herois[i].xp++;
		}

		cria_evento_morre(m, escolhido, m->herois[escolhido].base, M->tempo);
		
		return;
	}

	/* Se não, adia missão por 1 dia*/
	//Q: acho que isso vai dar ruim!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	printf("%6d: MISSAO %d IMPOSSIVEL\n", M->tempo, M->id);
	M->tempo = M->tempo + 1440;
	fprio_insere(m->LEF, M, MISSAO, M->tempo);
}