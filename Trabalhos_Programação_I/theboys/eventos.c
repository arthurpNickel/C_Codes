/* Implementação dos eventos */

#include "eventos.h"
#include <stdio.h>
#include <stdlib.h>

//cria dentro ou fora do evento os eventos???

/*Herói h chegando na base b no instante t. Ao chegar, o
herói analisa o tamanho da fila e decide se espera para entrar ou desiste*/
void evento_chega(struct Mundo *m, struct chega *c)
{
	int espera;
	struct espera *e;
	struct desiste *d;

	//função específica???!!!!!!!!!!!!!!!!!!!!!!!!!!
	printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ", c->tempo, c->heroi, c->base, 
			lista_tamanho(m->bases[c->base].fila_espera), m->bases[c->base].lotacao);

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
}

/* O herói H entra na fila de espera da base B. Assim que H entrar na fila, o
porteiro da base B deve ser avisado para verificar a fila: */
void evento_espera(struct Mundo *m, struct espera *e)
{
	struct avisa *a;

	printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", e->tempo, e->heroi, e->base, 
			lista_tamanho(m->bases[e->base].fila_espera));
	
	//É esse o item mesmo????
	//verificar se é fila ou lista!!!!!!!!!!!!!!!!!!!!!!!!
	lista_insere_fim(m->bases[e->base].fila_espera, e->heroi); //algum caso de erro???!!!!!!!!

	/* Cria evento avisa e insere na LEF */
	if (!(a = malloc(sizeof(struct avisa))))
		return;
	a->tempo = e->tempo;
	a->base = e->base;

	fprio_insere(m->LEF, a, AVISA, a->tempo);
}

/*O herói H desiste de entrar na base B, escolhe uma base aleatória D e viaja
para lá:*/
void evento_desiste(struct Mundo *m, struct espera *d)
{
	struct viaja *v;
	int destino; //precisa?!!!!!!!!!!!!!!!!!!!!!!!!!!

	printf("%6d: DESISTE HEROI %2d BASE %d\n", d->tempo, d->heroi, d->base);

	destino = rand() % m->nbases; /* Escolhe uma base aleatória */

	/* Cria evento viaja e insere na LEF */
	if(!(v = malloc(sizeof(struct viaja))))
		return;
	v->tempo = d->tempo;
	v->heroi = d->heroi;
	v->destino = destino; //pode colocar direto o rand aqui!!!!!!!!!!!!!!!!!!!!!!!!!!

	fprio_insere(m->LEF, v, VIAJA, v->tempo);
}

/* O porteiro da base B trata a fila de espera: */
void evento_avisa(struct Mundo *m, struct avisa *a)
{
	struct entra *in;
	int h;
	
	//como vou fazer essa porra????
	/*printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ %2d %2d ... ]")*/

	//m->bases[a->base].lotacao ou m->bases[a->base].presentes->cap???!!!!!!!!!!!!!!!!!!!!!!!
	while (m->bases[a->base].lotacao > m->bases[a->base].presentes->num && lista_tamanho(m->bases[a->base].fila_espera) != 0)
	{
		//verificar se é fila mesmo!!!!!!!!!!!!!!!!!!!!!!
		lista_remove_inicio(m->bases[a->base].fila_espera, &h);
		cjto_insere(m->bases[a->base].presentes, h);

		printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", a->tempo, a->base, h);

		/* Cria evento entra e insere na LEF */
		if(!(in = malloc(sizeof(struct entra))))
			return;
		in->tempo = a->tempo;
		in->heroi = h;
		in->base = a->base;

		fprio_insere(m->LEF, in, ENTRA, in->tempo);
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

	//vão todos no final então?!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", in->tempo, in->heroi, in->base,
			lista_tamanho(m->bases[in->base].fila_espera), m->bases[in->base].lotacao, s->tempo);
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

	printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", s->tempo, s->heroi, s->base,
			m->bases[s->base].presentes->num, m->bases[s->base].lotacao);
}


