#include "destruicao.h"

void destroi_bases(Tp_Mundo *m)
{
	int i;

	for (i = 0; i < m->nbases; i++)
	{
		m->bases[i].presentes = cjto_destroi(m->bases[i].presentes);
		m->bases[i].fila_espera = fila_destroi(m->bases[i].fila_espera);
	}
}

void destroi_missoes(Tp_Mundo *m)
{
	int i;

	for (i = 0; i < m->nmissoes; i++)
	{
		cjto_destroi(m->missoes[i]->habilidades_m);

        //Q: < ou <=???!!!!!!!!!!!!!!!!!!!!!!!!
		/* Se evento foi cumprido, ele não está na LEF, portando tem que ser liberado */
		if (m->missoes[i]->tempo < FIMMUNDO)
			free(m->missoes[i]);
	}

	free(m->missoes);
}

void destroi_herois(Tp_Mundo *m)
{
	int i;

	for (i = 0; i < NHEROIS; i++)
		m->herois[i].habilidades = cjto_destroi(m->herois[i].habilidades);
}

void destroi_lef(Tp_Mundo *m)
{
	m->LEF = fprio_destroi(m->LEF);
}
