/*Implementação do Tipo Abstrato de Dados Heap*/

/*criar um struct paciente com char e int??*/

void troca(int *a, int *b);
{
	int aux = *a;
	*a = *b;
	*b = aux;
}

/*Nunca feita*/
int *InicHeap(int *tam)
{
	int v[500];
	*tam = 0;
	return v;
}

//professor não manda número a ser inserido no parâmetro, nem atribui ele
void InsereHeap(int v, int *tam, int inserido)
{
	int i;

	i = *tam+1;
	
	//testar se chegou em 500??
	v[i] = inserido;
	
	while (i > 1 && v[i/2] < v[i]) //alguma outra condição de parada??
	{
		troca(v[i/2], v[i]); //isso mesmo ou endereços??
		i = i/2;
	}
	
	*tam++;
}

/*Nunca feita*/
int RemoveHeap()
{
	int removido = v[1];
	
	/*transformar em heap de novo
	 *-> talvez colocar último em primeiro e sacudir*/
	
	return removido;
}

void Heapfy(int v, int tam)
{
	int i;
	/*laço que seleciona o da vez que será inserido*/
	for (i = 2; i <= tam, i++) InsereHeap(v, i, v[i]); 
}

int ChecaHeap(int v, int tam)
{
	int i;
	for (i = tam; i > 1; i--)
		if (v[i/2] < v[i]) return 0; //menor ou menor e igual??
	
	return 1;
}

void ImprimeHep(int v, int tam)
{
	int i;
	
	if (tam == 0) printf("Fila vazia!");
	
	for (i = 1; i <= tam-1; i++) printf("%d ", v[i]);
	printf("%d\n", v[tam]);
}

HeapSort();

/*Nunca feita*/
AlteraHeap();

SacodeHeap()
{
	//voltar por aqui!!
}
