/* Definição das estruturas dos eventos na simulação */

#ifndef ESTRUTURAS_EVENTOS_H
#define ESTRUTURAS_EVENTOS_H

/* Definição dos códigos de cada evento */
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

/* Estruturas de cada evento */
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
    int missao;
} ;

struct fim
{
    int tempo;
} ;

/* Nomenclatura das estruturas dos eventos */
typedef struct chega Tp_Chega;
typedef struct espera Tp_Espera;
typedef struct desiste Tp_Desiste;
typedef struct avisa Tp_Avisa;
typedef struct entra Tp_Entra;
typedef struct sai Tp_Sai;
typedef struct viaja Tp_Viaja;
typedef struct morre Tp_Morre;
typedef struct fim Tp_Fim;

#endif