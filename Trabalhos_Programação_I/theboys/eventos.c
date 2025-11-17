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

	//acesso de mundo errado!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	m->herois[c->heroi].base = c->base; /* Muda ID da base que herói se encontra no momento*/

	if (m->bases[c->base].fila_espera->num < m->bases[c->base].lotacao && //precisa dessa primeira verificação???!!!!!!!!!!!!!!!!!!!!!!
		m->bases[c->base].fila_espera->num == 0)
		espera = 1;

	else //return? !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		espera =  m->herois[c->heroi].paciencia > 10 * m->bases[c->base].fila_espera->num;
    
    if (espera)
    {
		printf("ESPERA\n");

        /* Cria evento espera e insere na LEF*/
		if(!(e = malloc(sizeof(struct espera))))
			return;
		e->tempo = c->tempo;
		e->heroi = c->heroi;
		e->base = c->base;
        
		fprio_insere(m->LEF, e, ESPERA, e->tempo);

		return;
    }

	printf("DESISTE\n");
	
	/* Cria evento desiste e insere na LEF*/
	if(!(d = malloc(sizeof(struct desiste))))
		return;
	d->tempo = c->tempo;
	d->heroi = c->heroi;
	d->base = c->base;
	
	fprio_insere(m->LEF, d, DESISTE, d->tempo);
}

/*

/ O herói H entra na fila de espera da base B. Assim que H entrar na fila, o
porteiro da base B deve ser avisado para verificar a fila: /
void evento_espera(struct Mundo *m, struct espera *e)
{
	fila_insere(mundo.bases[e->base].fila_espera); //algum caso de erro???!!!!!!!!

}

/ O porteiro da base B trata a fila de espera: /
void evento_avisa(struct Mundo *m, struct avisa *a);

*/
