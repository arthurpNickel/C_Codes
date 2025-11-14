#ifndef EVENTOS
#define EVENTOS

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
    int heroi; //não sei!!!!!!!!!!!!!!!!!
    int base; 
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