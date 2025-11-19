#ifndef EVENTOS
#define EVENTOS

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
#define NHABILIDADES 10
#define FIMMUNDO 525600
#define NHEROIS NHABILIDADES * 5
#define NBASES NHEROIS / 5
#define NMISSOES FIMMUNDO / 100
#define TAMMUNDO 20000

//Tudo são inteiros iguais ou maiores que zero
struct Heroi 
{
	int id;
	struct cjto_t *habilidades;
	int paciencia;
	int velocidade;
	int xp;
	int base;
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
	struct lista *fila_espera; //fila de heróis esperando para entrar na base -> é uma fila normal

	struct Coord local;
} ;

struct Missao 
{
	int id;
	struct cjto_t *habilidades_m; //conjunto de habilidades necessárias
	struct Coord local;
} ;

struct Mundo 
{
	int nherois;
	struct Heroi herois[NHEROIS]; //Número constante assim mesmo?
	int nbases;
	struct Base bases[NBASES]; //revisar isso
	int nmissoes;
	struct Missao missoes[NMISSOES]; //revisar isso
	int nhabilidades;
	int ncompostos; //Compostos V!!!!!!!!!!
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

struct fim
{
    int tempo;
} ;

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

#endif