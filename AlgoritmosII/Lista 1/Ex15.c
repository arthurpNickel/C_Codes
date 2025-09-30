/*Escreva os programas iterativo e recursivo que exibem como saída a série completa de Fibonacci, do zero-ésimo termo ao i-ésimo termo, sendo i dado como entrada para o programa.*/

/*RECURSIVO*/

/*DEU ERRADOOOOOOOOOOOO*/

#include <stdio.h>

int fibonacci(int i)
{
	if (i == 0)
	{
		printf("0\n");
		return 0;
	}
	
	if (i == 1)
	{
		printf("1\n");
		return 1;
	}
	
	int fib = fibonacci(i-2) + fibonacci(i-1);
	
	printf("%d\n", fib);
	
	return fib;
}

int main()
{
	int i;
	scanf("%d", &i);
	fibonacci(i);
	return 0;
}
