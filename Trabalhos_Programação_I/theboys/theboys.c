//TO DO:

//QUESTION:
//Mudo todas as estruturas para dinâmica?
//Avalio retorno de eventos com casos de erro?
//O que vou modular e o que não?
//Usar time NULL no programa final?

// programa principal do projeto "The Boys - 2024/2"
// Autor: Arthur Paul Nickel, GRR 20252825

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "lista.h"
#include "conjunto.h"
#include "fprio.h"
#include "eventos.h"

// seus #defines vão aqui

// minimize o uso de variáveis globais

// programa principal
int main ()
{
	/* Iniciar entidades e atributos -> Q: modular? */
	struct Mundo mundo;
	void *evento_atual;
	int codigo_evento; 
	int i, b, t; /* Variáveis de suporte */

	srand(0);//Q:Usar time NULL depois?

	mundo.relogio = 0;
	mundo.tam_mundo.x = TAMMUNDO;
	mundo.tam_mundo.y = TAMMUNDO;
	mundo.nhabilidades = NHABILIDADES;
	mundo.nherois = NHEROIS;
	mundo.nbases = NBASES;
	mundo.nmissoes = NMISSOES;
	mundo.ncompostos = NCOMPOSTOS;
	mundo.ncumpridas = 0;
	mundo.neventos = 0;
	mundo.LEF = fprio_cria(); /* LEF é uma fila de prioridade, com prioridade = tempo */

	if(!(mundo.missoes = malloc(sizeof(struct Missao) * mundo.nmissoes))) /*Missões tem estrutura dinâmica*/
		return 1;

	/* Inicialização dos heróis */
	for (i = 0; i < mundo.nherois; i++)
	{
		mundo.herois[i].id = i;
		mundo.herois[i].xp = 0;
		mundo.herois[i].vivo = 1;
		mundo.herois[i].paciencia = aleatorio(0, 100);
		mundo.herois[i].velocidade = aleatorio(50, 5000);
		mundo.herois[i].habilidades = cjto_aleat(aleatorio(1, 3), mundo.nhabilidades); /* Heroi terá uma quantidade aleatória de habilidadades, também aleatórias */
	}

	/* logo depois de criar as habilidades dos heróis, adicione: */
	for (i = 0; i < mundo.nherois; i++) {
		printf("INIT: heroi %2d habilidades ptr = %p\n", i, (void*)mundo.herois[i].habilidades);
	}


	/* Inicialização das bases */
	for (i = 0; i < mundo.nbases; i++)
	{
		mundo.bases[i].id = i;
		mundo.bases[i].local.x = aleatorio(0, mundo.tam_mundo.x - 1);
		mundo.bases[i].local.y = aleatorio(0, mundo.tam_mundo.y - 1);
		mundo.bases[i].lotacao = aleatorio(3, 10);
		mundo.bases[i].fila_max = 0;
		mundo.bases[i].num_missoes = 0;

		mundo.bases[i].presentes = cjto_cria(mundo.bases[i].lotacao);
		mundo.bases[i].fila_espera = fila_cria();
	}

	/* Inicialização das missões */
	for (i = 0; i < mundo.nmissoes; i++)
		inicializa_evento_missao(&mundo, i);
	
	/* Eventos Iniciais */

	//Q: Tá boa essa abordagem mais direta???!!!!!!!!!!!!!!!!!!!!!!!!!!
	/* Cada herói chegará em alguma base aleatória dentro de 3 dias */
	for (i = 0; i < mundo.nherois; i++)
		cria_evento_chega(&mundo, i, aleatorio(0, mundo.nbases-1), aleatorio(0, 4320)); //colocar comentário do motivo desse número

	//Q: Modular cria evento missão???!!!!!!!!!!!!!!!!!!!!!!!!!!
	/* Distribuição das missões na LEF */
	for (i = 0; i < mundo.nmissoes; i++)
	{
		mundo.missoes[i]->tempo = aleatorio(0, FIMMUNDO);
		fprio_insere(mundo.LEF, mundo.missoes[i], MISSAO, mundo.missoes[i]->tempo);
	}

	/* Evento que finalizará a mundo */
	cria_evento_fim(&mundo);

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

	/* Destruição do mundo */
	
	/* Destruição dos conjuntos de presentes e das filas de espera de todas as bases */
	for (i = 0; i < mundo.nbases; i++)
	{
		mundo.bases[i].presentes = cjto_destroi(mundo.bases[i].presentes);
		mundo.bases[i].fila_espera = fila_destroi(mundo.bases[i].fila_espera);
	}

	/* Destruição do conjunto de habilidade de todas as missões*/
	for (i = 0; i < mundo.nmissoes; i++)
	{
		cjto_destroi(mundo.missoes[i]->habilidades_m);

		//Q: < ou <=???!!!!!!!!!!!!!!!!!!!!!!!!
		if (mundo.missoes[i]->tempo < FIMMUNDO) /* Se evento foi cumprido, ele não está na LEF */
			free(mundo.missoes[i]);
	}
/*
	printf(">>> antes do cleanup final\n");
	for (i = 0; i < mundo.nherois; i++) {
		printf("CLEANUP: heroi %2d habilidades ptr = %p\n", i, (void*)mundo.herois[i].habilidades);
	}
*/
	/* Destruição dos conjuntos de habilidades dos heróis */
	for (i = 0; i < NHEROIS; i++)
		mundo.herois[i].habilidades = cjto_destroi(mundo.herois[i].habilidades); //verificar se é assim mesmo!!!!!!

	/* Destruição da LEF */
	mundo.LEF = fprio_destroi(mundo.LEF);

	free(mundo.missoes);

  return (0) ;
}