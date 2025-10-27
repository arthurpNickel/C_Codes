/*Implementação do Tipo Abstrato de Dados Heap*/

//Infermeira vai mandar uma struct ou só os parâmetros?

struct paciente
{
	char[50] nome; //vai dar boa isso??
	int prioridade;
};

void troca(struct paciente *a, struct paciente *b);
{
	struct paciente aux = *a;
	*a = *b;
	*b = aux;
}

/*Nunca feita*/
int *InicHeap(int *tam)
{
	struct paciente v[500];
	*tam = 0;
	return v;
}

//professor não manda número a ser inserido no parâmetro, nem atribui ele
void InsereHeap(struct paciente v, int *tam, int prioridade, char nome)
{
	int i;

	i = *tam+1;
	
	//testar se chegou em 500??
	v[i].prioridade = prioridade;
	v[i].nome = nome;
	
	while (i > 1 && v[i/2].prioridade < v[i].prioridade) //alguma outra condição de parada??
	{
		troca(v[i/2], v[i]); //isso mesmo ou endereços??
		i = i/2;
	}
	
	*tam++;
}

/*Nunca feita*/
struct paciente RemoveHeap(struct paciente v, int *tam)
{
	struct paciente removido = v[1];
	
	v[1] = v[tam];
	
	*tam--;
	
	SacodeHeap(v, tam);
	
	return removido;
}

/*Reportar número de comparações e trocas!*/
void Heapfy(struct paciente v, int tam)
{
	int i;
	/*laço que seleciona o da vez que será inserido*/
	for (i = 2; i <= tam, i++) InsereHeap(v, i, v[i]); 
}

int ChecaHeap(struct paciente v, int tam)
{
	int i;
	for (i = tam; i > 1; i--)
		if (v[i/2].prioridade < v[i].prioridade) return 0; //menor ou menor e igual??
	
	return 1;
}

/*NUnca feita*/
void ImprimeHeap(int v, int tam)
{
	int i;
	
	if (tam == 0) printf("Fila vazia!");
	
	for (i = 1; i <= tam-1; i++)
	{
		printf("(%d - ", v[i].prioridade);
		//como imprime char???
	}
	printf("(%d - ", v[tam]);
	//imprimir char
}

/*Reportar número de comparações e trocas*/
void HeapSort(struct paciente v, int tam)
{
	int i;
	
	Heapfy(v, tam);
	
	for (i = tam; i > 1; i--)
	{
		troca(v[1], v[i]);
		SacodeHeap(v, i - 1);
	}
}

/*Nunca feita
 *atualizar a prioridade de algum paciente que piorou ou melhorou (AlteraHeap).
 *se status = 0, paciente piorou
 *se status = 1, paciente melhorou*/
void AlteraHeap(struct paciente v, char nome, int melhorou)
{
	//como implementar essa busca pelo nome??
	
	if (melhorou)
		troca(x, y);
	
	troca(x, z);
	return;
}

void SacodeHeap(struct paciente v, int tam)
{
	int i = 2;
	
	while (i <= tam)
	{
		if (i < tam?? v[i+1].prioridade > v[i].prioridade) i++;
		
		if (v[i/2].prioridade >= v[i].prioridade) break;
		
		troca(v[i], v[i/2]);
		
		i = i*2;
		/* Será?
		if (v[i/2].prioridade < v[i].prioridade)
			troca(v[i], v[i/2]);
		*/
	}
}
