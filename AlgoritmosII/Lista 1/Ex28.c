/*Bubble Sort*/
/*Ordem Crescente*/

void bubble_sort(int v[], int tam)
{
	int i, j, aux;
	/*laço que "seleciona" a posição da vez para ser ordenada*/
	for (i = 0;i < tam-1;i++)
	{
		/*laço que "arrasta" menor elemento do vetor para a posição da vez*/
		j = tam - 1;
		while (j > i)
		{
			if (v[j] < v[j-1])
			{
				aux = v[j];
				v[j] = v[j-1];
				v[j-1] = v[j];
			}
			j--;
		}
	}
	return;
}

/*Seria melhor ir de 1 até tam -> v[0] para sentinela
 *Poderia ter usado 2 for*/
