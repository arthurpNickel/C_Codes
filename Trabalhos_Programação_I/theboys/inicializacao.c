#include "inicializacao.h"

void inicializa_mundo(Tp_Mundo *m)
{
	m->relogio = 0;
	m->tam_mundo.x = TAMMUNDO;
	m->tam_mundo.y = TAMMUNDO;
	m->nhabilidades = NHABILIDADES;
	m->nherois = NHEROIS;
	m->nbases = NBASES;
	m->nmissoes = NMISSOES;
	m->ncompostos = NCOMPOSTOS;
	m->ncumpridas = 0;
	m->neventos = 0;
	m->LEF = fprio_cria(); /* LEF é uma fila de prioridade, com prioridade = tempo */
}

void inicializa_herois(Tp_Mundo *m)
{
	int i;

	for (i = 0; i < m->nherois; i++)
	{
		m->herois[i].id = i;
		m->herois[i].xp = 0;
		m->herois[i].vivo = 1;
		m->herois[i].paciencia = aleatorio(0, 100);
		m->herois[i].velocidade = aleatorio(50, 5000);
        /* Cada heroi terá uma quantidade aleatória de habilidadades, também aleatórias */
		m->herois[i].habilidades = cjto_aleat(aleatorio(1, 3), m->nhabilidades);
	}
}

void inicializa_bases(Tp_Mundo *m)
{
	int i;

	for (i = 0; i < m->nbases; i++)
	{
		m->bases[i].id = i;
		m->bases[i].local.x = aleatorio(0, m->tam_mundo.x - 1);
		m->bases[i].local.y = aleatorio(0, m->tam_mundo.y - 1);
		m->bases[i].lotacao = aleatorio(3, 10);
		m->bases[i].fila_max = 0;
		m->bases[i].num_missoes = 0;

		m->bases[i].presentes = cjto_cria(m->nbases);
		m->bases[i].fila_espera = fila_cria();
	}
}

void inicializa_missoes(Tp_Mundo *m)
{
	int i;

    m->missoes = malloc(sizeof(Tp_Missao) * m->nmissoes);

	for (i = 0; i < m->nmissoes; i++)
	{
        m->missoes[i] = malloc(sizeof(Tp_Missao));
        m->missoes[i]->id = i;
        m->missoes[i]->tentativas = 0;
        m->missoes[i]->local.x = aleatorio(0, m->tam_mundo.x - 1);
        m->missoes[i]->local.y = aleatorio(0, m->tam_mundo.y - 1);
        m->missoes[i]->habilidades_m = cjto_aleat(aleatorio(6, 10), m->nhabilidades);
	}
}

