// programa principal do projeto "The Boys - 2024/2"
// Autor: Arthur Paul Nickel, GRR 20252825

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "lista.h"
#include "conjunto.h"
#include "fprio.h"

// seus #defines vão aqui
#define NHABILIDADES 10
#define FIMMUNDO 525600
#define NHEROIS NHABILIDADES * 5
#define NBASES NHEROIS / 5
#define NMISSOES FIMMUNDO / 100
#define TAMMUNDO 20000

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

// minimize o uso de variáveis globais

//onde fica o fprio???

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
	struct fila_t *fila_espera; //fila de heróis esperando para entrar na base -> é uma fila normal

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

// programa principal
int main ()
{
	/* Iniciar entidades e atributos -> modular? */
	struct Mundo mundo;
	int codigo_evento, tempo, hab, h, b, t, fim_do_mundo = FIMMUNDO;
	void *evento_atual;

	mundo.relogio = 0;
	mundo.tam_mundo.x = TAMMUNDO; //verificar se é isso mesmo!!!!!!!!!!!!!!!!!!!!!!!!!!!
	mundo.tam_mundo.y = TAMMUNDO;
	mundo.nhabilidades = 10;
	mundo.nherois = mundo.nhabilidades * 5;
	mundo.nbases = mundo.nherois / 5;
	mundo.nmissoes = fim_do_mundo / 100;
	mundo.ncompostos = mundo.nhabilidades * 3;
	mundo.LEF = fprio_cria();

	/* Inicialização dos heróis */
	for (int i = 0; i < mundo.nherois; i++)
	{
		mundo.herois[i].id = i;
		mundo.herois[i].xp = 0;
		mundo.herois[i].paciencia = rand() % 100 + 0; //1 a 100
		mundo.herois[i].velocidade = rand() % 5000 + 50;

		/* Heroi terá uma quantidade aleatória de habilidadades, também aleatórias */
		mundo.herois[i].habilidades = cjto_cria(rand() % 3 + 1); //tá bom???????
		for (int j = 0; j < mundo.herois[i].habilidades->cap; j++)
		{
			hab = rand() % mundo.nhabilidades + 1;
			cjto_insere(mundo.herois[i].habilidades, hab); //verificar se é assim mesmo!!!!!!
		}
	}

	/* Inicialização das bases */
	for (int i = 0; i < mundo.nbases; i++)
	{
		mundo.bases[i].id = i;
		mundo.bases[i].local.x = rand() % mundo.tam_mundo.x-1 + 0;
		mundo.bases[i].local.y = rand() % mundo.tam_mundo.y-1 + 0;
		mundo.bases[i].lotacao = rand() % 10 + 5;
	
		mundo.bases[i].presentes = cjto_cria(mundo.bases[i].lotacao);
		mundo.bases[i].fila_espera = fila_cria();
	}

	/* Inicialização das missões */
	for (int i = 0; i < mundo.nmissoes; i++)
	{
		mundo.missoes[i].id = i;
		mundo.missoes[i].local.x = rand() % mundo.tam_mundo.x-1 + 0;
		mundo.missoes[i].local.y = rand() % mundo.tam_mundo.y-1 + 0;

		mundo.missoes[i].habilidades_m = cjto_cria(rand() % 10 + 6); 
		for (int j = 0; j < mundo.missoes[i].habilidades_m->cap; j++)
		{
			hab = rand() % mundo.nhabilidades + 1;
			cjto_insere(mundo.missoes[i].habilidades_m, hab);
		}
	}
	
	/* Eventos Iniciais */

	/* Cada herói chegará em alguma base dentro de 3 dias */
	for (int i = 0; i < mundo.nherois; i++)
	{
		/* Cria o evento */
		struct chega *c;
    	if(!(c = malloc(sizeof(struct chega))))
        	return;
		c->heroi = i;
		c->base = rand() % mundo.nbases-1 + 0; //verificar se tá certo!!!!!!!!!!
		c->tempo = rand() % 4320 + 0;

		fprio_insere(mundo.LEF, c, CHEGA, c->tempo); //verificar se é isso!!!!!!!!!!!!!!!!!!!!!
	}

	/ Cada missão irá ocorrer em algum momento /
	for (int i = 0; i < mundo.nmissoes; i++)
	{
		t = rand() % fim_do_mundo + 0;
		fprio_insere(evento_missao(t, mundo.missoes[i].id)); //ver se é assim !!!!!!!!!!!!!
	}
	*/

	/
	/* Evento que finalizará a mundo */
	t = fim_do_mundo;
	fprio_insere(t) //arrumar isso!!!!!!!!!!!!!!!!!
	*/

	// executar o laço de simulação

	/* Evento atual aponta para a struct do próximo evento */
	evento_atual = fprio_retira(mundo.LEF, &codigo_evento, &tempo);

	switch (codigo_evento) /* Escolhe o próximo evento a ser realizado na simulação de acordo com o código*/
	{
		case CHEGA {evento_chega(mundo, evento_atual), break};
	}


	/* Destruição do mundo */
	
	/* Destruição dos conjuntos de habilidades dos heróis */
	for (int i = 0; i < mundo.nherois; i++)
	{
		for (int j = 0; j < mundo.herois[i].habilidades->cap; j++)
			cjto_destroi(mundo.herois[i].habilidades); //verificar se é assim mesmo!!!!!!
	}

	/* Destruição dos conjuntos de presentes e das filas de espera de todas as bases */
	for (int i = 0; i < mundo.nbases; i++)
	{
		cjto_destroi(mundo.bases[i].presentes);
		fila_destroi(mundo.bases[i].fila_espera);
	}

	/* Destruição do conjunto de habilidade de todas as missões*/
	for (int i = 0; i < mundo.nmissoes; i++)
		cjto_destroi(mundo.missoes[i].habilidades_m);

  return (0) ;
}

