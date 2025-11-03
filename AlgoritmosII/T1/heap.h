/*Protótipo das funções do Tipo Abstrato de Dados Heap*/

#ifndef Heap_H
#define Heap_H

//Entender exatamente o que está acontecendo aqui
typedef struct heap Heap;
typedef struct paciente Paciente;

//Tá faltando muitos casos de erro!!

//funções para não quebrar TAD!!

//Como fazer tamanho?
/*Inicializa estrutura de dados heap.
 *Retorna endereço para ela.
 **/
Heap *InicHeap();

/*Insere o paciente, com prioridade e nome, dentro do heap,
 *na posição de acordo com sua prioridade.
 *Retorna 1 se conseguiu inserir;
 *Retorna 0 se o heap estiver cheio.
 **/
int InsereHeap(Heap *h, int prioridade, const char *nome); //tá certo esse nome?

/*Retorna o paciente com maior prioridade e o remove do heap.
 **/
Paciente RemoveHeap(Heap *h);

/*Transforma a estrutura de dados em um heap.
 *Retorna 0 se fila estiver vazia;
 *Retorna 1 se conseguiu heapficar.
 **/
int Heapfy(Heap *h);

/*Verifica se a estrutura de dados é um heap.
 *Retorna 0 se não for e 1 se for.
 **/
int ChecaHeap(Heap *h);

/*Imprime o heap, com cada paciente sendo impresso
 *da seguinte forma: "('prioridade') ('nome')"*/
void ImprimeHeap(const Heap *h); //pq const??

/*Ordena, crescentemente, um heap.
 *Retorna 0 se fila estiver vazia;
 *Retorna 1 se conseguiu ordenar.
 **/
int HeapSort(Heap *h);

/*Atualiza a prioridade de algum paciente que piorou ou melhorou:
 *se melhorou = 0, paciente piorou;
 *se melhorou = 1, paciente melhorou.
 *Retorna 0 se paciente não for encontrado ou se a fila estiver vazia;
 *Retorna 1 se conseguiu alterar a prioridade.
 **/
int AlteraHeap(Heap *h,const char *nome, int melhorou); //pq nome??

/*Coloca um paciente que está fora de ordem na primeira posição
 *na sua posição certa no heap.
 *Retorna 0 se fila estiver vazia;
 *Retorna 1 se conseguiu sacodir.
 **/
int SacodeHeap(Heap *h);

/*Libera a memória alocada para o heap.
 **/
void LiberaHeap(Heap *h);

#endif