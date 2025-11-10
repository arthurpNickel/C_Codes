// programa principal do projeto "The Boys - 2024/2"
// Autor: xxxxx, GRR xxxxxx

// seus #includes vão aqui

// seus #defines vão aqui

// minimize o uso de variáveis globais

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
	struct fila_t *fila_espera; //fila de heróis esperando para entrar na base

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
	struct Heroi herois[]; //Revisar isso aqui!!!!!
	int nbases;
	struct Base bases[]; 
	int nmissoes;
	struct Missao missoes[];
	int nhabilidades;
	int ncompostos; //Compostos V!!!!!!!!!!
	struct Coord tam_mundo;
	int relogio;
}
// programa principal
int main ()
{
	/* Iniciar entidades e atributos -> modular? */
	struct Mundo mundo;
	int hab, fim_do_mundo = 525600; //é isso mesmo?????

	mundo.relogio = 0;
	mundo.tam_mundo.x = 20000; //verificar se é isso mesmo!!!!!!
	mundo.tam_mundo.y = 20000;
	mundo.nhabilidades = 10;
	mundo.nherois = mundo.nhabilidades * 5;
	mundo.nbases = mundo.nherois / 5;
	mundo.nmissoes = fim_do_mundo / 100;
	mundo.ncompostos = mundo.nhabilidades * 3;

	/* Inicialização dos heróis */
	for (int i = 0; i < mundo.nherois; i++)
	{
		mundo.herois[i].id = i;
		mundo.herois[i].xp = 0;
		mundo.herois[i].paciencia = rand() % 100 + 0; //1 a 100
		mundo.herois[i].velocidade = rand() % 5000 + 50;

		/* Heroi terá uma quantidade aleatória de habilidadades, também aleatórias */
		mundo.herois.habilidades = cjto_cria(rand() % 3 + 1); //tá bom???????
		for (int j = 0; j < mundo.herois[i].habilidades.cap; j++)
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
		for (int j = 0; j < mundo.missoes[i].habilidades_m.cap; j++)
		{
			hab = rand() % mundo.nhabilidades + 1;
			cjto_insere(mundo.missoes[i].habilidades_m, hab);
		}
	}


	
	//verificar se o que eu fiz ali em cima ta certo



  // executar o laço de simulação

  // destruir o mundo

  return (0) ;
}

