#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

/* coloque demais includes aqui */

/* ------------------- Nao altere estas structs ------------------------- */
struct nodo {
    int chave;
    struct nodo *prox;
};

struct lista {
    struct nodo *ini;
    struct nodo *ptr; /* ponteiro para algum nodo da lista (iterador) */
    int tamanho;

};
/* ---------------------------------------------------------------------- */

struct lista *lista_cria ()
{
	struct lista *l; /*cria ponteiro para nodo cabeça*/
	
	if(!(l = malloc(sizeof(struct lista)))) /*aloca espaço para a o nodo cabeça*/
		return NULL;
	
	/*Não tenho certeza disso
	aterramento de ponteiros*/
	l->ini = NULL;
	l->ptr = NULL;
	
	l->tamanho = 0;
	
	return l;
}

/*depois resolver saporra*/
void lista_destroi (struct lista **lista);

/*
 * Insere chave no inicio da lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int lista_insere_inicio (struct lista *lista, int chave)
{
	struct nodo *novo;
	
	if(!(novo = malloc(sizeof(struct nodo)))) /*aloca espaço para a o nodo*/
		return 0;
	
	novo->chave = chave;
	
	/*troca de ponteiros*/
	novo->prox = lista->ini; /*novo aponta para antigo primeiro nodo*/
	lista->ini = novo; /*nodo cabeça aponta para novo         *é assim mesmo?*/
	
	/*aumenta tamanho da lista*/
	lista->tamanho++;
	
	return 1;
}


int lista_insere_fim (struct lista *lista, int chave);

int lista_insere_ordenado (struct lista *lista, int chave);

/*
 * Remove o elemento do inicio da lista e o retorna
 * no parametro chave. Nao confundir com o retorno da funcao.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
int lista_remove_inicio (struct lista *lista, int *chave)
{
	struct lista aux; /*struct nodo ou lista?*/
	
	if (lista_vazia(lista))
		return 0;
	
	*chave = lista->ini->chave;
	
	if (lista->tamanho == 1)
	{
		free(lista->ini);
		lista->ini = NULL;
		return 1;
	}
	
	aux.ini = lista->ini;
	
	lista->ini = lista->ini->prox;
	
	free(aux.ini);
	aux.ini = NULL;
	
	return 1;	
	
}

int lista_remove_fim (struct lista *lista, int *chave);

int lista_remove_ordenado (struct lista *lista, int chave);

int lista_vazia (struct lista *lista)
{
	if (lista->tamanho == 0)
		return 1;
	
	return 0;
	/*assim ou verificando se lista->ini == NULL?*/
}

int lista_tamanho (struct lista *lista);

int lista_pertence (struct lista *lista, int chave);

void lista_inicia_iterador (struct lista *lista)
{
	lista->ptr = lista->ini;
	return;
}

int lista_incrementa_iterador (struct lista *lista, int *chave)
{	
	/*quando *lista.*ptr guardar NULL, iterador para*/
	if (lista->ptr == NULL)
		return 0;
	
	/* chave recebe a chave do nodo que a lista->ptr está apontando*/
	*chave = lista->ptr->chave;
	
	/*anda na lista*/
	lista->ptr = lista->ptr->prox;
	
	return 1;
}

/*
void lista_destroi (struct lista **lista)
{
	struct lista aux;
	
	while (**lista->ini == NULL) /condição certa?/
	{
		aux = **lista; /guardar endereço do primeiro nodo da lista             *É isso mesmo?? /
		**lista->ini = **lista->ini->prox; /cabeça aponta para segundo nodo da lista      *Dá certo?/
		
		/condicional/
		free(aux->ini); /isso mesmo que dá free?/
		aux->ini = NULL;
	}
}

int lista_incrementa_iterador (struct lista *lista, int *chave)
{
	if (lista->ptr == NULL)
		return 0;
		
	*chave = lista->ptr->chave;
	
	if (lista->ptr->prox == NULL)
		return 0;
	
	lista->ptr = lista->ptr->prox;
	
	return 1;
}
*/
