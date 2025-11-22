/* Implementação dos eventos */

#include "eventos.h"

/*Herói h chegando na base b no instante t. Ao chegar, o
herói analisa o tamanho da fila e decide se espera para entrar ou desiste*/
void evento_chega(struct Mundo *m, struct chega *c)
{
	int espera;
	struct espera *e;
	struct desiste *d;

	m->herois[c->heroi].base = c->base; /* Muda ID da base que herói se encontra no momento*/

	if (lista_tamanho(m->bases[c->base].fila_espera) < m->bases[c->base].lotacao && //precisa dessa primeira verificação???!!!!!!!!!!!!!!!!!!!!!!
		lista_tamanho(m->bases[c->base].fila_espera) == 0)
		espera = 1;

	else //return? !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		espera =  m->herois[c->heroi].paciencia > 10 * lista_tamanho(m->bases[c->base].fila_espera);
    
    if (espera)
    {
		printf("ESPERA\n");

		//modular?!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        /* Cria evento espera e insere na LEF (mesmos atributos do evento chega) */
		if(!(e = malloc(sizeof(struct espera))))
			return;
		e->tempo = c->tempo;
		e->heroi = c->heroi;
		e->base = c->base;
        
		fprio_insere(m->LEF, e, ESPERA, e->tempo);

		return;
    }

	printf("DESISTE\n");
	
	/* Cria evento desiste e insere na LEF (mesmos atributos do evento chega) */
	if(!(d = malloc(sizeof(struct desiste))))
		return;
	d->tempo = c->tempo;
	d->heroi = c->heroi;
	d->base = c->base;
	
	fprio_insere(m->LEF, d, DESISTE, d->tempo);

	printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ",
		c->tempo, c->heroi, c->base, lista_tamanho(m->bases[c->base].fila_espera), m->bases[c->base].lotacao);
}

/* O herói H entra na fila de espera da base B. Assim que H entrar na fila, o
porteiro da base B deve ser avisado para verificar a fila: */
void evento_espera(struct Mundo *m, struct espera *e)
{
	struct avisa *a;
	
	//verificar se é fila ou lista!!!!!!!!!!!!!!!!!!!!!!!!
	lista_insere_fim(m->bases[e->base].fila_espera, e->heroi); //algum caso de erro???!!!!!!!!

	/* Cria evento avisa e insere na LEF */
	if (!(a = malloc(sizeof(struct avisa))))
		return;
	a->tempo = e->tempo;
	a->base = e->base;

	fprio_insere(m->LEF, a, AVISA, a->tempo);

	printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",
			e->tempo, e->heroi, e->base, lista_tamanho(m->bases[e->base].fila_espera));
}

/*O herói H desiste de entrar na base B, escolhe uma base aleatória D e viaja
para lá*/
void evento_desiste(struct Mundo *m, struct espera *d)
{
	struct viaja *v;
	int destino; //precisa?!!!!!!!!!!!!!!!!!!!!!!!!!!

	destino = rand() % m->nbases; /* Escolhe uma base aleatória */

	/* Cria evento viaja e insere na LEF */
	if(!(v = malloc(sizeof(struct viaja))))
		return;
	v->tempo = d->tempo;
	v->heroi = d->heroi;
	v->destino = destino; //pode colocar direto o rand aqui!!!!!!!!!!!!!!!!!!!!!!!!!!

	fprio_insere(m->LEF, v, VIAJA, v->tempo);

	printf("%6d: DESISTE HEROI %2d BASE %d\n",
			d->tempo, d->heroi, d->base);

}

/* O porteiro da base B trata a fila de espera: */
void evento_avisa(struct Mundo *m, struct avisa *a)
{
	struct entra *in;
	int h;
	
	printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", 
			a->tempo, a->base, lista_tamanho(m->bases[a->base].fila_espera), m->bases[a->base].lotacao);
			//FILA [ %2d %2d  ]"
	
	//modular?!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/*------------Impressão da fila de espera-------------*/
	if (lista_vazia(m->bases[a->base].fila_espera))
	{
		printf ("]\n");
		return;
	}
	
	lista_inicia_iterador(m->bases[a->base].fila_espera);

	lista_incrementa_iterador (m->bases[a->base].fila_espera, &h);
	printf ("%d", h);
	while (lista_incrementa_iterador(m->bases[a->base].fila_espera, &h))
		printf (" %d", h);
	printf (" ]\n");
	/*----------------------------------------------------*/

	//m->bases[a->base].lotacao ou m->bases[a->base].presentes->cap???!!!!!!!!!!!!!!!!!!!!!!!
	while (m->bases[a->base].lotacao > m->bases[a->base].presentes->num 
			&& lista_tamanho(m->bases[a->base].fila_espera) != 0)
	{
		//verificar se é fila mesmo!!!!!!!!!!!!!!!!!!!!!!
		lista_remove_inicio(m->bases[a->base].fila_espera, &h);
		cjto_insere(m->bases[a->base].presentes, h);

		/* Cria evento entra e insere na LEF */
		if(!(in = malloc(sizeof(struct entra))))
			return;
		in->tempo = a->tempo;
		in->heroi = h;
		in->base = a->base;

		fprio_insere(m->LEF, in, ENTRA, in->tempo);

		printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n",
				a->tempo, a->base, h);
	}
}

/*O herói H entra na base B. Ao entrar, o herói decide quanto tempo vai ficar e
agenda sua saída da base*/
void evento_entra(struct Mundo *m, struct entra *in)
{
	struct sai *s;
	int TPB = 15 + m->herois[in->heroi].paciencia * (1 + rand() % 20); //1 a 20

	/* Cria evento sai e insere na LEF */
	if(!(s = malloc(sizeof(struct entra))))
		return;
	s->tempo = in->tempo + TPB;
	s->heroi = in->heroi;
	s->base = in->base;

	fprio_insere(m->LEF, s, SAI, s->tempo);

	printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n",
		in->tempo, in->heroi, in->base, lista_tamanho(m->bases[in->base].fila_espera),
		m->bases[in->base].lotacao, s->tempo);
}

/*O herói H sai da base B. Ao sair, escolhe uma base de destino para viajar; o
porteiro de B é avisado, pois uma vaga foi liberada*/
void evento_sai(struct Mundo *m, struct sai *s)
{
	struct viaja *v;
	struct avisa *a;
	int destino, status;

	status = cjto_retira(m->bases[s->base].presentes, s->heroi);

	//if (status == -1) ????!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	destino = rand() % m->nbases; /* Escolhe uma base aleatória */

	/* Cria evento viaja e insere na LEF */
	if(!(v = malloc(sizeof(struct viaja))))
		return;
	v->tempo = s->tempo;
	v->heroi = s->heroi;
	v->destino = destino;

	fprio_insere(m->LEF, v, VIAJA, v->tempo);

	/* Cria evento avisa e insere na LEF */
	if (!(a = malloc(sizeof(struct avisa))))
		return;
	a->tempo = s->tempo;
	a->base = s->base;

	fprio_insere(m->LEF, a, AVISA, a->tempo);

	printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n",
			s->tempo, s->heroi, s->base, m->bases[s->base].presentes->num, m->bases[s->base].lotacao);
}

//qual o sentido disso?????!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
/*O herói H se desloca para uma base D (que pode ser a mesma onde já está)*/
void evento_viaja(struct Mundo *m, struct viaja *v)
{
	struct chega *c;
	int distancia, duracao;

	/* Cálculo da distância e da duração */
	//modular distância??!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//Ta errado esse cálculo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	distancia = sqrt(pow(m->herois[v->heroi].base, 2) + pow(v->destino, 2));

	duracao = distancia / m->herois[v->heroi].velocidade;

	/* Cria evento chega e insere na LEF */
	if(!(c = malloc(sizeof(struct chega))))
		return;
	c->tempo = v->tempo + duracao;
	c->heroi = v->heroi;
	c->base = v->destino;

	fprio_insere(m->LEF, c, CHEGA, c->tempo);

	printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",
			v->tempo, v->heroi, m->herois[v->heroi].base, v->destino, 
			distancia, m->herois[v->heroi].velocidade, c->tempo);
}

//Decrementar número de heróis!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*O herói H morre no instante T.*/
void evento_morre(struct Mundo *m, struct morre *mo)
{
	struct avisa *a;

	cjto_retira(m->bases[mo->base].presentes, mo->heroi); /* Retira herói da base em que se encontra */

	//Como mudo status do herói??!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/* Cria evento avisa e insere na LEF */
	if (!(a = malloc(sizeof(struct avisa))))
		return;
	a->tempo = mo->tempo;
	a->base = mo->base;

	fprio_insere(m->LEF, a, AVISA, a->tempo);

	printf("%6d: MORRE HEROI %2d MISSAO %d\n", mo->tempo, mo->heroi, 0);
}

/*Uma missão M é disparada no instante T*/
void evento_missao(struct Mundo *m, struct Missao *M) //Manter esse m maiusculo????!!!!!!!!!!!!!!
{
	struct fprio_t *distancia_bases;
	struct cjto_t *habilidades_base;
	int i, distancia, BMP, b, primeira, id; //!!
	void *primeira, *base; //!!

	/* Calcula a distância de cada base ao local da missão e insere em uma fila, ordenada pela distancia */
	for (i = 0; i < m->nbases; i++)
	{
		//modular distância??!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		distancia = sqrt(pow(m->bases[i].local.x - M->local.x, 2) + pow(m->bases[i].local.y - M->local.y, 2));		
		fprio_insere(distancia_bases, &m->bases[i], i, distancia);
	}

	/* Guarda base mais próxima - Caso precise usar composto V*/
	primeira = fprio_retira(distancia_bases, &id ,&distancia); //isso é gambiarra??!!!!!!!!!!!!!!1
	fprio_insere(distancia_bases, &m->bases[primeira], id, distancia);

	//testar se base tem herói???!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//add na fila apenas as que tem herói

	/* Verifica se existe alguma base com todas as habilidades necessárias para a missão */
	lista_inicia_iterador(distancia_bases);
	while (lista_incrementa_iterador(distancia_bases, &b))
	{
		base = fprio_retira(distancia_bases, &id, &distancia);
		
		//Como acesso todos os heróis da base para unir habilidades??!!!!!!!!!!!!!!!!!!!!!!

	}
}