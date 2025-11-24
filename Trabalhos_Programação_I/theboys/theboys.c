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


// AVALIAR RETORNOS DE ERRO!!!!!!!!!!!!!!!!!!!!!!!!!!


// programa principal
int main ()
{
	/* Iniciar entidades e atributos -> modular? */
	struct Mundo mundo;
	int codigo_evento, tempo, hab;
	void *evento_atual;

	srand(0); //Usar time NULL depois?

	mundo.relogio = 0;
	mundo.tam_mundo.x = TAMMUNDO;
	mundo.tam_mundo.y = TAMMUNDO;
	mundo.nhabilidades = NHABILIDADES;
	mundo.nherois = NHEROIS;
	mundo.nbases = NBASES;
	mundo.nmissoes = NMISSOES;
	mundo.ncompostos = NCOMPOSTOS;
	mundo.LEF = fprio_cria(); /* LEF é uma fila de prioridade, com prioridade = tempo */

	//usar cjto_aleat???!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/* Inicialização dos heróis */
	mundo.vivos = cjto_cria(mundo.nherois);
	for (int i = 0; i < mundo.nherois; i++)
	{
		mundo.herois[i].id = i;
		mundo.herois[i].xp = 0;
		mundo.herois[i].paciencia = rand() % 101; //0 a 100
		mundo.herois[i].velocidade = 50 + rand() % 4951; //50 a 5000

		cjto_insere(mundo.vivos, i);

		/* Heroi terá uma quantidade aleatória de habilidadades, também aleatórias */
		mundo.herois[i].habilidades = cjto_cria(1 + rand() % 4); //1 a 3
		for (int j = 0; j < mundo.herois[i].habilidades->cap; j++)
		{
			hab = 1 + rand() % mundo.nhabilidades; //1 a NHABILIDADES
			cjto_insere(mundo.herois[i].habilidades, hab); //verificar se é assim mesmo!!!!!!!!!!!!!!!
		}
	}

	/* Inicialização das bases */
	for (int i = 0; i < mundo.nbases; i++)
	{
		mundo.bases[i].id = i;
		mundo.bases[i].local.x = rand() % mundo.tam_mundo.x; //0 a TAMMUNDO-1
		mundo.bases[i].local.y = rand() % mundo.tam_mundo.y; //0 a TAMMUNDO-1
		mundo.bases[i].lotacao = 3 + rand() % 11; //3 a 10

		mundo.bases[i].presentes = cjto_cria(mundo.bases[i].lotacao);

		mundo.bases[i].fila_espera = fila_cria();
	}

	/* Inicialização das missões */
	for (int i = 0; i < mundo.nmissoes; i++)
	{
		mundo.missoes[i].id = i;
		mundo.missoes[i].tentativas = 0;
		mundo.missoes[i].local.x = rand() % mundo.tam_mundo.x; //0 a TAMMUNDO-1
		mundo.missoes[i].local.y = rand() % mundo.tam_mundo.y; //0 a TAMMUNDO-1

		mundo.missoes[i].habilidades_m = cjto_cria(6 + rand() % 5);  //6 a 10
		for (int j = 0; j < mundo.missoes[i].habilidades_m->cap; j++)
		{
			hab = 1 + rand() % mundo.nhabilidades; //1 a NHABILIDADES
			cjto_insere(mundo.missoes[i].habilidades_m, hab);
		}
	}
	
	/* Eventos Iniciais */

	/* Cada herói chegará em alguma base dentro de 3 dias */
	for (int i = 0; i < mundo.nherois; i++)
	{
		/* Cria o evento */
		struct chega *c;
    	if (!(c = malloc(sizeof(struct chega))))
        	return 1;
		
		c->heroi = i;
		c->base = rand() % mundo.nbases; //0 a NBASES-1 verificar se tá certo!!!!!!!!!!
		c->tempo = rand() % 4321; //0 a 4320

		fprio_insere(mundo.LEF, c, CHEGA, c->tempo);
	}

	/* Distribuição das missões na LEF */
	for (int i = 0; i < mundo.nmissoes; i++)
	{
		mundo.missoes[i].tempo = rand() % (FIMMUNDO + 1);
		fprio_insere(mundo.LEF, &mundo.missoes[i], MISSAO, mundo.missoes[i].tempo);
	}


	/* Evento que finalizará a mundo */
	struct fim *f;
	if (!(f = malloc(sizeof(struct fim))))
		return 1; //return o que?!!!!!!!!!!!!!!!!!!!!!!!!!
	f->tempo = FIMMUNDO;

	fprio_insere(mundo.LEF, f, FIM, FIMMUNDO);

	/* Laço da simulação */
	do {
		/* Evento atual aponta para a struct do próximo evento */
		evento_atual = fprio_retira(mundo.LEF, &codigo_evento, &tempo);

		mundo.relogio = tempo;

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
				printf("fim do mundo\n");
				break;

			default:
				break;
		}

		//CPA NÃO PRECISE -> FPRIO DESTRÓI ITENS TAMBÉM
		if (codigo_evento != MISSAO) /* Missão é a única estrutura estática (mundo.missoes[i]) */
			free(evento_atual);

	} while (codigo_evento != FIM);


	/* Destruição do mundo */
	
	/* Destruição dos conjuntos de habilidades dos heróis */
	for (int i = 0; i < mundo.nherois; i++)
		cjto_destroi(mundo.herois[i].habilidades); //verificar se é assim mesmo!!!!!!

	/* Destruição dos conjuntos de presentes e das filas de espera de todas as bases */
	for (int i = 0; i < mundo.nbases; i++)
	{
		cjto_destroi(mundo.bases[i].presentes);
		mundo.bases[i].fila_espera = fila_destroi(mundo.bases[i].fila_espera);
	}

	cjto_destroi(mundo.vivos);

	/* Destruição do conjunto de habilidade de todas as missões*/
	for (int i = 0; i < mundo.nmissoes; i++)
		cjto_destroi(mundo.missoes[i].habilidades_m);

	/* Destruição da LEF */
	mundo.LEF = fprio_destroi(mundo.LEF);

  return (0) ;
}