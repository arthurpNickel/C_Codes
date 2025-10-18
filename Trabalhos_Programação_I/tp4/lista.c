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

/*Dá para fazer sem aux -> dá boa?*/
int lista_insere_fim (struct lista *lista, int chave)
{
	struct nodo *aux;
	
	/*cria novo nodo, aloca e atribui chave*/
	struct nodo *novo;
	if(!(novo = malloc(sizeof(struct nodo)))) /*aloca espaço para a o nodo*/
		return 0;
	novo->chave = chave;
	
	novo->prox = NULL; /*aterra novo, já que vai ficar no meio*/
	
	aux = lista->ini; /*aux aponta para início da lista*/
	
	lista->tamanho++;
	
	if (aux == NULL) /*se o vetor for vazio, insere no início*/
	{
		lista->ini = novo;
		return 1;
	}
	
	/*laço para aux apontar para o último nodo*/
	while (aux->prox != NULL) /* ... */
	{
		/*anda na lista*/
		aux = aux->prox; /* ... */
	}
	
	aux->prox = novo; /*antigo último aponta para novo nodo*/
	
	return 1;	
}

/*
 * Insere chave em ordem na lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
/* Juntar casos de lista única e inserção no primeiro -> mesma coisa
   E ver se if e else fica melhor
   Arrumar atribuição de tamanho*/
int lista_insere_ordenado (struct lista *lista, int chave)
{
	struct nodo *aux;
	
	/*cria novo nodo, aloca e atribui chave*/
	struct nodo *novo;
	if(!(novo = malloc(sizeof(struct nodo)))) /*aloca espaço para a o nodo*/
		return 0;
	novo->chave = chave;
	
	aux = lista->ini; /*aux aponta para início da lista!!!!*/
	
	if (aux == NULL) /*se a lista for vazia, insere no início*/
	{
		lista->ini = novo;
		lista->tamanho++;
		return 1;
	}
	
	/*confirmar se precisa mesmo -> acho que não em*/
	if (aux->prox == NULL)
	{
		lista->tamanho++;
		
		if (aux->chave >= chave)
		{
			novo->prox = aux; /*insere novo no primeiro*/
			return 1;
		}
		
		/*Ou insere novo no segundo*/
		lista->ini->prox = novo;
		novo->prox = NULL; /*!!!!!!!*/
		return 1;
	}
	
	/* verificando se primeiro nodo já tem chave maior que o novo */
	if (aux->chave >= chave)
	{
		novo->prox = aux;
		lista->ini = novo;
		return 1;
	}
	
	/*laço para aux apontar para nodo anterior ao nodo novo ou para o último nodo*/
	/* enquanto chave do próximo nodo for menor ou igual a chave ... */
	/*enquanto aux prox ou aux prox prox??*/
	while (aux->prox->chave < chave && aux->prox->prox != NULL)
	{
		/*anda na lista*/
		aux = aux->prox; /* ... */
	}
	
	lista->tamanho++;
	
	if (aux->prox->chave >= chave)
	{
		novo->prox = aux->prox; /*novo aponta para o próximo ponteiro*/
		aux->prox = novo; /*nodo apontado por aux aponta para novo nodo*/
		return 1;
	}
	
	/* se não, o nodo novo é o maior da lista: */
	aux->prox->prox = novo; /*!!!!!!!!!!!!!!*/
	novo->prox = NULL;
	
	return 1;
}

int lista_remove_inicio (struct lista *lista, int *chave)
{
	struct nodo *aux;
	
	if (lista_vazia(lista))
		return 0;
	
	*chave = lista->ini->chave;
	
	aux = lista->ini; /*auxiliar aponta para primeiro nodo*/
	
	lista->ini = lista->ini->prox; /*nodo cabeça aponta para segundo nodo*/
	
	/*desaloca espaço do primeiro nodo e aterra*/
	free(aux);
	aux = NULL;
	
	lista->tamanho--;
	
	return 1;
}

/*DÚVIDA: eu preciso aterrar o penúltimo, novo último, ou ao dar free no último ele já está aterrado?*/
int lista_remove_fim (struct lista *lista, int *chave)
{
	struct nodo *aux;
	
	if (lista_vazia(lista))
		return 0;
	
	aux = lista->ini; /*aux aponta para início da lista*/
	
	if (lista->tamanho == 1)
	{
		*chave = aux->chave;
		
		free(aux);
		lista->ini = NULL;
		
		lista->tamanho--;
		
		return 1;
	}
	
	/*laço para aux apontar para o penúltimo nodo*/
	while (aux->prox->prox != NULL) /* ... */
	{
		/*anda na lista*/
		aux = aux->prox; /* ... */
	}
	
	*chave = aux->prox->chave;
	
	/*desaloca último nodo e aterra penúltimo*/
	free(aux->prox);
	aux->prox = NULL;
	
	lista->tamanho--;
	
	return 1;
}

/*
 * Remove o elemento chave da lista mantendo-a ordenada.
 * A função considera que a chave esta presente na lista, quem chama
 * esta funcao deve garantir isso.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
int lista_remove_ordenado (struct lista *lista, int chave)
{
	struct nodo *aux = lista->ini;
	
	if (lista_vazia(lista))
		return 0;
		
	lista->tamanho--;
	
	if (aux->chave == chave)
	{
		free(aux);
		lista->ini = NULL;
		return 1;
	}
	
	/*sem teste de fim da lista!!!*/
	while (aux->prox->chave != chave) /* ... */
	{
		aux = aux->prox; /*anda na lista*/
	}
	
	free(aux->prox);
	aux->prox = NULL;
	
	return 1;
}

int lista_vazia (struct lista *lista)
{
	if (lista->tamanho == 0)
		return 1;
	
	return 0;
	/*assim ou verificando se lista->ini == NULL?*/
}

int lista_tamanho (struct lista *lista)
{
	return lista->tamanho;
}

int lista_pertence (struct lista *lista, int chave);

void lista_inicia_iterador (struct lista *lista)
{
	lista->ptr = lista->ini;
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
