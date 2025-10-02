/*QuickSort Recursivo*/

void QuickSort(int v[], int tam, int ini)
{
	if (tam == 1)
		return
	
	particiona_v(v, tam, v[ini]);
	
	QuickSort(v, tam/2, ini);
	
	Quick(v, tam/2, tam/2+1);
}
