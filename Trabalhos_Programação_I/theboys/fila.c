#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

//Testar!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fila_t *fila_cria ()
{
	struct fila_t *f;
	if (!(f = malloc(sizeof(struct fila_t))))
		return NULL;

    f->prim = NULL;
    f->ult = NULL;
    f->num = 0;
	
	return f;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fila_t *fila_destroi (struct fila_t *f)
{
	struct fila_nodo_t *aux = f->prim;
	
	/*Enquanto aux não estiver aterrado*/
	while (aux != NULL)
	{
		f->prim = f->prim->prox; /*f aponta para segundo nodo ou é aterrado*/
		
		free(aux); /*Libera primeiro nodo*/
		
		aux = f->prim; /*aux aponta para o próximo ou é aterrado*/
	}
	
	free(f);
	
	return NULL;
}

// Insere um item no final da fila (politica FIFO).
// Retorno: 1 se tiver sucesso ou 0 se falhar.
int fila_insere (struct fila_t *f, int item)
{
	struct fila_nodo_t *novo;

	if (f == NULL)
		return 0;
	
	if (!(novo = malloc(sizeof(struct fila_nodo_t))))
		return 0;
	
	novo->prox = NULL;
	novo->item = item;

    f->num++;

    if (f->prim == NULL) /* Testa fila vazia */
    {
        f->prim = novo;
        f->ult = novo;
        return 1;
    }

	f->ult->prox = novo;
	f->ult = novo;

	return 1;
}

// Retira o primeiro item da fila e o devolve
// Retorno 1 se a operação foi bem sucedida e 0 caso contrário
int fila_retira (struct fila_t *f, int *item)
{
    struct fila_nodo_t *aux;
    
    if (f == NULL || f->prim == NULL) /* Caso em que fila está nula ou vazia */
        return 0;

    *item = f->prim->item;

    f->num--;

    /*Desalocar primeiro nodo*/
    aux = f->prim;
    f->prim = f->prim->prox; /* f aponta ou para o próximo da fila ou é aterrado */
    free(aux);

    if (f->prim == NULL) /* Se fila esvaziar, aterrar último*/
        f->ult = NULL;

    return 1;
}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fila_tamanho (struct fila_t *f)
{
    if (f == NULL)
        return -1;
    
    return f->num;
}

// Existe liberdade para as mensagens?!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Imprime o conteúdo da fila 
void fila_imprime (struct fila_t *f)
{
    struct fila_nodo_t *aux;

    if (f == NULL || f->num == 0)
        return;

    aux = f->prim;

    if (f->num != 1) //Será que ficou confuso?!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    {
        while (aux->prox->prox != NULL)
        {
            printf("%d ", aux->item);
            aux = aux->prox;
        }
        aux = aux->prox;
    }
    printf("%d", aux->item);   
}