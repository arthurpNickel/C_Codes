/*O fatorial foi o primeiro algoritmo recursivo que estudamos na disciplina. Escreva dois programas na linguagem C que implementam o fatorial RECURSIVO e ITERATIVO. Em suas implementações a cada vez que o fatorial de 1 é calculado uma mensagem é impressa na tela. Edite, compile e execute seus programas. Quantas mensagens surgem quando você calcula o fatorial de 8 na versão iterativa? E na versão recursiva?*/

/*Versão ITERATIVA*/

#include <stdio.h>

int main()
{
	int n;
	scanf("%d", &n);
	
	int fat = 1;
	int i;
	for (i = 1;i <= n;i++)
	{
		fat = fat*i;
		if (i == 1)
			printf("mensagem ");
	}
	
	printf("%d", fat);
	
	return 0;
}
