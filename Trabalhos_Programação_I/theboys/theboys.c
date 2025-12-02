// programa principal do projeto "The Boys - 2024/2"
// Autor: Arthur Paul Nickel, GRR 20252825

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "valores_simulacao.h"
#include "entidades.h"
#include "inicializacao.h"
#include "criacao.h"
#include "eventos.h"
#include "destruicao.h"
#include "fprio.h"

/* Chama funções que inicializam simulação */
void inicialiaza_simulacao(Tp_Mundo *mundo)
{
	inicializa_mundo(mundo);
	inicializa_herois(mundo);
	inicializa_bases(mundo);
	inicializa_missoes(mundo);
}

/* Chama funções que destroem a simulação*/
void destroi_simulacao(Tp_Mundo *mundo)
{
	destroi_bases(mundo);
	destroi_missoes(mundo);
	destroi_herois(mundo);
	destroi_lef(mundo);
}

int main ()
{
	Tp_Mundo mundo;

	void *evento_atual; /* Variável que aponta para a estrutura do evento atual */
	int codigo_evento; /* Guarda o código do evento atual */

	srand(time(NULL)); /* Semente para números aleatórios */

	inicialiaza_simulacao(&mundo);
	
	cria_eventos_iniciais(&mundo); 

	/* Laço principal da simulação */
	do {
		/* Evento atual aponta para a struct do próximo evento da LEF */
		evento_atual = fprio_retira(mundo.LEF, &codigo_evento, &mundo.relogio);

		switch (codigo_evento) /* Escolhe o próximo evento a ser realizado na simulação de acordo com o código */
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

		/* Evento missão será utilizado para estatísticas,
		   por isso, não deve ser destruído por enquanto */
		if (codigo_evento != MISSAO)
			free(evento_atual);
	
	} while (codigo_evento != FIM);

	destroi_simulacao(&mundo);

	return (0);
}