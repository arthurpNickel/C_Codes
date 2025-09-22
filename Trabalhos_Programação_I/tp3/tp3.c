/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 09/09/2025 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>

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

/* programa principal */
int main ()
{
	int n;
	scanf("%d", &n);
	
	if ((n < 0) || (n > 100))
		return 1;
	int *v;
	if (!(v = malloc(sizeof(struct racional)*n*1024))) //1024??
		return 1;
	int i;
	long num, den;
	for (i = 0; i < n; i++)
	{
		scanf("%ld %ld", num, den);
		v[i] = cria_r(num, den);
	}
	
	imprime_v(v, n);
	
	return 0;
}

