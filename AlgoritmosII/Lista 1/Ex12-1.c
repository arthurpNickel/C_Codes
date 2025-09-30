/*Algoritmo de pesquisa binária iterativa*/
int pesquisa_binaria(int v[], int tam, int procurado)
{
	int esq = 0;
	int dir = tam - 1;
	int meio = (esq + dir)/2;
	
	while ((v[meio] != procurado) && (esq =< dir))
	{
		if (procurado > v[meio])
			esq = meio + 1;
		else if (procurado < v[meio])
			dir = meio - 1;
		
		meio = (esq + dir)/2;
	}
	
	if (esq >= dir) /*verificação errada (esquerda pode ser igual a direita e dar certo)*/
		return -1; /*verificação certa: v[meio] == procurado*/
	
	return meio;
}
