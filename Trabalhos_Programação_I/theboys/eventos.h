#ifndef EVENTOS
#define EVENTOS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fila.h"
#include "lista.h"
#include "conjunto.h"
#include "fprio.h"

/* Eventos */
#define CHEGA 1
#define ESPERA 2
#define DESISTE 3
#define AVISA 4
#define ENTRA 5
#define SAI 6
#define VIAJA 7
#define MORRE 8
#define MISSAO 9
#define FIM 10

//Tirar daqui depois tudo isso!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// seus #defines vão aqui
#define NHABILIDADES 7 //original: 10
#define FIMMUNDO 52560 //original: 525600
#define NHEROIS NHABILIDADES * 5
#define NBASES NHEROIS / 5
#define NMISSOES FIMMUNDO / 100
#define TAMMUNDO 20000
#define NCOMPOSTOS NHABILIDADES * 3

//Tudo são inteiros iguais ou maiores que zero
struct Heroi 
{
	int id;
	struct cjto_t *habilidades;
	int paciencia;
	int velocidade;
	int xp;
	int base;
	int vivo; /* 1 se herói está vivo, 0 se morto */
} ;

struct Coord 
{
	int x;
	int y;
} ;

struct Base 
{
	int id;
	int lotacao; //número máximo de heróis

	//Assim será????
	struct cjto_t *presentes; //conjunto de IDs dos heróis presentes na base

	//verificar se é fila ou lista!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	struct fila_t *fila_espera; //fila de heróis esperando para entrar na base -> é uma fila normal

	struct Coord local;
	
	int fila_max; /* Guarda o tamanho da maior fila que simulação teve*/

	int num_missoes; /* Guarda a quantidade de missões em que herois da base se envolveram */
} ;


struct Missao 
{
	int id;
	struct cjto_t *habilidades_m; //conjunto de habilidades necessárias
	struct Coord local;
	int tempo; //Não tenho certeza disso!!!!!!!!!!!!!!!!!!]
	int tentativas; //posso??!!!!!!!!!!!!!!!!!!!!!
} ;

struct Mundo 
{
	int nherois;
	struct Heroi herois[NHEROIS]; //Número constante assim mesmo?
	int nbases;
	struct Base bases[NBASES]; //revisar isso
	int nmissoes;
	struct Missao **missoes; //revisar isso
	int nhabilidades;
	int ncompostos; //Compostos V!!!!!!!!!!
	int neventos; /* Guarda quantidade de eventos tratados */
	int ncumpridas; /* Guarda quantidade de missões cumpridas */
	struct Coord tam_mundo;
	int relogio;
	struct fprio_t *LEF;
} ;

struct chega
{
    int tempo;
    int heroi;
    int base;
} ;

struct espera
{
    int tempo;
    int heroi;
    int base;
} ;

struct desiste
{
    int tempo;
    int heroi;
    int base;  
} ;

struct avisa
{
    int tempo;
    int base; 
} ;

struct entra
{
	int tempo;
	int heroi;
	int base;
} ;

struct sai
{
	int tempo;
	int heroi;
	int base;
} ;

struct viaja
{
	int tempo;
	int heroi;
	int destino;
} ;

struct morre
{
	int heroi;
	int tempo;
	int base;
} ;

struct fim
{
    int tempo;
} ;

/* Retorna um número aleatório entre min e max, inclusive */
int aleatorio(int min, int max);

/* Cria evento missão e inicializa atributos */
void inicializa_evento_missao(struct Mundo *m, int id);

/* Cria evento fim e insere na LEF */
void cria_evento_fim(struct Mundo *m); //Q: colocar tempo???!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/* Cria evento chega e insere na LEF */
void cria_evento_chega(struct Mundo *m, int heroi, int base, int tempo);

/* Cria evento espera e insere na LEF */
void cria_evento_espera(struct Mundo *m, int heroi, int base, int tempo);

/* Cria evento desiste e insere na LEF */
void cria_evento_desiste(struct Mundo *m, int heroi, int base, int tempo);

/* Cria evento avisa e insere na LEF */
void cria_evento_avisa(struct Mundo *m, int base, int tempo);

/* Cria evento viaja e insere na LEF */
void cria_evento_viaja(struct Mundo *m, int heroi, int destino, int tempo);

/* Cria evento sai e insere na LEF */
void cria_evento_sai(struct Mundo *m, int heroi, int base, int tempo);

/* Cria evento entra e insere na LEF */
void cria_evento_entra(struct Mundo *m, int heroi, int base, int tempo);

/* Cria evento morre e insere na LEF */
void cria_evento_morre(struct Mundo *m, int heroi, int base, int tempo);

/*Herói h chegando na base b no instante t. Ao chegar, o
herói analisa o tamanho da fila e decide se espera para entrar ou desiste*/
void evento_chega(struct Mundo *m, struct chega *c);

/*O herói H entra na fila de espera da base B. Assim que H entrar na fila, o
porteiro da base B deve ser avisado para verificar a fila:*/
void evento_espera(struct Mundo *m, struct espera *e);

/*O herói H desiste de entrar na base B, escolhe uma base aleatória D e viaja
para lá:*/
void evento_desiste(struct Mundo *m, struct espera *d);

/*O porteiro da base B trata a fila de espera:*/
void evento_avisa(struct Mundo *m, struct avisa *a);

/*O herói H entra na base B. Ao entrar, o herói decide quanto tempo vai ficar e
agenda sua saída da base*/
void evento_entra(struct Mundo *m, struct entra *in);

/*O herói H sai da base B. Ao sair, escolhe uma base de destino para viajar; o
porteiro de B é avisado, pois uma vaga foi liberada*/
void evento_sai(struct Mundo *m, struct sai *s);

/*O herói H se desloca para uma base D (que pode ser a mesma onde já está)*/
void evento_viaja(struct Mundo *m, struct viaja *v);

/*O herói H morre no instante T.*/
void evento_morre(struct Mundo *m, struct morre *mo);

/*Uma missão M é disparada no instante T*/
void evento_missao(struct Mundo *m, struct Missao *M);

/* Encerra a simulação no instante T e apresenta as estatísticas */
void evento_fim(struct Mundo *m, struct fim *f);

#endif