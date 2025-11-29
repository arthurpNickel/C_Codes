//Revisão
//Ver se não tem código de erro

//TO DO:

//QUESTION:
//Usar time NULL no programa final?

// programa principal do projeto "The Boys - 2024/2"
// Autor: Arthur Paul Nickel, GRR 20252825

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>

#include "valores_simulacao.h"
#include "entidades.h"
#include "inicializacao.h"
#include "criacao.h"
#include "eventos.h"
#include "destruicao.h"

#include "fprio.h"

#include "fila.h"
#include "lista.h"
#include "conjunto.h"
#include "eventos.h"
#include "entidades.h"

int main ()
{
	Tp_Mundo mundo;
	void *evento_atual;
	int codigo_evento; 
	int i, b, t; /* Variáveis de suporte */

	srand(0);//Q:Usar time NULL depois?

	/*----------Inicializações----------*/
	inicializa_mundo(&mundo);

	inicializa_herois(&mundo);

	inicializa_bases(&mundo);

	inicializa_missoes(&mundo);
	/*----------------------------------*/
	
	cria_eventos_iniciais(&mundo);

	/* Laço da simulação */
	do {
		/* Evento atual aponta para a struct do próximo evento */
		evento_atual = fprio_retira(mundo.LEF, &codigo_evento, &t);

		mundo.relogio = t;

		switch (codigo_evento) /* Escolhe o próximo evento a ser realizado na simulação de acordo com o código*/
		{
			case CHEGA:
				evento_chega(&mundo, evento_atual);
				break;

			case ESPERA:
				evento_espera(&mundo, evento_atual);
				break;

			case DESISTE:
				evento_desiste(&mundo, evento_atual);
				break;
			
			case AVISA:
				evento_avisa(&mundo, evento_atual);
				break;

			case ENTRA:
				evento_entra(&mundo, evento_atual);
				break;

			case SAI:
				evento_sai(&mundo, evento_atual);
				break;

			case VIAJA:
				evento_viaja(&mundo, evento_atual);
				break;

			case MORRE:
				evento_morre(&mundo, evento_atual);
				break;

			case MISSAO:
				evento_missao(&mundo, evento_atual);
				break;

			case FIM:
				evento_fim(&mundo, evento_atual);
				break;

			default:
				break;
		}

		if (codigo_evento != MISSAO) /* Evento missão será utilizado para estatísticas */
			free(evento_atual);
	
	} while (codigo_evento != FIM);

/*Q: 
	printf(">>> antes do cleanup final\n");
	for (i = 0; i < mundo.nherois; i++) {
		printf("CLEANUP: heroi %2d habilidades ptr = %p\n", i, (void*)mundo.herois[i].habilidades);
	}
*/

	/*--------Destruição do mundo--------*/
	destroi_bases(&mundo);

	destroi_missoes(&mundo); //Q: Será que vai dar boa o free(m->missoes)???!!!!!!!

	destroi_herois(&mundo);
	
	destroi_lef(&mundo);
	/*-----------------------------------*/

  return (0) ;
}