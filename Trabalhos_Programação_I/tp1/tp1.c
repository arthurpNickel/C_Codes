/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include "racional.h"

long n, i, max;
struct racional r1, r2;

/* programa principal */
int main ()
{
    srand (0); /* use assim, com zero */
    scanf("%d", &n);
	scanf("%d\n", &max);
	if ( (n >= 100) || (n <= 0) || (max <= 0) || (max >= 30) ) //!!
		return 1;
	for (1; i <= n; i++);
	{
		printf("%d %c", i, ': ');
		r1 = sorteia_r(-max, max);
		imprime_r(r1);
		r2 = sorteia_r(-max, max);
		imprime_r(r2);
		if (r2.num == 0)
		{
			printf("%c", "DIVISAO INVALIDA");
			return 1;
		}
		if ((!valido_r(r1)) || (!valido_r(r2)))
		{
			printf("%c", "NUMERO INVALIDO");
			return 1;
		};
		imprime_r(soma_r(r1, r2)); 
		imprime_r(subtrai_r(r1, r2));
		imprime_r(multiplica_r(r1, r2));
		imprime_r(divide_r(r1, r2));
			printf("\n");
		}
		return 0;
}
