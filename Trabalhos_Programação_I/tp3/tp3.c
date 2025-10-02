/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 09/09/2025 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* coloque aqui as funções auxiliares que precisar neste arquivo */

/*imprime vetor de racionais*/
void imprime_v(struct racional *v[], int tam)
{
	printf("VETOR = ");
	int i;
	for (i = 0; i < tam; i++)
	{
		if (i > 0)
			printf(" ");
		imprime_r(v[i]);
	}
	printf("\n");
}

/*Entender porque isso dá certo*/

/*troca endereços entre dois ponteiros de racionais*/
void troca_r(struct racional **a, struct racional **b)
/* a = endereço do rótulo do vetor
  *a = ponteiro que aponta para conteúdo do rótulo do vetor (endereço do racional
  **a = ponteiro de ponteiro, que aponta para o racional em si que se quer guardar*/
{
	struct racional *aux = *a;
	*a = *b;
	*b = aux;
}

/*elimina elementos inválidos do vetor, colocando todos os inválidos à direita*/
void elimina_v(struct racional *v[], int tam)
{
	int i = 0;
	int j = tam - 1;
	
	while (i <= j) 
	{
		if (valido_r(v[i]))
        		i++; 
    		else if (!valido_r(v[j]))
        		j--;
    		else
    		{
        		troca_r(&v[i], &v[j]);
        		i++;
        		j--;
    		}
	}
}

void particiona_v(*v[], )
{
	int i = esq;
	int j = dir;
	int aux;
	
	while (i < j)
	{
		while ()
	}
}

/*QuickSort implementado recursivamente, ordenando de forma crescente*/
void ordena_v(struct racional *v[], esq, dir)
{
	int pos_pivo;		
	
	if (esq < dir)
	{
		particiona_v();
		
		ordena_v(v, esq, pos_pivo-1);
		
		ordena_v(v, pos_pivo+1, dir);
	}
}

/* programa principal */
int main ()
{
	/*lê tamanho e testa se é válido*/
	int n;
	scanf("%d", &n);
	
	if ((n < 0) || (n > 100))
		return 1;
	
	/*cria ponteiro para o primeiro elemento do vetor (que é um ponteiro)*/
	struct racional **v;
	
	/*aloca n espaços para o ponteiro para ponteiro v e testa*/
	if (!(v = malloc(sizeof(struct racional*)*n)))
		return 1;
	
	/*cada ponteiro do vetor de structs recebe um endereço para apontar, com uma certa struct*/
	int i;
	long num, den;
	for (i = 0; i < n; i++)
	{
		scanf("%ld %ld", &num, &den);
		v[i] = cria_r(num, den);
	}
	
	imprime_v(v, n);
	
	elimina_v(v, n);
	
	/*conta elementos válidos*/
	int novo_tam = 0;
	while (valido_r(v[novo_tam])) novo_tam++;
	
	imprime_v(v, novo_tam);
	
	ordena_v(v, novo_tam);
	
	imprime_v(v, 0, tam-1);
	
	//Fazer o compara!!!!

	return 0;
}

/*Porque isso deu errado??

void troca_r(struct racional **a, struct racional **b)
{
    struct racional *aux;
    *aux = *a;
    *a = *b;
    *b = *aux;
}
*/

