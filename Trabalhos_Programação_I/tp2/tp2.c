/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include "racional.h"

int n;

/* coloque aqui as funções auxiliares que precisar neste arquivo */

int le_v(struct racional V[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		scanf("%ld" "%ld", &V[i].num, &V[i].den); //ta certo?
	return 1;
}

int imprime_v(struct racional V[], int n)
{
	int i;
	printf("VETOR = ");
	for (i = 0; i < n; i++)
	{
		imprime_r(V[i]);
		printf(" ");
	}
	printf("\n");
	return 1;
}

//aqui ou no TADS?
void troca_r(struct racional *a, struct racional *b)
{
	struct racional aux = *a;
	*a = *b;
	*b = aux;
	return;
}

//select sort
int ordena_v(struct racional V[], int N)
{
	int pos_menor, i, j;
	
	//define posição da vez que será ordenada
	for (i = 0; i <= N; i++)
	{
		//procura posição do menor elemento não ordenado no vetor
		pos_menor = i;
		for (j = i + 1; j <= N; j++)
			if (compara_r(V[j], V[pos_menor]) == -1) //se V[j] for menor que menor...
				pos_menor = j;
		
		//função de troca entre rótulos	
		troca_r(&V[i], &V[pos_menor]);
	}
	
	return 0;
}

/* programa principal */
int main ()
{
	struct racional V[100];
	
	scanf("%d", &n);
	if (!( (n > 0) || (n < 100) ))
		return 0;
	
	le_v(V, n);
	imprime_v(V, n);
	
	//eliminar elementos inválidos - ou mover todos os válidos um para trás
	int invalidos = 0;
	int i, j, novo_tam;
	
	i = n-1;
	while (i >= 0)
	{
		if (!valido_r(V[i]))
		{
		       //tirar elemento invalido do vetor, movendo todos os elementos da frente uma posição à esquerda
			for (j = i; j < ((n-1)-invalidos); j++) //tá certa a condição?
				V[j] = V[j+1]; //assim é o melhor jeito?
			
			invalidos++;
		}
		i--;
	}
	
	novo_tam = n-invalidos;
	
	imprime_v(V, n);
	
	ordena_v(V, novo_tam);
	
	imprime_v(V, n);
	
	//somar elementos do vetor
	struct racional soma = V[0];
	for (i = 1; i <= novo_tam; i++)
		soma_r(soma, V[i], &soma);

	
	printf("SOMA = ");
	imprime_r(soma);
	printf("\n");

	return 0;
}

/*isso daqui não vai dar certo -> não considerei que vetor vai diminuindo
	for (i = 0; i < n; i++) //será que não é melhor de trás para frente?
		if (!valido_r(V[i]))
		{
			for (j = i; j < (n-invalidos); j++) //tá certa a condição?
				V[j] = J[j+1]; //assim é o melhor jeito?
			invalidos++;
		}
	*/
