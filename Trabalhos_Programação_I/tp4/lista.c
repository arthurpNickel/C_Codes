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

int lista_insere_inicio (struct lista *lista, int chave)
{
	struct nodo *novo;
	
	if(!(novo = malloc(sizeof(struct nodo)))) /*aloca espaço para a o nodo*/
		return 0;
	
	novo->chave = chave;
	
	/*Será que tem outra função que simplifica???*/
	if (lista_vazia(lista))
	{
		lista->ini = novo;
		novo->prox = NULL;
	}
	
	/*troca de ponteiros*/
	novo->prox = lista->ini; /*novo aponta para antigo primeiro nodo*/
	lista->ini = novo; /*nodo cabeça aponta para novo         *é assim mesmo?*/
	
	/*aumenta tamanho da lista*/
	lista->tamanho++;
	
	return 1;
}


int lista_insere_fim (struct lista *lista, int chave);

int lista_insere_ordenado (struct lista *lista, int chave);

int lista_remove_inicio (struct lista *lista, int *chave)
{
	*chave = 0;
	if (lista_vazia(lista))
		return 0;
	
	return 1;	
	/*falta a remoção de verdade*/
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

/*!!!!*/
void lista_inicia_iterador (struct lista *lista)
{
	/*??????*/
}
/*!!!!*/
int lista_incrementa_iterador (struct lista *lista, int *chave)
{
	if (lista->ptr == NULL)
		return 0;
		
	/*dá para entender o que é para fazer pela descrição da função*/
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
*/
