#ifndef CRIACAO_H
#define CRIACAO_H

#include <stdio.h>
#include <stdlib.h>

#include "entidades.h"
#include "estruturas_eventos.h"
#include "valores_simulacao.h"
#include "auxiliares.h"

#include <stdio.h>
#include <stdlib.h>

/*...*/
void cria_eventos_iniciais(Tp_Mundo *mundo);

/* Cria evento fim e insere na LEF */
void cria_evento_fim(Tp_Mundo *m); //Q: colocar tempo???!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/* Cria evento chega e insere na LEF */
void cria_evento_chega(Tp_Mundo *m, int heroi, int base, int tempo);

/* Cria evento espera e insere na LEF */
void cria_evento_espera(Tp_Mundo *m, int heroi, int base, int tempo);

/* Cria evento desiste e insere na LEF */
void cria_evento_desiste(Tp_Mundo *m, int heroi, int base, int tempo);

/* Cria evento avisa e insere na LEF */
void cria_evento_avisa(Tp_Mundo *m, int base, int tempo);

/* Cria evento viaja e insere na LEF */
void cria_evento_viaja(Tp_Mundo *m, int heroi, int destino, int tempo);

/* Cria evento sai e insere na LEF */
void cria_evento_sai(Tp_Mundo *m, int heroi, int base, int tempo);

/* Cria evento entra e insere na LEF */
void cria_evento_entra(Tp_Mundo *m, int heroi, int base, int tempo);

/* Cria evento morre e insere na LEF */
void cria_evento_morre(Tp_Mundo *m, int heroi, int base, int tempo);

#endif