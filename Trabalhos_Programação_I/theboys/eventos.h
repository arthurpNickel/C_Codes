#ifndef EVENTOS
#define EVENTOS

struct chega
{
    int tempo;
    int heroi;
    int base;
}

/*Herói h chegando na base b no instante t. Ao chegar, o
herói analisa o tamanho da fila e decide se espera para entrar ou desiste*/
void evento_chega(struct heroi *h, int b, int t);