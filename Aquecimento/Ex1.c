#include <stdio.h>

int main () {
	int x, i;
	scanf("%d", &x );
	i = 1;
	while (i*(i+1)*(i+2) <= x)
	{
		if (i*(i+1)*(i+2) == x)
		{
			printf("%s\n", "1"); /*porque imprimi uma string de um e não 1??*/
			return 1; /*sucesso = 0, erro que é 1*/
		}
		i++;
	}
	printf("%s\n", "0");
	return 0;
	}
	

