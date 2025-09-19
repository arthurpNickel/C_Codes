/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

#include <stdio.h>
#include "racional.h"

/*funções auxiliares*/

/*lê vetores de racionais*/
void le_v(struct racional V[], int tam)
{
	int i;
	long num, den;
	for (i = 0; i < tam; i++)
	{
		scanf("%ld %ld", &num, &den);
		V[i] = cria_r(num, den);
	}
}

/*imprime vetor de racionais*/
void imprime_v(struct racional V[], int tam)
{
	printf("VETOR = ");
	int i;
	for (i = 0; i < tam; i++)
	{
		if (i > 0)
			printf(" ");
		imprime_r(V[i]);
	}
	printf("\n");
}

/*troca entre dois racionais*/
void troca_r(struct racional *a, struct racional *b)
{
	struct racional aux = *a;
	*a = *b;
	*b = aux;
}

/*ordena vetor com select sort*/
void ordena_v(struct racional V[], int tam)
{
	int pos_menor, i, j;
	
	/*define posição da vez que será ordenada*/
	for (i = 0; i < tam - 1; i++)
	{
		/*procura posição do menor elemento não ordenado no vetor*/
		pos_menor = i;
		for (j = i + 1; j < tam; j++)
			if (compara_r(V[j], V[pos_menor]) == -1) /*se V[j] for menor que menor...*/
				pos_menor = j;
		
		/*função de troca entre rótulos*/
		troca_r(&V[i], &V[pos_menor]);
	}
}

/*elimina elementos inválidos do vetor, colocando todos os inválidos à direita*/
void elimina_v(struct racional V[], int tam)
{
	int i = 0;
	int j = tam - 1;
	
	while (i <= j) 
	{
		if (valido_r(V[i]))
        		i++; 
    		else if (!valido_r(V[j]))
        		j--;
    		else
    		{
        		troca_r(&V[i], &V[j]);
        		i++;
        		j--;
    		}
	}
}

/*retorna a soma dos elementos de um vetor de racionais*/
struct racional soma_v(struct racional V[], int tam)
{
	int i;
	struct racional vsoma;
	
	/*caso para quando o vetor é unitário e o único elemento é inválido:
	define soma como 0*/
	if (tam == 0)
		vsoma = cria_r(0, 1);
	else
	{	
		vsoma = V[0];
		for (i = 1; i < tam; i++)
			soma_r(vsoma, V[i], &vsoma);
	}
	return vsoma;
}

/* programa principal */

int main ()
{
	struct racional V[100];
	int n, novo_tam;
	
	scanf("%d", &n);
	if (!( (n > 0) && (n < 100) ))
		return 0;
	
	le_v(V, n);
	imprime_v(V, n);
	
	
	elimina_v(V, n);

	/*conta elementos válidos*/
	novo_tam = 0;
	while (valido_r(V[novo_tam])) novo_tam++;
	
	imprime_v(V, novo_tam);
	
	
	ordena_v(V, novo_tam);
	imprime_v(V, novo_tam);
	
	
	struct racional soma = soma_v(V, novo_tam);
	
	printf("SOMA = ");
	imprime_r(soma);
	printf("\n");

	return 0;
}
