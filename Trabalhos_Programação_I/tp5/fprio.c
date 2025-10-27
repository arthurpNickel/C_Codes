// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Marcos Castilho, inclui as structs no arquivo.c, Out 2025
// Implementação com lista encadeada simples

#include <stdlib.h>
#include <stdio.h>

// descreve um nodo da fila de prioridades
// NAO altere estas estruturas
struct fpnodo_t
{
  void *item ;          // item associado ao nodo
  int   tipo ;          // tipo do item
  int   prio ;          // prioridade do item
  struct fpnodo_t *prox;    // próximo nodo
};

// descreve uma fila de prioridades
struct fprio_t
{
  struct fpnodo_t *prim ;   // primeiro nodo da fila
  int num ;         // número de itens na fila
} ;

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fprio_t *fprio_cria ()
{
	struct fprio_t *f;
	if (!(f = malloc(sizeof(struct fprio_t)))) //estilo condição?
		return NULL;
	
	f->prim = NULL;
	f->num = 0;
	
	return f;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fprio_t *fprio_destroi (struct fprio_t *f)
{
	struct fpnodo_t *aux = f->prim;
	
	while (aux) //estilo condição?
	{
		f->prim = f->prim->prox; /*f aponta para segundo nodo ou é aterrado*/
		
		free(aux->item); /*Libera primeiro nodo*/
		free(aux);
		
		aux = f->prim; /*aux aponta para o próximo ou é aterrado*/
	}
	
	free(f);
	
	//aterramento de *f?
	
	return NULL;
}

// Insere o item na fila, mantendo-a ordenada por prioridades crescentes.
// Itens com a mesma prioridade devem respeitar a politica FIFO (retirar
// na ordem em que inseriu).
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio)
{	
	struct fpnodo_t *aux, *novo;
	
	if (!f || !item) return -1;//estilo condição? identação?
	
	aux = f->prim;
	
	/*verifica se tem item repetido na lista*/
	while (aux && aux->item != item) //estilo condição?
		aux = aux->prox;
	if (aux) return -1; //identação?
	
	/*cria novo nodo*/
	if (!(novo = malloc(sizeof(struct fpnodo_t))))
		return -1;
	novo->item = item; novo->tipo = tipo; novo->prio = prio;//identação?
	
	f->num++;
	
	aux = f->prim;
	
	/*verificar se insere no primeiro*/
	if (aux == NULL || novo->prio < aux->prio) //condição? fila vazia?
	{
		novo->prox = aux; /*aponta para segundo nodo ou aterra*/
		f->prim = novo;
		return f->num;
	}
	
	//Comparação com aux->prox->prio
	//Para manter FIFO: novo->prio < aux->prox->prio

	/*laço que aponta para onde se deve inserir*/
	while (aux->prox != NULL && novo->prio >= aux->prox->prio) //Condição de parada certa???
		aux = aux->prox;

	novo->prox = aux->prox;
	aux->prox = novo;

	return f->num;
}

// Retira o primeiro item da fila e o devolve; o tipo e a prioridade
// do item são devolvidos nos parâmetros "tipo" e "prio".
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio)
{
	//Pode fazer assim será?
	if (!f || !tipo || !prio) //função própria ou só !f->prim -> dúvida para o prof?
		return NULL;
	
	struct fpnodo_t *aux = f->prim;
	void *item_ptr;
		
	f->num--;
		
	item_ptr = f->prim->item;
	*tipo = f->prim->tipo; //ou usar removido?
	*prio = f->prim->prio;
	
	f->prim = aux->prox; /*f aponta para segundo da lista*/
	
	free(aux);
	
	return item_ptr;
}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fprio_tamanho (struct fprio_t *f)
{
	if (!f) return -1;

	return f->num;
}

// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void fprio_imprime (struct fprio_t *f)
{
	struct fpnodo_t *aux = f->prim;	
	
	if (f->num == 0) //Ou fazer uma função "fila vazia"?
		return;
	
	/*Enquanto o valor do próximo nodo não for NULL*/
	while (aux->prox) //Ou aux->prox != NULL?
	{
		printf("(%d %d) ", aux->tipo, aux->prio);
		aux = aux->prox;
	}
	printf("(%d %d)", aux->tipo, aux->prio);
}

/*

Ordem decrescente de prioridade:

int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio)
{
	//prestar atenção com fifo >= < ...
	
	struct fpnodo_t *novo, *aux = f->prim;
	if (!(novo = malloc(sizeof(struct fpnodo_t))))
		return -1;
	
	novo->item = item; novo->tipo = tipo; novo->prio = prio; novo->prox = NULL;//Assim será?
	
	f->num++;
	
	//Preciso estar com o aux apontando para o nodo anterior onde vou inserir
		//Consequência -> pensar caso para primeiro nodo
	//Comparação com aux->prox->prio
	//Para manter FIFO: novo->prio > aux->prox->prio
	if (aux == NULL || novo->prio > aux->prio)
	{
		novo->prox = aux;
		f->prim = novo;
		return f->num;
	}

	/ laço que aponta para onde se deve inserir /
	while (aux->prox != NULL && novo->prio > aux->prox->prio) //Condição de parada certa???
		aux = aux->prox;

	novo->prox = aux->prox;
	aux->prox = novo;

	return f->num;
}
*/

