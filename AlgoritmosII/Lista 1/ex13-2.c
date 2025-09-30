/*O fatorial foi o primeiro algoritmo recursivo que estudamos na disciplina. Escreva dois programas na linguagem C que implementam o fatorial RECURSIVO e ITERATIVO. Em suas implementações a cada vez que o fatorial de 1 é calculado uma mensagem é impressa na tela. Edite, compile e execute seus programas. Quantas mensagens surgem quando você calcula o fatorial de 8 na versão iterativa? E na versão recursiva?*/

/*Versão RECURSIVA*/

#include <stdio.h>

int fatorial (int n)
{
	if (n == 0)
		return 1;
	
	if (n == 1)
	{
		printf("fatorial de 1!\n");
		return 1;
	}
	
	return fatorial(n-1)*n;
}

int main()
{
	int n;
	scanf("%d", &n);
	printf("%d\n", fatorial(n));
	return 0;
}
