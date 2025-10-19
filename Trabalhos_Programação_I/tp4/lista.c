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

/*
 * Cria e retorna uma nova lista.
 * Retorna NULL em caso de erro de alocação.
*/
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

/* Desaloca toda memoria da lista e faz lista receber NULL. */
void lista_destroi (struct lista **lista)
{
	struct nodo *aux = (*lista)->ini;

	while (aux != NULL)
	{
		(*lista)->ini = (*lista)->ini->prox; /*!!!!!!!!!*/
		free(aux);
		aux = (*lista)->ini;
	}
	
	free(*lista);
	*lista = NULL;
}

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
	novo->prox = lista->ini; /*novo aponta para antigo primeiro nodo - ou não*/
	lista->ini = novo; /* nodo cabeça aponta para novo */
	
	/*aumenta tamanho da lista*/
	lista->tamanho++;
	
	return 1;
}

/*
 * Insere chave no final da lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int lista_insere_fim (struct lista *lista, int chave)
{
	struct nodo *aux = lista->ini; /*aux aponta para início da lista*/
	
	/*cria novo nodo, aloca e atribui chave*/
	struct nodo *novo;
	if(!(novo = malloc(sizeof(struct nodo)))) /*aloca espaço para a o nodo*/
		return 0;
	novo->chave = chave;
	novo->prox = NULL; /*aterra novo, já que vai ficar no fim*/
	
	lista->tamanho++;
	
	if (aux == NULL) /*se lista for vazia, insere no início*/
	{
		lista->ini = novo;
		return 1;
	}
	
	/*laço para aux apontar para o último nodo*/
	while (aux->prox != NULL) aux = aux->prox; /*anda na lista*/
	
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
	struct nodo *aux = lista->ini; /*aux aponta para início da lista!!!!*/
	
	/*cria novo nodo, aloca e atribui chave*/
	struct nodo *novo;
	if(!(novo = malloc(sizeof(struct nodo)))) /*aloca espaço para a o nodo*/
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
	
	/* verificando se primeiro nodo já tem chave maior que o novo */
	if (aux->chave >= chave)
	{
		novo->prox = aux;
		lista->ini = novo;
		return 1;
	}
	
	/*laço para aux apontar para nodo anterior ao nodo novo ou para o último nodo*/
	/* enquanto chave do próximo nodo for menor ou igual a chave ... */
	while (aux->prox != NULL && aux->prox->chave < chave) aux = aux->prox; /*anda na lista*/
	
	/* testando se o nodo novo é o maior da lista: */
	if (aux->prox == NULL)
	{
		aux->prox = novo;
		novo->prox = NULL;
		return 1;
	}
	
	/* se não, foi encontrado uma chave maior que a do novo */
	novo->prox = aux->prox; /*novo aponta para o próximo ponteiro*/
	aux->prox = novo; /*nodo apontado por aux aponta para novo nodo*/
	return 1;
}

/*
 * Remove o elemento do inicio da lista e o retorna
 * no parametro chave. Nao confundir com o retorno da funcao.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
int lista_remove_inicio (struct lista *lista, int *chave)
{
	struct nodo *aux = lista->ini; /*aux aponta para início da lista*/
	
	if (lista_vazia(lista))
		return 0;
	
	*chave = aux->chave;
	
	lista->ini = aux->prox; /*nodo cabeça aponta para segundo nodo*/
	
	/*desaloca espaço do primeiro nodo*/
	free(aux);
	
	lista->tamanho--;
	
	return 1;
}

/*
 * Remove o elemento do final da lista e o retorna
 * no parametro chave. Nao confundir com o retorno da funcao.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
int lista_remove_fim (struct lista *lista, int *chave)
{
	struct nodo *aux = lista->ini; /*aux aponta para início da lista*/
	
	if (lista_vazia(lista))
		return 0;
	
	lista->tamanho--;
	
	/* testa caso em que a lista só tem 1 nodo */
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

/*
 * Remove o elemento chave da lista mantendo-a ordenada.
 * A função considera que a chave esta presente na lista, quem chama
 * esta funcao deve garantir isso.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
int lista_remove_ordenado (struct lista *lista, int chave)
{
	struct nodo *aux = lista->ini;
	struct nodo *removido;
	
	if (lista_vazia(lista))
		return 0;
		
	lista->tamanho--;
	
	/* testar caso em que primeiro é o que se deve remover */
	if (aux->chave == chave)
	{
		lista->ini = aux->prox;
		free(aux);
		return 1;
	}
	
	/*sem teste de fim da lista!!!*/
	while (aux->prox->chave != chave) aux = aux->prox; /*anda na lista*/
	
	removido = aux->prox; /*guarda o endereço do nodo que se quer remover*/
	
	aux->prox = aux->prox->prox; /*faz nodo anterior do removido apontar para o próximo do removido*/
	
	free(removido);
	
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

int lista_pertence (struct lista *lista, int chave)
{
	struct nodo *aux = lista->ini;
	
	while (aux != NULL && aux->chave != chave) aux = aux->prox;
	
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

Ver o que errei:

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

/tem algo muito errado aqui----------------------------------------------------------/
	
	/confirmar se precisa mesmo -> acho que não em/
	if (aux->prox == NULL)
	{	
		if (aux->chave >= chave)
		{
			novo->prox = aux; /insere novo no primeiro/
			return 1;
		}
		
		/Ou insere novo no segundo/
		lista->ini->prox = novo;
		novo->prox = NULL; /!!!!!!!/
		return 1;
	}
	
	/ verificando se primeiro nodo já tem chave maior que o novo /
	if (aux->chave >= chave)
	{
		novo->prox = aux;
		lista->ini = novo;
		return 1;
	}
	
	/laço para aux apontar para nodo anterior ao nodo novo ou para o último nodo/
	/ enquanto chave do próximo nodo for menor ou igual a chave ... /
	/enquanto aux prox ou aux prox prox?/
	while (aux->prox->chave < chave && aux->prox->prox != NULL) aux = aux->prox; /anda na lista/
	
	if (aux->prox->chave >= chave)
	{
		novo->prox = aux->prox; /novo aponta para o próximo ponteiro/
		aux->prox = novo; /nodo apontado por aux aponta para novo nodo/
		return 1;
	}
	
	/ se não, o nodo novo é o maior da lista: /
	aux->prox->prox = novo; /!!!!!!!!!!!!!!/
	novo->prox = NULL;
	
	return 1;
	
/-----------------------------------------------------------------------------------------*/
