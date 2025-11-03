#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

/* coloque demais includes aqui */

/* ------------------- Nao altere estas structs ------------------------- */
struct nodo 
{
    int chave;
    struct nodo *prox;
};

struct lista 
{
    struct nodo *ini;
    struct nodo *ptr; /* ponteiro para algum nodo da lista (iterador) */
    int tamanho;
};
/* ---------------------------------------------------------------------- */

struct lista *lista_cria ()
{
	struct lista *l;
	
	if(!(l = malloc(sizeof(struct lista))))
		return NULL;
	
	l->ini = NULL;
	l->ptr = NULL;
	l->tamanho = 0;
	
	return l;
}


void lista_destroi (struct lista **lista)
{
	struct nodo *aux = (*lista)->ini;

	/*nodo cabeça aponta para o segundo nodo e aux aponta para primeiro, que é desalocado,
	 *até todos os nodos serem desalocados*/
	while (aux != NULL)
	{
		(*lista)->ini = (*lista)->ini->prox;
		free(aux);
		aux = (*lista)->ini;
	}
	
	free(*lista);
	*lista = NULL;
}


int lista_insere_inicio (struct lista *lista, int chave)
{
	struct nodo *novo;
	
	if(!(novo = malloc(sizeof(struct nodo))))
		return 0;
	
	novo->chave = chave;
	
	novo->prox = lista->ini; /*novo aponta para antigo primeiro nodo ou é aterrado*/
	lista->ini = novo; /*nodo cabeça aponta para novo*/

	lista->tamanho++;
	
	return 1;
}


int lista_insere_fim (struct lista *lista, int chave)
{
	struct nodo *aux = lista->ini;
	
	/*cria novo nodo, aloca, atribui chave e aterra*/
	struct nodo *novo;
	if(!(novo = malloc(sizeof(struct nodo)))) 
		return 0;
	novo->chave = chave;
	novo->prox = NULL;
	
	lista->tamanho++;
	
	/*se lista for vazia, insere no início*/
	if (aux == NULL)
	{
		lista->ini = novo;
		return 1;
	}
	
	/*laço para aux apontar para o último nodo*/
	while (aux->prox != NULL) aux = aux->prox;
	
	aux->prox = novo;
	
	return 1;	
}


int lista_insere_ordenado (struct lista *lista, int chave)
{
	struct nodo *aux = lista->ini;
	
	/*cria novo nodo, aloca e atribui chave*/
	struct nodo *novo;
	if(!(novo = malloc(sizeof(struct nodo))))
		return 0;
	novo->chave = chave;
	
	lista->tamanho++;
	
	/*se a lista for vazia, insere no início*/
	if (aux == NULL)
	{
		lista->ini = novo;
		novo->prox = NULL;
		return 1;
	}
	
	/*se primeiro nodo já tem chave maior que o novo, insere no primeiro*/
	if (aux->chave >= chave)
	{
		novo->prox = aux;
		lista->ini = novo;
		return 1;
	}
	
	/*laço para aux apontar para nodo anterior ao nodo novo ou para o último nodo*/
	while (aux->prox != NULL && aux->prox->chave < chave) aux = aux->prox;
	
	/*se o nodo novo é o maior da lista, insere no último*/
	if (aux->prox == NULL)
	{
		aux->prox = novo;
		novo->prox = NULL;
		return 1;
	}
	
	/*se não, foi encontrado uma chave maior que a do novo */
	novo->prox = aux->prox; /*novo aponta para o próximo ponteiro*/
	aux->prox = novo; /*nodo apontado por aux aponta para novo nodo*/
	return 1;
}


int lista_remove_inicio (struct lista *lista, int *chave)
{
	struct nodo *aux = lista->ini; 
	
	if (lista_vazia(lista))
		return 0;
	
	*chave = aux->chave;
	
	lista->ini = aux->prox; /*nodo cabeça aponta para segundo nodo*/
	
	free(aux);
	
	lista->tamanho--;
	
	return 1;
}


int lista_remove_fim (struct lista *lista, int *chave)
{
	struct nodo *aux = lista->ini;
	
	if (lista_vazia(lista))
		return 0;
	
	lista->tamanho--;
	
	/*se só tiver um nodo, remove e aterra o cabeça*/
	if (aux->prox == NULL)
	{
		*chave = aux->chave;
		
		free(aux);
		lista->ini = NULL;
		
		return 1;
	}
	
	/*laço para aux apontar para o penúltimo nodo*/
	while (aux->prox->prox != NULL) aux = aux->prox;
	
	*chave = aux->prox->chave;
	
	/*desaloca último nodo e aterra penúltimo*/
	free(aux->prox);
	aux->prox = NULL;
	
	return 1;
}


int lista_remove_ordenado (struct lista *lista, int chave)
{
	struct nodo *aux = lista->ini;
	struct nodo *removido;
	
	if (lista_vazia(lista))
		return 0;
		
	lista->tamanho--;
	
	/*testa se o primeiro é o que se deve remover*/
	if (aux->chave == chave)
	{
		lista->ini = aux->prox;
		free(aux);
		return 1;
	}
	
	/*laço que faz aux apontar para o nodo anterior do que o que se deve remover*/
	while (aux->prox->chave != chave) aux = aux->prox;
	
	removido = aux->prox; /*guarda o endereço do nodo que se quer remover*/
	
	aux->prox = aux->prox->prox; /*faz nodo anterior do removido apontar para o próximo do removido*/
	
	free(removido);
	
	return 1;
}


int lista_vazia (struct lista *lista)
{
	return lista->tamanho == 0; 
}


int lista_tamanho (struct lista *lista)
{
	return lista->tamanho;
}


int lista_pertence (struct lista *lista, int chave)
{
	struct nodo *aux = lista->ini;
	
	/*laço que procura chave na lista*/
	while (aux != NULL && aux->chave != chave) aux = aux->prox;
	
	/*se procurou por toda lista e não achou, retorna 0*/
	if (aux == NULL)
		return 0;
	
	return 1;
}


void lista_inicia_iterador (struct lista *lista)
{
	lista->ptr = lista->ini;
}


int lista_incrementa_iterador (struct lista *lista, int *chave)
{	
	/*se a lista acabou, iterador para*/
	if (lista->ptr == NULL)
		return 0;
		
	*chave = lista->ptr->chave;
	
	lista->ptr = lista->ptr->prox; /*anda na lista*/
	
	return 1;
}
