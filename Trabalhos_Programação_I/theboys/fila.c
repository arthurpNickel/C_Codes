#include <stdio.h>
#include <stdlib.h>
#include "fila.h"


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


struct fila_t *fila_destroi (struct fila_t *f)
{
	struct fila_nodo_t *aux;

    if (f == NULL)
        return NULL;

    aux = f->prim;
	
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


int fila_tamanho (struct fila_t *f)
{
    if (f == NULL)
        return -1;
    
    return f->num;
}


void fila_imprime (struct fila_t *f)
{
    struct fila_nodo_t *aux;

    if (f == NULL || f->num == 0)
        return;

    aux = f->prim;

    if (f->num != 1) /* Se fila não for unitária...*/
    {
        while (aux->prox->prox != NULL) /* Imprime até o penúltimo com espaço */
        {
            printf("%d ", aux->item);
            aux = aux->prox;
        }
        aux = aux->prox; /* aux aponta para o último nodo */
    }
    printf("%d", aux->item); /* Imprime último item sem espaço */
}