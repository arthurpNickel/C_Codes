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
			m->bases[c->base].fila_espera->num, m->bases[c->base].lotacao);

	m->herois[c->heroi].base = c->base; /* Muda ID da base que herói se encontra no momento*/

	if (m->bases[c->base].fila_espera->num < m->bases[c->base].lotacao && //precisa dessa primeira verificação???!!!!!!!!!!!!!!!!!!!!!!
		m->bases[c->base].fila_espera->num == 0)
		espera = 1;

	else //return? !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		espera =  m->herois[c->heroi].paciencia > 10 * m->bases[c->base].fila_espera->num;
    
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
			m->bases[e->base].fila_espera->num);
	
	//É esse o item mesmo????
	//verificar se é fila ou lista!!!!!!!!!!!!!!!!!!!!!!!!
	fila_insere(m->bases[e->base].fila_espera, e->heroi); //algum caso de erro???!!!!!!!!

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

	destino = rand() % (m->nbases); /* Escolhe uma base aleatória */

}

/* O porteiro da base B trata a fila de espera: */
void evento_avisa(struct Mundo *m, struct avisa *a)
{
	struct entra *in;
	int h;
	
	//como vou fazer essa porra????
	/*printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ %2d %2d ... ]")*/

	//m->bases[a->base].lotacao ou m->bases[a->base].presentes->cap???!!!!!!!!!!!!!!!!!!!!!!!
	while (m->bases[a->base].lotacao > m->bases[a->base].presentes->num && m->bases[a->base].fila_espera->num != 0)
	{
		//verificar se é fila mesmo!!!!!!!!!!!!!!!!!!!!!!
		fila_retira(m->bases[a->base].fila_espera, &h);
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


