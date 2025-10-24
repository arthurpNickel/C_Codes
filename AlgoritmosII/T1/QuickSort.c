int EscolhePivo(struct paciente v, int esq, int dir, int meio)
{
	if (v[esq.prioridade] > v[dir].prioridade)
		if(v[esq].prioridade > v[meio].prioridade) return esq;
	
	if (v[dir].prioridade > v[meio]) return dir;
	
	return meio;
}

void ParticionaV(struct paciente v, int esq, int dir, int pivo, int *pos_pivo)
{
	int i = esq;
	int j = dir;
	int aux;
	
	while (i < j)
	{
		while ((v[i].prioridade <= pivo) && (i < dir)) i++;
		
		while (v[j] > pivo) j--;
		
		if (i < j) troca(v[i], v[j]); //assim a troca mesmo??
	}
	troca();
}

void QuickSort(struct paciente v, int esq, int dir, int *pos_pivo)
{
	if (esq < dir)
	{
		*pos_pivo = EscolhePivo(v, esq, dir, ((esq + dir)/2));
		
		ParticionaV();
		
		QuickSort(v, ); //Ordena subvetor à esquerda do pivo
		
		QuickSort(); //Ordena subvetor à direita do pivo
	}
}
