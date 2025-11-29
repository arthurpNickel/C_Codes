//TO DO:
//Arrumar evento avisa -> ?
//Modular cálculo de distância -> "arrumar"
//Verificar se as variáveis do evento missão estão liberadas e aterradas
//Verificar se o laço que eu fiz no evento missão para encontrar a BPM está bom


//QUESTION:
//Verificar se as minhas soluções sobre missões são válidas
//Como marco missão como cumprida -> novo campo?
//Verificar se tem que fazer casos de erro
//Enquanto o herói está viajando ele carrega na sua struct o id da base antiga?
//Decremento número de heróis em evento morre?
//Como identifico o evento missão? M, m, mi, ...
//Aumenta-se o XP do herói que usará composto V?
//Vale a pena modular herói vivo?
//Em todas os eventos preciso verificar se herói está vivo?

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

/* retorna um número aleatório entre min e max, inclusive */
int aleatorio(int min, int max)
{
	return min + rand() % (max - min + 1);
}

/* Retorna união das habilidades entre u (onde será unido) e h */
struct cjto_t *uniao_habilidades(struct cjto_t *u, struct cjto_t *h)
{
    struct cjto_t *aux = cjto_uniao(u, h);
    cjto_destroi(u);
    return aux;
}


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

/* Cria evento missão e inicializa atributos */
void inicializa_evento_missao(struct Mundo *m, int id)
{
	if (!(m->missoes[id] = malloc(sizeof(struct Missao))))
		return;

	m->missoes[id]->id = id;
	m->missoes[id]->tentativas = 0;
	m->missoes[id]->local.x = aleatorio(0, m->tam_mundo.x - 1);
	m->missoes[id]->local.y = aleatorio(0, m->tam_mundo.y - 1);
	m->missoes[id]->habilidades_m = cjto_aleat(aleatorio(6, 10), m->nhabilidades);
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

/* Cria evento fim e insere na LEF */
void cria_evento_fim(struct Mundo *m)
{
	struct fim *f;
	if (!(f = malloc(sizeof(struct fim))))
		return;

	f->tempo = FIMMUNDO;

	fprio_insere(m->LEF, f, FIM, f->tempo);
}

/*Herói h chegando na base b no instante t. Ao chegar, o
herói analisa o tamanho da fila e decide se espera para entrar ou desiste*/
void evento_chega(struct Mundo *m, struct chega *c)
{
	int espera;

	/* Se herói estiver morto, ignora o evento */
	if (!m->herois[c->heroi].vivo)
		return;

	m->neventos++;

	printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ",
	c->tempo, c->heroi, c->base, fila_tamanho(m->bases[c->base].fila_espera), m->bases[c->base].lotacao);

	m->herois[c->heroi].base = c->base; /* Muda ID da base que herói se encontra no momento*/

	if (fila_tamanho(m->bases[c->base].fila_espera) < m->bases[c->base].lotacao &&
		fila_tamanho(m->bases[c->base].fila_espera) == 0)
		espera = 1;

	else 
		espera =  m->herois[c->heroi].paciencia > 10 * fila_tamanho(m->bases[c->base].fila_espera);
    
    if (espera)
    {
		printf("ESPERA\n");
		cria_evento_espera(m, c->heroi, c->base, c->tempo);
		return;
    }

	printf("DESISTE\n");
	cria_evento_desiste(m, c->heroi, c->base, c->tempo);
}

/* O herói H entra na fila de espera da base B. Assim que H entrar na fila, o
porteiro da base B deve ser avisado para verificar a fila: */
void evento_espera(struct Mundo *m, struct espera *e)
{
	/* Se herói estiver morto, ignora o evento */
	if (!m->herois[e->heroi].vivo)
		return;
	
	m->neventos++;

	printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",
			e->tempo, e->heroi, e->base, fila_tamanho(m->bases[e->base].fila_espera));
	
	fila_insere(m->bases[e->base].fila_espera, e->heroi); //algum caso de erro???!!!!!!!!

	//Q: Verificar se pode!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (fila_tamanho(m->bases[e->base].fila_espera) > m->bases[e->base].fila_max)
		m->bases[e->base].fila_max = fila_tamanho(m->bases[e->base].fila_espera);

	cria_evento_avisa(m, e->base, e->tempo);
}

/*O herói H desiste de entrar na base B, escolhe uma base aleatória D e viaja
para lá*/
void evento_desiste(struct Mundo *m, struct espera *d)
{
	int destino; //Q: precisa?!!!!!!!!!!!!!!!!!!!!!!!!!!

	/* Se herói estiver morto, ignora o evento */
	if (!m->herois[d->heroi].vivo)
		return;

	m->neventos++;

	destino = aleatorio(0, m->nbases-1);

	cria_evento_viaja(m, d->heroi, destino, d->tempo);

	printf("%6d: DESISTE HEROI %2d BASE %d\n",
			d->tempo, d->heroi, d->base);
}

/* O porteiro da base B trata a fila de espera: */
void evento_avisa(struct Mundo *m, struct avisa *a)
{
	int h;
	
	m->neventos++;

	//T: arrumar aqui
	printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", 
			a->tempo, a->base, fila_tamanho(m->bases[a->base].fila_espera), m->bases[a->base].lotacao);
	
	fila_imprime(m->bases[a->base].fila_espera); //T: verificar se deu boa!!!!!!!!!!!!!!!!!!!!!!!!!!
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
	int TPB;

	/* Se herói estiver morto, ignora o evento */
	if (!m->herois[in->heroi].vivo)
		return;

	m->neventos++;

	/* Calcula tempo de permanência na base (TPM) */
	TPB = 15 + m->herois[in->heroi].paciencia * aleatorio(1, 20);

	cria_evento_sai(m, in->heroi, in->base, in->tempo + TPB);

	printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n",
		in->tempo, in->heroi, in->base, cjto_card(m->bases[in->base].presentes),
		m->bases[in->base].lotacao, in->tempo + TPB); //T: verificar esse tempo!!!!
}

/*O herói H sai da base B. Ao sair, escolhe uma base de destino para viajar; o
porteiro de B é avisado, pois uma vaga foi liberada*/
void evento_sai(struct Mundo *m, struct sai *s)
{
	int destino; 
	//Q: int status;????!!!!!!!!!!!!!!!!!!

	/* Se herói estiver morto, ignora o evento */
	if (!m->herois[s->heroi].vivo)
		return;

	m->neventos++;

	/*status = */ cjto_retira(m->bases[s->base].presentes, s->heroi);

	//Q: if (status == -1) ????!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	destino = aleatorio(0, m->nbases-1); /* Escolhe uma base aleatória */

	cria_evento_viaja(m, s->heroi, destino, s->tempo);

	cria_evento_avisa(m, s->base, s->tempo);

	printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n",
			s->tempo, s->heroi, s->base, cjto_card(m->bases[s->base].presentes), m->bases[s->base].lotacao);
}

//Q: qual o sentido disso?????!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
/*O herói H se desloca para uma base D (que pode ser a mesma onde já está)*/
void evento_viaja(struct Mundo *m, struct viaja *v)
{
	int distancia, duracao;

	/* Se herói estiver morto, ignora o evento */
	if (!m->herois[v->heroi].vivo)
		return;

	m->neventos++;

	/* Cálculo da distância e da duração */
	//T: modular distância!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	distancia = (int) sqrt((double)(pow((m->bases[v->destino].local.x - m->bases[m->herois[v->heroi].base].local.x), 2)
	 						+ pow((m->bases[v->destino].local.y - m->bases[m->herois[v->heroi].base].local.y), 2)));

	duracao = distancia / m->herois[v->heroi].velocidade; //Q: arredondar para cima?? -> viagens instantâneas

	cria_evento_chega(m, v->heroi, v->destino, v->tempo + duracao);

	printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",
			v->tempo, v->heroi, m->herois[v->heroi].base, v->destino, 
			distancia, m->herois[v->heroi].velocidade, v->tempo + duracao); //T: verficar se é esse tempo mesmo
}

//Q: Decrementar número de heróis!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*O herói H morre no instante T.*/
void evento_morre(struct Mundo *m, struct morre *mo)
{
	/* Se herói estiver morto, ignora o evento */
	if (!m->herois[mo->heroi].vivo) //Q: Será??!!!!!!!!!!!!!!!!!!!!!!!!!!
		return;

	m->neventos++;

	cjto_retira(m->bases[mo->base].presentes, mo->heroi); /* Retira herói da base em que se encontra */
	
	m->herois[mo->heroi].vivo = 0; 	/* Muda status do herói */

	cria_evento_avisa(m, mo->base, mo->tempo);

	printf("%6d: MORRE HEROI %2d MISSAO %d\n", mo->tempo, mo->heroi, 0);
}

//T: verificar aterramentos
//T: manipulação de ponteiro de bases e etc!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//T: verificar se eu usei acesso por mundo inves de por base!!!!!!!!!!!!!!!!!!!!
/*Uma missão M é disparada no instante T*/
void evento_missao(struct Mundo *m, struct Missao *M) //Q: Manter esse m maiusculo????!!!!!!!!!!!!!!
{
	struct cjto_t *habilidades_base = NULL;
	int distancia_missao[NBASES]; /* Cria vetor ordenado pela distância */
	int i, j;
	int id_primeira; 
	int id_base = -1;
	int escolhido = -1;
	int xp_atual;
	int BMP;

	M->tentativas++;

	m->neventos++; //Q: prorrogar evento conta como novo???!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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
		/* Guarda em id_base o id da base atual de verificação*/
		id_base = distancia_missao[i];

		if (habilidades_base)
        	cjto_destroi(habilidades_base);

		/* Criação do conjunto de habilidades da base retirada*/
		habilidades_base = cjto_cria(m->nhabilidades);

		for (j = 0; j < NHEROIS; j++)
		{
			/* Se o herói j pertecente a base da vez, então suas habilidades são unidas as da base*/
			if (cjto_pertence(m->bases[id_base].presentes, j))
			{
				printf("%6d: MISSAO %d HAB HEROI %2d: [ ", M->tempo, M->id, j);
				cjto_imprime(m->herois[j].habilidades);
				printf(" ]\n");

				habilidades_base = uniao_habilidades(habilidades_base, m->herois[j].habilidades);

				printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ", M->tempo, M->id, id_base);
				cjto_imprime(habilidades_base);
				printf(" ]\n");
			}
		}

		//Q: guardar a primeira base aqui??!!!!!!!!!!!!!!!!!!!!!!!!! 

		/* Verifica se as habilidades da missão estão contidas no conjunto de habilidades da base*/
		if (cjto_contem(habilidades_base, M->habilidades_m))
			BMP = 1; /* Base é marcada como BMP (o id dela está na variável id_base) */
		//else
		//	habilidades_base = cjto_destroi(habilidades_base);

		i++;
	}

	/* Se existe base cujos heróis conseguem cumprir a missão: */
	//id dessa base está salvo
	if (BMP)
	{
		//Q: assim que marca como cumprida????!!!!!!!!!!!!!!!!!!!1
		m->ncumpridas++;

		m->bases[id_base].num_missoes++;

		printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", M->tempo, M->id, id_base);
		cjto_imprime(habilidades_base);
		printf(" ]\n");

		for (i = 0; i < NHEROIS; i++)
			/* Se o herói pertecente a base, então sua experiência aumenta*/
			if (cjto_pertence(m->bases[id_base].presentes, i))
				m->herois[i].xp++;

		habilidades_base = cjto_destroi(habilidades_base);

		return;
	}

	/* Se não, verifica se é possível usar composto V*/
	if (m->ncompostos != 0 && M->tempo % 2500 == 0)
	{
		/* Procura e guarda a base não vazia mais próxima em id_primeira */
		id_primeira = 0;
		while (id_primeira < m->nbases && cjto_card(m->bases[distancia_missao[id_primeira]].presentes) == 0)
			id_primeira++;

		//T: Verificar se faz sentido esse caso!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		/* Se não tem nenhum herói em nenhuma base, adia evento missão*/
		if (id_primeira == m->nbases)
		{
			printf("%6d: MISSAO %d IMPOSSIVEL\n", M->tempo, M->id);
			M->tempo = M->tempo + 1440;
			fprio_insere(m->LEF, M, MISSAO, M->tempo);

			return;
		}

		m->ncompostos--;

		//Q: assim que marca como cumprida????!!!!!!!!!!!!!!!!!!!1
		m->ncumpridas++;

		m->bases[id_primeira].num_missoes++;

		//T: tirar acho
		if (habilidades_base)
        	cjto_destroi(habilidades_base);

		//Q: Tá bom essa criação do conjunto??!!!!!!!!!!!!!!!!!!!!!!!!!!!
		/* Criação do conjunto de habilidades da base mais próxima mais as habilidades do herói com composto V */
		habilidades_base = cjto_cria(m->nhabilidades);

		//Q: isso tá com cara de gambiarra!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		xp_atual = -1;	/* Variável para buscar maior xp */

		/* Laço que une habilidades da base, busca herói com maior xp e aumenta o xp dos demais heróis */
		for (i = 0; i < NHEROIS; i++)
		{
			if (cjto_pertence(m->bases[id_primeira].presentes, i))
			{
				/* Une habilidades */
				habilidades_base = uniao_habilidades(habilidades_base, m->herois[i].habilidades);

				/* Procura herói mais experiente */
				if (m->herois[i].xp > xp_atual)
				{
					xp_atual = m->herois[i].xp;
					escolhido = i;
				}

				/* Aumenta XP */
				m->herois[i].xp++;
			}
		}
		
		/* Adiciona ao conjunto de habilidades da base as habilidades da missão (poder do composto V) */
		habilidades_base = uniao_habilidades(habilidades_base, M->habilidades_m); //tem que fazer isso??!!!!!!!!!!!!!!!!

		printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", M->tempo, M->id, id_primeira);
		cjto_imprime(habilidades_base);
		printf(" ]\n");

		habilidades_base = cjto_destroi(habilidades_base);

		cria_evento_morre(m, escolhido, m->herois[escolhido].base, M->tempo);
		
		return;
	}

	//T: tirar acho
	if (habilidades_base)
        cjto_destroi(habilidades_base);

	/* Se não, adia missão por 1 dia*/
	printf("%6d: MISSAO %d IMPOSSIVEL\n", M->tempo, M->id);
	M->tempo = M->tempo + 1440;
	fprio_insere(m->LEF, M, MISSAO, M->tempo);
}

/* Encerra a simulação no instante T e apresenta as estatísticas */
void evento_fim(struct Mundo *m, struct fim *f)
{
	int max_tentativas, min_tentativas, total_tentativas;
	int total_mortos;
	int i;

	printf("%6d: FIM\n", f->tempo);

	total_mortos = 0;
	for (i = 0; i < NHEROIS; i++)
		if (m->herois[i].vivo) //Q: Existe uma forma melhor ou é esse if else mesmo???!!!!!!!!!!!!!!!!!!!!!!!
		{
			printf("HEROI %2d VIVO PAC %3d VEL %4d EXP %4d HABS [ ",
					i, m->herois[i].paciencia, m->herois[i].velocidade, m->herois[i].xp);
			
			cjto_imprime(m->herois[i].habilidades);
			printf(" ]\n");
		}
		else
		{
			printf("HEROI %2d MORTO PAC %3d VEL %4d EXP %4d HABS [ ",
					i, m->herois[i].paciencia, m->herois[i].velocidade, m->herois[i].xp);
			
			cjto_imprime(m->herois[i].habilidades);
			printf(" ]\n");

			total_mortos++;
		}
	
	for (i = 0; i < m->nbases; i++)
		printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n",
				i, m->bases[i].lotacao, m->bases[i].fila_max, m->bases[i].num_missoes); //Q: pode add campos???!!!!!!!!!!!!!!!!!!!!!!!!
	
	//Q: pode add campos???!!!!!!!!!!!!!!!!!!!
	printf("EVENTOS TRATADOS: %d\n", m->neventos);

	//Q: pode add campos???!!!!!!!!!!!!!!!!
	printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", m->ncumpridas, m->nmissoes, (double)m->ncumpridas/m->nmissoes); //Q: piso,teto, ....???!!!!!!

	//Q: Dá boa essa inicialização???!!!!!!!!!!!!!!!!
	max_tentativas = m->missoes[0]->tentativas;
	min_tentativas = m->missoes[0]->tentativas;
	total_tentativas = m->missoes[0]->tentativas;
	for (i = 1; i < m->nmissoes; i++)
	{
		if (m->missoes[i]->tentativas > max_tentativas)
			max_tentativas = m->missoes[i]->tentativas;
		else if (m->missoes[i]->tentativas < min_tentativas)
			min_tentativas = m->missoes[i]->tentativas;
		
		total_tentativas = total_tentativas + m->missoes[i]->tentativas;
	}
	
	printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n",
			min_tentativas, max_tentativas, (double)total_tentativas/m->nmissoes); //Q: média com piso,teto, ....???!!!!!!

	printf("TAXA MORTALIDADE: %.1f%%\n", (double)total_mortos/NHEROIS); //Q: média com piso,teto, ....???!!!!!!
}