/*"Escreva o algoritmo da pesquisa sequencial inspecionando o vetor a partir do primeiro elemento, e usando sentinela. "*/

void pesquisa_sequencial(v[], tam, procurado)
{
	v[tam] = procurado; /*sentinela*/
	
	int achou = 0;
	int i = 0; /*a partir do primeiro*/
	while (!achou)
	{
		if (v[i] == procurado)
			achou = 1;
		else
			i++;
	}
	
	/*testa se achou sentinela*/
	if (i == tam)
		return -1;
	
	return i;
}

/*correção: dá para tirar o achou e deixar mais simples -> teste direto no while*/
