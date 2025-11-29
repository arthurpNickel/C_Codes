#include "auxiliares.h"

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
void troca(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

/* Calcula distância entre 2 pontos */
int calcula_distancia(int x1, int y1, int x2, int y2) 
{
    return (int)round(sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
}

/* Calcula distância entre duas bases*/
int calcula_distancia_bases(Tp_Mundo *m, int b1, int b2)
{
	return calcula_distancia(
		m->bases[b1].local.x, m->bases[b1].local.y,
		m->bases[b2].local.x, m->bases[b2].local.y
	);
}

/* Calcula distância da missão até a base*/
int calcula_distancia_missao(Tp_Mundo *m, Tp_Missao *M, int id_base)
{
	return calcula_distancia(
		m->bases[id_base].local.x, m->bases[id_base].local.y,
		M->local.x, M->local.y
	);
}

/* Partição */
void Particao(Tp_Mundo *m, Tp_Missao *M, int v[], int ini, int fim, int *pos_pivo)
{
    int i = ini + 1, j = fim;
    int pospivo = ini;
    int pivo = calcula_distancia_missao(m, M, v[pospivo]);

    troca(&v[ini], &v[pospivo]);

    while (i < j)
    {
        while (i <= fim && calcula_distancia_missao(m, M, v[i]) <= pivo)
            i++;

        while (j > ini && calcula_distancia_missao(m, M, v[j]) > pivo)
            j--;

        if (i < j)
            troca(&v[i], &v[j]);
    }

    troca(&v[ini], &v[j]);
    *pos_pivo = j;
}

//usar static???!!!!!!!!!!!!!!!!!!!!!
/* QuickSort */
void QuickSort(Tp_Mundo *m, Tp_Missao *M, int v[], int ini, int fim)
{
    int pos_pivo;

    if (ini < fim)
    {
        Particao(m, M, v, ini, fim, &pos_pivo);
        QuickSort(m, M, v, ini, pos_pivo - 1);
        QuickSort(m, M, v, pos_pivo + 1, fim);
    }
}  