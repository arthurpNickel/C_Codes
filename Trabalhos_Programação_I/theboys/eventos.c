/* Implementação dos eventos da simulação */


#include "eventos.h"
#include "entidades.h"


void evento_chega(Tp_Mundo *m, Tp_Chega *c)
{
	int espera;

	/* Se herói estiver morto, ignora o evento */
	if (!m->herois[c->heroi].vivo)
		return;

	m->neventos++;

	printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ",
			c->tempo, c->heroi, c->base, fila_tamanho(m->bases[c->base].fila_espera),
			m->bases[c->base].lotacao);

	m->herois[c->heroi].base = c->base; /* Muda ID da base que herói se encontra no momento*/

	/* Se a fila estiver vazia e houver vaga, o herói entra direto */
	if (fila_tamanho(m->bases[c->base].fila_espera) < m->bases[c->base].lotacao &&
		fila_tamanho(m->bases[c->base].fila_espera) == 0)
		espera = 1;

	/* Se não, ele decide se vai esperar na fila */
	else 
		espera =  m->herois[c->heroi].paciencia > 10 * fila_tamanho(m->bases[c->base].fila_espera);
    
    if (espera)
    {
		printf("ESPERA\n");
		cria_evento_espera(m, c->heroi, c->base, c->tempo);
		return;
    }

	printf("DESISTE\n");
	cria_evento_desiste(m, c->heroi, c->base, c->tempo);
}


void evento_espera(Tp_Mundo *m, Tp_Espera *e)
{
	/* Se herói estiver morto, ignora o evento */
	if (!m->herois[e->heroi].vivo)
		return;
	
	m->neventos++;

	printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",
			e->tempo, e->heroi, e->base, fila_tamanho(m->bases[e->base].fila_espera));
	
	fila_insere(m->bases[e->base].fila_espera, e->heroi); /* Adiciona o herói a fila de espera */

	/* Verifica se a fila atual é a fila máxima da base */
	if (fila_tamanho(m->bases[e->base].fila_espera) > m->bases[e->base].fila_max)
		m->bases[e->base].fila_max = fila_tamanho(m->bases[e->base].fila_espera);

	cria_evento_avisa(m, e->base, e->tempo);
}


void evento_desiste(Tp_Mundo *m, Tp_Desiste *d)
{
	int destino;

	/* Se herói estiver morto, ignora o evento */
	if (!m->herois[d->heroi].vivo)
		return;

	m->neventos++;

	destino = aleatorio(0, m->nbases-1); /* Herói escolhe uma base aleatória para viajar */

	cria_evento_viaja(m, d->heroi, destino, d->tempo);

	printf("%6d: DESISTE HEROI %2d BASE %d\n",
			d->tempo, d->heroi, d->base);
}


void evento_avisa(Tp_Mundo *m, Tp_Avisa *a)
{
	int h;

	m->neventos++;

	printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", 
			a->tempo, a->base, fila_tamanho(m->bases[a->base].fila_espera), m->bases[a->base].lotacao);
	fila_imprime(m->bases[a->base].fila_espera);
	printf (" ]\n");

	/* Enquanto houver vaga na base, o porteiro admite o próximo herói da fila */
	while (m->bases[a->base].lotacao > cjto_card(m->bases[a->base].presentes) 
			&& fila_tamanho(m->bases[a->base].fila_espera) != 0)
	{
		fila_retira(m->bases[a->base].fila_espera, &h); /* Tira herói da fila */
		cjto_insere(m->bases[a->base].presentes, h); /* Insere herói na base */

		cria_evento_entra(m, h, a->base, a->tempo);

		printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n",
				a->tempo, a->base, h);
	}
}


void evento_entra(Tp_Mundo *m, Tp_Entra *en)
{
	int TPB;

	/* Se herói estiver morto, ignora o evento */
	if (!m->herois[en->heroi].vivo)
		return;

	m->neventos++;

	/* Calcula tempo de permanência na base (TPM) */
	TPB = 15 + m->herois[en->heroi].paciencia * aleatorio(1, 20);

	cria_evento_sai(m, en->heroi, en->base, en->tempo + TPB); /* Sai em tempo atual + TPB */

	printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n",
		en->tempo, en->heroi, en->base, cjto_card(m->bases[en->base].presentes),
		m->bases[en->base].lotacao, en->tempo + TPB);
}


void evento_sai(Tp_Mundo *m, Tp_Sai *s)
{
	int destino; 

	/* Se herói estiver morto, ignora o evento */
	if (!m->herois[s->heroi].vivo)
		return;

	m->neventos++;

	cjto_retira(m->bases[s->base].presentes, s->heroi); /* Retira herói da base */

	destino = aleatorio(0, m->nbases-1); /* Herói escolhe base aleatória para viajar */

	cria_evento_viaja(m, s->heroi, destino, s->tempo);

	cria_evento_avisa(m, s->base, s->tempo); /* Avisa porteiro, pois liberou vaga na base */

	printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n",
			s->tempo, s->heroi, s->base, cjto_card(m->bases[s->base].presentes), m->bases[s->base].lotacao);
}


void evento_viaja(Tp_Mundo *m, Tp_Viaja *v)
{
	int distancia, duracao;

	/* Se herói estiver morto, ignora o evento */
	if (!m->herois[v->heroi].vivo)
		return;

	m->neventos++;

	distancia = calcula_distancia_bases(m, m->herois[v->heroi].base, v->destino);

	duracao = distancia / m->herois[v->heroi].velocidade; /* Calcula duração da viagem, de acordo com velocidade */

	cria_evento_chega(m, v->heroi, v->destino, v->tempo + duracao);

	printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",
			v->tempo, v->heroi, m->herois[v->heroi].base, v->destino, 
			distancia, m->herois[v->heroi].velocidade, v->tempo + duracao);
}


void evento_morre(Tp_Mundo *m, Tp_Morre *mr)
{
	/* Se herói estiver morto, ignora o evento */
	if (!m->herois[mr->heroi].vivo)
		return;

	m->neventos++;

	cjto_retira(m->bases[mr->base].presentes, mr->heroi); /* Retira herói da base em que se encontra */
	
	m->herois[mr->heroi].vivo = 0; 	/* Muda status do herói, para ignorar futuros eventos */

	cria_evento_avisa(m, mr->base, mr->tempo);

	printf("%6d: MORRE HEROI %2d MISSAO %d\n", mr->tempo, mr->heroi, mr->missao);
}


void evento_missao(Tp_Mundo *m, Tp_Missao *ms)
{
	struct cjto_t *habilidades_base = NULL;
	int distancia_missao[NBASES]; /* Cria vetor ordenado pela distância */
	int i, j;
	int id_primeira; 
	int id_base = -1;
	int escolhido;
	int xp_atual;
	int BMP;

	ms->tentativas++; /* Aumenta número de tentativas na missão */

	m->neventos++;

	printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", ms->tempo, ms->id, ms->tentativas);
	cjto_imprime(ms->habilidades_m);
	printf(" ]\n");

	/* Inicializa vetor de id de bases ordenado pela distância à missão */
	for (i = 0; i < m->nbases; i++)
		distancia_missao[i] = i;

    /* Ordena as bases pelo critério de distância até a missão, usando QuickSort */
    quick_sort(m, ms, distancia_missao, 0, m->nbases - 1);

	/* Impressão das bases ordenadas pela distância */
	for (i = 0; i < m->nbases; i++)
	{
		printf("%6d: MISSAO %d BASE %d DIST %d HEROIS [ ", ms->tempo, ms->id, distancia_missao[i], calcula_distancia_missao(m, ms, distancia_missao[i]));
		cjto_imprime(m->bases[distancia_missao[i]].presentes);
		printf(" ]\n");
	}

	/* Laço que busca a base apta mais próxima. Se tiver, o conjunto de habilidades da base e o id da BPM 
	   são mantidos para uso fora do laço. */

	BMP = 0; /* "Base mais próxima com heróis capazes" <- Falso */
	i = 0; /* Inicializa indice do vetor de bases ordenado por distância */
	while (!BMP && i < m->nbases)
	{
		/* Guarda em id_base o id da base em verificação*/
		id_base = distancia_missao[i];

		/* Destrói conjunto de habilidades de bases inaptas, pois não serão utilizadas */
		if (habilidades_base)
			habilidades_base = cjto_destroi(habilidades_base);

		/* Criação do conjunto de habilidades da base em verificação */
		habilidades_base = cjto_cria(m->nhabilidades);

		/* Laço que reúne habilidades dos heróis que pertencem a base em verificação */
		for (j = 0; j < NHEROIS; j++)
		{
			if (cjto_pertence(m->bases[id_base].presentes, j))
			{
				printf("%6d: MISSAO %d HAB HEROI %2d: [ ", ms->tempo, ms->id, j);
				cjto_imprime(m->herois[j].habilidades);
				printf(" ]\n");

				habilidades_base = uniao_habilidades(habilidades_base, m->herois[j].habilidades);

				printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ", ms->tempo, ms->id, id_base);
				cjto_imprime(habilidades_base);
				printf(" ]\n");
			}
		}

		/* Verifica se as habilidades da missão estão contidas no conjunto de habilidades da base em verificação */
		if (cjto_contem(habilidades_base, ms->habilidades_m))
			BMP = 1; /* Se sim, a base é apta e sai do laço */
		
		i++;
	}

	/* Se existe base cujos heróis conseguem cumprir a missão, a missão é cumprida, ou seja, sai da LEF */
	if (BMP)
	{
		m->bases[id_base].num_missoes++; /* Aumenta número de missões na base */

		printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", ms->tempo, ms->id, id_base);
		cjto_imprime(habilidades_base); /* Imprime conjunto de habilidades da base apta */
		printf(" ]\n");

		/* Aumenta a experiência dos heróis que pertencem a base */
		for (i = 0; i < NHEROIS; i++)
			if (cjto_pertence(m->bases[id_base].presentes, i))
				m->herois[i].xp++;

		habilidades_base = cjto_destroi(habilidades_base);

		return;
	}

	/* Se não existe BPM, deve-se destruir o conjunto de habilidades da última base testada */
	if (habilidades_base)
		habilidades_base = cjto_destroi(habilidades_base);

	/* Verifica se é possível usar composto V*/
	if (m->ncompostos != 0 && ms->tempo % 2500 == 0)
	{
		/* Procura e guarda a base não vazia mais próxima em id_primeira */
		id_primeira = 0;
		while (id_primeira < m->nbases && cjto_card(m->bases[distancia_missao[id_primeira]].presentes) == 0)
			id_primeira++;

		/* Se não tem nenhum herói em nenhuma base, a missão é impossível*/
		if (id_primeira == m->nbases)
		{
			printf("%6d: MISSAO %d IMPOSSIVEL\n", ms->tempo, ms->id);
			ms->tempo = ms->tempo + 1440;
			fprio_insere(m->LEF, ms, MISSAO, ms->tempo);

			return;
		}

		/* Se existe herói em alguma base, então missão é cumprida, pois usará composto V */

		/* Criação do conjunto de habilidades da base mais próxima mais as habilidades do herói com composto V */
		habilidades_base = cjto_cria(m->nhabilidades);

		xp_atual = -1;	/* Variável de comparação para buscar herói com maior xp */
		escolhido = -1; /* Varíavel que guarda herói com maior xp */

		/* Laço que une habilidades da base, busca herói com maior xp e aumenta o xp dos demais heróis */
		for (i = 0; i < NHEROIS; i++)
		{
			if (cjto_pertence(m->bases[id_primeira].presentes, i))
			{
				/* Une habilidades */
				habilidades_base = uniao_habilidades(habilidades_base, m->herois[i].habilidades);

				/* Procura herói mais experiente */
				if (m->herois[i].xp > xp_atual)
				{
					xp_atual = m->herois[i].xp;
					escolhido = i;
				}

				/* Aumenta XP */
				m->herois[i].xp++;
			}
		}

		/* Código de erro que, apesar de inútil, pois a lógica garante que isso não aconteça,
		   traz robustez ao programa e a mais liberdade de mudança futura */
		if (xp_atual == -1 || escolhido == -1)
		{
			if (habilidades_base)
				habilidades_base = cjto_destroi(habilidades_base);
			
			printf("ERRO: herói não escolhido\n");
			return;
		}
		
		/* Adiciona ao conjunto de habilidades da base as habilidades da missão (poder do composto V) */
		habilidades_base = uniao_habilidades(habilidades_base, ms->habilidades_m);

		m->ncompostos--; /* Diminui número de compostos V disponíveis*/

		m->bases[id_primeira].num_missoes++; /* Aumenta número de missões na base */

		printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", ms->tempo, ms->id, id_primeira);
		cjto_imprime(habilidades_base);
		printf(" ]\n");

		habilidades_base = cjto_destroi(habilidades_base);
		
		/* Cria evento de morte para o herói que consumiu o composto V - escolhido */
		cria_evento_morre(m, escolhido, m->herois[escolhido].base, ms->tempo, ms->id);
		
		return;
	}

	/* Se não, adia missão por 1 dia*/
	printf("%6d: MISSAO %d IMPOSSIVEL\n", ms->tempo, ms->id);
	ms->tempo = ms->tempo + 1440;
	fprio_insere(m->LEF, ms, MISSAO, ms->tempo);
}


void evento_fim(Tp_Mundo *m, Tp_Fim *f)
{
	int max_tentativas, min_tentativas, total_tentativas;
	int total_mortos;
	int cumpridas;
	int i;

	printf("%6d: FIM\n", f->tempo);

	m->neventos++;

	/* Apresentação das estatísticas de cada herói da simulação, além da contagem de mortos */
	total_mortos = 0;
	for (i = 0; i < NHEROIS; i++)
		if (m->herois[i].vivo)
		{
			printf("HEROI %2d VIVO PAC %3d VEL %4d EXP %4d HABS [ ",
					i, m->herois[i].paciencia, m->herois[i].velocidade, m->herois[i].xp);
			
			cjto_imprime(m->herois[i].habilidades);
			printf(" ]\n");
		}
		else
		{
			printf("HEROI %2d MORTO PAC %3d VEL %4d EXP %4d HABS [ ",
					i, m->herois[i].paciencia, m->herois[i].velocidade, m->herois[i].xp);
			
			cjto_imprime(m->herois[i].habilidades);
			printf(" ]\n");

			total_mortos++;
		}
	
	/* Apresentação das estatísticas de cada base da simulação */
	for (i = 0; i < m->nbases; i++)
		printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n",
				i, m->bases[i].lotacao, m->bases[i].fila_max, m->bases[i].num_missoes);
	
	printf("EVENTOS TRATADOS: %d\n", m->neventos); /* Quantidade de eventos processados */

	/* Contagem de missões cumpridas */
	cumpridas = 0;
	for (i = 0; i < m->nmissoes; i++)
		if (m->missoes[i]->tempo < FIMMUNDO) /* Se evento não estiver na LEF, então foi cumprida/não adiada */
			cumpridas++;
	
	printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", 
			cumpridas, m->nmissoes, (double)cumpridas/m->nmissoes*100);

	/* Contagem de estatísticas relacionadas às tentativas de missões */
	max_tentativas = m->missoes[0]->tentativas;
	min_tentativas = m->missoes[0]->tentativas;
	total_tentativas = m->missoes[0]->tentativas;
	for (i = 1; i < m->nmissoes; i++)
	{
		if (m->missoes[i]->tentativas > max_tentativas)
			max_tentativas = m->missoes[i]->tentativas;
		else if (m->missoes[i]->tentativas < min_tentativas)
			min_tentativas = m->missoes[i]->tentativas;
		
		total_tentativas = total_tentativas + m->missoes[i]->tentativas;
	}
	
	printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n",
			min_tentativas, max_tentativas, (double)total_tentativas/m->nmissoes); 

	/* Apresentação da taxa de mortalidade de heróis */
	printf("TAXA MORTALIDADE: %.1f%%\n", (double)total_mortos/NHEROIS);
}