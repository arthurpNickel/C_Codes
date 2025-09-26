#include <stdio.h>

int BuscaBinaria(int procurado, int esq, int dir, int v[])
{
	if (esq > dir)
		return -1;
	
	int meio = (esq + dir) / 2;
	
	if (v[meio] == procurado)
		return meio;
		
	if (v[meio] > procurado)
		return BuscaBinaria(procurado, esq, meio-1, v);
	
	return BuscaBinaria(procurado, meio+1, dir, v);
}

int main ()
{
	int tam;
	printf("entre com tamanho do vetor: ");
	scanf("%d", &tam);
	
	int v[tam];
	
	int i;
	printf("entre com os elementos do vetor (de forma ordenada): ");
	for (i = 0; i < tam; i++)
		scanf("%d", &v[i]);
	
	int procurado;
	printf("entre com o elemento que quer procurar no vetor: ");
	scanf("%d", &procurado);
	
	int resultado = BuscaBinaria(procurado, 0, tam-1, v);
	if (resultado == -1)
	{
		printf("Busca sem sucesso");
		return 1;
	}
	printf("O elemento %d está na posição %d do vetor\n", procurado, resultado);
	return 0;
}
