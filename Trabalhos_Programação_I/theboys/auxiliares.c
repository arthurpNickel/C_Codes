/* Implementação das funções auxiliares da simulação */


#include "auxiliares.h"


int aleatorio(int min, int max)
{
	return min + rand() % (max - min + 1);
}


struct cjto_t *uniao_habilidades(struct cjto_t *u, struct cjto_t *h)
{
    struct cjto_t *aux = cjto_uniao(u, h);
    cjto_destroi(u);
    return aux;
}


void troca(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

/*Calcula a distância cartesiana entre 2 pontos
 **/
int calcula_distancia(int x1, int y1, int x2, int y2) 
{
    return (int)round(sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
}


int calcula_distancia_bases(Tp_Mundo *m, int b1, int b2)
{
	return calcula_distancia(
		m->bases[b1].local.x, m->bases[b1].local.y,
		m->bases[b2].local.x, m->bases[b2].local.y
	);
}


int calcula_distancia_missao(Tp_Mundo *m, Tp_Missao *M, int id_base)
{
	return calcula_distancia(
		m->bases[id_base].local.x, m->bases[id_base].local.y,
		M->local.x, M->local.y
	);
}

/*Partição do vetor pelo método Lomuto
 **/
void particao(Tp_Mundo *m, Tp_Missao *M, int v[], int ini, int fim, int *pos_pivo)
{
    int pivo = calcula_distancia_missao(m, M, v[fim]);
    int i = ini - 1;

    for (int j = ini; j < fim; j++)
    {
        if (calcula_distancia_missao(m, M, v[j]) <= pivo)
        {
            i++;
            troca(&v[i], &v[j]);
        }
    }

    troca(&v[i + 1], &v[fim]);
    *pos_pivo = i + 1;
}


void quick_sort(Tp_Mundo *m, Tp_Missao *M, int v[], int ini, int fim)
{
    int pos_pivo;

    if (ini < fim)
    {
        particao(m, M, v, ini, fim, &pos_pivo);
        quick_sort(m, M, v, ini, pos_pivo - 1);
        quick_sort(m, M, v, pos_pivo + 1, fim);
    }
}  