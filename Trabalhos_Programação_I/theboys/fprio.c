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


int fila_vazia (struct fprio_t *f)
{
	if (f->prim == NULL)
		return 1;
	
	return 0;
}


struct fprio_t *fprio_cria ()
{
	struct fprio_t *f;
	if (!(f = malloc(sizeof(struct fprio_t))))
		return NULL;
	
	f->prim = NULL;
	f->num = 0;
	
	return f;
}


struct fprio_t *fprio_destroi (struct fprio_t *f)
{
	struct fpnodo_t *aux = f->prim;
	
	/*Enquanto aux não estiver aterrado*/
	while (aux != NULL)
	{
		f->prim = f->prim->prox; /*f aponta para segundo nodo ou é aterrado*/
		
		/*Libera primeiro nodo e item dele*/
		free(aux->item);
		free(aux);
		
		aux = f->prim; /*aux aponta para o próximo ou é aterrado*/
	}
	
	free(f);
	
	return NULL;
}


int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio)
{	
	struct fpnodo_t *aux, *novo;
	
	/*Verifica casos de erro*/
	if (f == NULL || item == NULL)
		return -1;
	
	aux = f->prim;
	
	/*Verifica se tem item repetido na lista*/
	while (aux != NULL && aux->item != item)
		aux = aux->prox;
	/*Retorna erro se não andou lista inteira*/
	if (aux != NULL)
		return -1;
	
	/*Cria novo nodo*/
	if (!(novo = malloc(sizeof(struct fpnodo_t))))
		return -1;
	novo->item = item;
	novo->tipo = tipo;
	novo->prio = prio;
	
	f->num++;
	
	aux = f->prim;
	
	/*Verifica se insere no primeiro*/
	if (fila_vazia(f) || novo->prio < aux->prio)
	{
		novo->prox = aux; /*aponta para segundo nodo ou aterra*/
		f->prim = novo;
		return f->num;
	}

	/*Laço que aponta para onde se deve inserir*/
	while (aux->prox != NULL && novo->prio >= aux->prox->prio) /*mantém FIFO*/
		aux = aux->prox;

	novo->prox = aux->prox;
	aux->prox = novo;

	return f->num;
}


void *fprio_retira (struct fprio_t *f, int *tipo, int *prio)
{	
	struct fpnodo_t *aux;
	void *item_ptr;
	
	/*Verifica casos de erro*/
	if (f == NULL || tipo == NULL || prio == NULL || fila_vazia(f))
		return NULL;
	
	aux = f->prim;
		
	f->num--;
	
	/*Atribuições do removido*/
	item_ptr = f->prim->item;
	*tipo = f->prim->tipo;
	*prio = f->prim->prio;
	
	f->prim = aux->prox; /*f aponta para segundo da lista*/
	
	free(aux);
	
	return item_ptr;
}


int fprio_tamanho (struct fprio_t *f)
{
	if (f == NULL)
		return -1;

	return f->num;
}


void fprio_imprime (struct fprio_t *f)
{
	struct fpnodo_t *aux = f->prim;	
	
	if (fila_vazia(f))
		return;
	
	/*Enquanto o valor do próximo nodo não for NULL*/
	while (aux->prox != NULL)
	{
		printf("(%d %d) ", aux->tipo, aux->prio);
		aux = aux->prox;
	}
	printf("(%d %d)", aux->tipo, aux->prio);
}
