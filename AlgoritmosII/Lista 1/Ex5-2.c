/*"Escreva o algoritmo da pesquisa sequencial inspecionando o vetor a partir do primeiro elemento, e usando sentinela. "*/

int pesquisa(int v[], int tam, int procurado)
{
	v[tam] = procurado;
	
	int i = 0;
	while (v[i] != procurado) i++;
	
	if (i < tam)
		return i;
	
	return -1;
}
