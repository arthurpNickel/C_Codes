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
	
	return f;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fila_t *fila_destroi (struct fila_t *f);

// Insere um item no final da fila (politica FIFO).
// Retorno: 1 se tiver sucesso ou 0 se falhar.
int fila_insere (struct fila_t *f, int item)
{
	struct fila_nodo_t *novo;

	if (f == NULL)
		return 0;
	
	if (!(novo = malloc(sizeof(struct fila_t))))
		return 0;
	
	novo->prox = NULL;
	novo->item = item;

	f->ult->prox = novo;
	f->ult = novo;

	f->num++;

	return 1;
}

// Retira o primeiro item da fila e o devolve
// Retorno 1 se a operação foi bem sucedida e 0 caso contrário
int fila_retira (struct fila_t *f, int *item)
{
    struct fila_nodo_t *aux;
    
    if (f == NULL)
        return 0;
    
    aux = f->prim;

    if (aux == NULL) /* Caso em que fila está vazia */
        return 0;

    *item = f->ult->item;

    f->num--;

    /* Encontrar penúltimo para poder aterrar */

    if (f->num == 0) /* Caso em que a fila tem um elemento */
    {
        free(f->prim);
        f->prim = NULL;
        return 1; 
    }

    /* Enquanto aux não apontar para o antepenúltimo, ele anda na fila */
    while (aux->prox != f->ult)
        aux = aux->prox;
    
    free(f->ult);
    aux->prox = NULL;
    f->ult = aux;

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

    if (f == NULL)
    {
        printf("Fila Nula!\n");
        return;
    }
    
    if (f->num == 0)
    {
        printf("Fila Vazia!\n");
        return;
    }

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
    printf("%d\n", aux->item);   
}