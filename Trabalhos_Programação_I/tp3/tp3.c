/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 09/09/2025 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

void imprime_v(struct racional *v[], int tam)
{
	int i;
	
	printf("VETOR = ");
	
	for (i = 0; i < tam-1; i++)
	{
		imprime_r(v[i]);
		printf(" ");
	}
	
	if (tam > 0)
		imprime_r(v[tam-1]);
	printf("\n");
}

/*troca endereços entre dois ponteiros de racionais*/
void troca_r(struct racional **a, struct racional **b)
{
	struct racional *aux = *a;
	*a = *b;
	*b = aux;
}

/*cada ponteiro do vetor de structs recebe um endereço para apontar, 
  com uma certa struct lida do teclado*/
void preenche_v(struct racional *v[], int tam)
{
	int i;
	long num, den;
	
	for (i = 0; i < tam; i++)
	{
		scanf("%ld %ld", &num, &den);
		v[i] = cria_r(num, den);
	}
}

/*elimina elementos inválidos do vetor, colocando todos os inválidos à direita*/
void elimina_v(struct racional *v[], int tam)
{
	int i = 0;
	int j = tam - 1;
	
	while (i < j) 
	{
		if (valido_r(v[i]))
        		i++; 
    		else if (!valido_r(v[j]))
        		j--;
    		else
    		{
        		/*manda os endereços para trocar*/
        		troca_r(&v[i], &v[j]);
        		i++;
        		j--;
    		}
	}
}

void particiona_v(struct racional *v[], int esq, int dir, int *pos_pivo)
{
	struct racional *pivo = v[esq];
	int i = esq + 1;
	int j = dir;
	
	while (1) 
	{
		while (i <= dir && compara_r(v[i], pivo) == -1) i++;        	

		while (j >= esq && compara_r(v[j], pivo) == 1) j--;

		if (i >= j) break;		

		troca_r(&v[i], &v[j]);
		i++;
		j--;
	}
	
	troca_r(&v[esq], &v[j]);
	*pos_pivo = j;
}

/*QuickSort implementado recursivamente, ordenando de forma crescente*/
void ordena_v(struct racional *v[], int esq, int dir)
{
	int pos_pivo;	
	
	if (esq < dir)
	{
		particiona_v(v, esq, dir, &pos_pivo);
		
		ordena_v(v, esq, pos_pivo-1);
		
		ordena_v(v, pos_pivo+1, dir);
	}
}

/*retorna a soma dos elementos de um vetor de racionais*/
void soma_v(struct racional *v[], struct racional **soma, int tam)
{
	int i;
	struct racional *nova, *antiga;
	
	for (i = 0; i < tam; i++) 
	{
		nova = cria_r(0, 1);

		soma_r(*soma, v[i], nova);
	
		/*passa acumulador para nova soma
		  e libera espaço do antigo acumulador*/
		antiga = *soma;
		*soma = nova;
		destroi_r(&antiga);
	}
}

void libera_v(struct racional *v[], int tam)
{
	int i;
	
	for (i = 0; i < tam; i++)
		destroi_r(&v[i]);
}

/* programa principal */
int main ()
{
	struct racional **v = NULL;
	struct racional *soma = NULL;
	int n;
	int novo_tam;
	
	/*lê tamanho e testa se é válido*/
	scanf("%d", &n);
	if ((n < 0) || (n > 100))
		return 1;
	
	if (!(v = malloc(sizeof(struct racional*)*n)))
		return 1;
	
	preenche_v(v, n);
	
	imprime_v(v, n);
	
	elimina_v(v, n);
	
	/*conta elementos válidos*/
	novo_tam = 0;
	while ((novo_tam < n) && valido_r(v[novo_tam])) novo_tam++;
	
	imprime_v(v, novo_tam);
	
	ordena_v(v, 0, novo_tam-1);
	
	imprime_v(v, novo_tam);
	
	/*inicializa soma zerada*/
	soma = cria_r(0, 1);
	
	soma_v(v, &soma, novo_tam);
	
	printf("SOMA = ");
	imprime_r(soma);
	printf("\n");
	
	libera_v(v, n);
	
	imprime_v(v, novo_tam);

	free(v);
	v = NULL;
	
	destroi_r(&soma);
	
	return 0;
}
