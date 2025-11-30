/* Definição dos eventos da simulação */

#ifndef EVENTOS_H
#define EVENTOS_H

#include <stdio.h>
#include <stdlib.h>

#include "fila.h"
#include "conjunto.h"
#include "fprio.h"

#include "valores_simulacao.h"
#include "estruturas_eventos.h"
#include "auxiliares.h"
#include "entidades.h"
#include "criacao.h"

/*Herói chegando em uma base em um certo tempo. Ao chegar, o herói 
 *analisa o tamanho da fila e decide se espera para entrar ou desiste.
 **/
void evento_chega(Tp_Mundo *m, Tp_Chega *c);

/*O herói entra na fila de espera de uma base. Assim que entra na fila,
 *o porteiro da base deve ser avisado para verificar a lotação da base.
 **/
void evento_espera(Tp_Mundo *m, Tp_Espera *e);

/*O herói desiste de entrar na base, escolhe uma base aleatória e 
 *viaja para lá.
 **/
void evento_desiste(Tp_Mundo *m, Tp_Desiste *d);

/*O porteiro da base trata a fila de espera.
 **/
void evento_avisa(Tp_Mundo *m, Tp_Avisa *a);

/*O herói entra na base. Ao entrar, o herói decide quanto tempo 
 *vai ficar e agenda sua saída da base.
 **/
void evento_entra(Tp_Mundo *m, Tp_Entra *en);

/*O herói sai da base. Ao sair, escolhe uma base de destino para viajar;
 *o porteiro é avisado, pois uma vaga foi liberada.
 **/
void evento_sai(Tp_Mundo *m, Tp_Sai *s);

/*O herói se desloca para uma base (que pode ser a mesma onde já está)
 **/
void evento_viaja(Tp_Mundo *m, Tp_Viaja *v);

/*O herói morre em alguma missão, usando composto V.
 **/
void evento_morre(Tp_Mundo *m, Tp_Morre *mr);

/*A missão pode ser cumprida ou por heróis de uma base apta ou por um herói que usou
 *composto V sob certas condições. Caso contrário, a missão é dada como impossível e é adiada. 
 **/
void evento_missao(Tp_Mundo *m, Tp_Missao *ms);

/*Encerra a simulação e apresenta as estatísticas.
 **/
void evento_fim(Tp_Mundo *m, Tp_Fim *f);

#endif