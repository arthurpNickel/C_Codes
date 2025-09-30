/*Algoritmo de pesquisa binária recursiva*/
int pesquisa(v[], esq, dir, procurado)
{
	if (esq < dir)
		return -1
	
	int meio = (esq + dir)/2;
	
	if (v[meio] == procurado)
		return meio;
	
	if (v[meio] > procurado)
		return pesquisa(v, esq, meio-1, procurado);
	
	return pesquisa(v, meio+1, dir, procurado);
}
