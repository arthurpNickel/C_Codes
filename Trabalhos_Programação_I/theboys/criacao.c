#include "criacao.h"

//Q: Tá boa essa abordagem mais direta???!!!!!!!!!!!!!!!!!!!!!!!!!!
/* Eventos Iniciais */
void cria_eventos_iniciais(Tp_Mundo *m)
{
	int i;

	/* Cada herói chegará em alguma base aleatória dentro de 3 dias */
	for (i = 0; i < m->nherois; i++)
		cria_evento_chega(m, i, aleatorio(0, m->nbases - 1), aleatorio(0, 4320)); /* 4320 = 24*60*3 */

	/* Distribuição das missões na LEF */
	for (i = 0; i < m->nmissoes; i++)
	{
		m->missoes[i]->tempo = aleatorio(0, FIMMUNDO);
		fprio_insere(m->LEF, m->missoes[i], MISSAO,	m->missoes[i]->tempo);
	}

	/* Evento que finalizará o mundo */
	cria_evento_fim(m);
}

/* Cria evento chega e insere na LEF */
void cria_evento_chega(Tp_Mundo *m, int heroi, int base, int tempo)
{
	Tp_Chega *c = malloc(sizeof(Tp_Chega));

	c->heroi = heroi;
	c->base = base;
	c->tempo = tempo;

	fprio_insere(m->LEF, c, CHEGA, c->tempo);
}

/* Cria evento espera e insere na LEF */
void cria_evento_espera(Tp_Mundo *m, int heroi, int base, int tempo)
{
	Tp_Espera *e = malloc(sizeof(Tp_Espera));

	e->heroi = heroi;
	e->base = base;
	e->tempo = tempo;

	fprio_insere(m->LEF, e, ESPERA, e->tempo);
}

/* Cria evento desiste e insere na LEF */
void cria_evento_desiste(Tp_Mundo *m, int heroi, int base, int tempo)
{
	Tp_Desiste *d = malloc(sizeof(Tp_Desiste));

	d->heroi = heroi;
	d->base = base;
	d->tempo = tempo;

	fprio_insere(m->LEF, d, DESISTE, d->tempo);
}

/* Cria evento avisa e insere na LEF */
void cria_evento_avisa(Tp_Mundo *m, int base, int tempo)
{
	Tp_Avisa *a = malloc(sizeof(Tp_Avisa));

	a->base = base;
	a->tempo = tempo;

	fprio_insere(m->LEF, a, AVISA, a->tempo);
}

/* Cria evento viaja e insere na LEF */
void cria_evento_viaja(Tp_Mundo *m, int heroi, int destino, int tempo)
{
	Tp_Viaja *v = malloc(sizeof(Tp_Viaja));

	v->heroi = heroi;
	v->destino = destino;
	v->tempo = tempo;

	fprio_insere(m->LEF, v, VIAJA, v->tempo);
}

/* Cria evento sai e insere na LEF */
void cria_evento_sai(Tp_Mundo *m, int heroi, int base, int tempo)
{
	Tp_Sai *s = malloc(sizeof(Tp_Sai));

	s->heroi = heroi;
	s->base = base;
	s->tempo = tempo;

	fprio_insere(m->LEF, s, SAI, s->tempo);
}

/* Cria evento entra e insere na LEF */
void cria_evento_entra(Tp_Mundo *m, int heroi, int base, int tempo)
{
	Tp_Entra *in = malloc(sizeof(Tp_Entra));

	in->heroi = heroi;
	in->base = base;
	in->tempo = tempo;

	fprio_insere(m->LEF, in, ENTRA, in->tempo);
}

/* Cria evento morre e insere na LEF */
void cria_evento_morre(Tp_Mundo *m, int heroi, int base, int tempo)
{
	Tp_Morre *mr = malloc(sizeof(Tp_Morre));

	mr->base = base;
	mr->heroi = heroi;
	mr->tempo = tempo;

	fprio_insere(m->LEF, mr, MORRE, mr->tempo);
}

/* Cria evento fim e insere na LEF */
void cria_evento_fim(Tp_Mundo *m)
{
	Tp_Fim *f = malloc(sizeof(Tp_Fim));

	f->tempo = FIMMUNDO;

	fprio_insere(m->LEF, f, FIM, f->tempo);
}