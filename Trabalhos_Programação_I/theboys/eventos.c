/* Implementação dos eventos */

#include "eventos.h"

int heroi_morto(struct Mundo *m, int heroi)
{
	if (cjto_pertence(m->vivos, heroi))
		return 0;
	return 1;
}

/*Herói h chegando na base b no instante t. Ao chegar, o
herói analisa o tamanho da fila e decide se espera para entrar ou desiste*/
void evento_chega(struct Mundo *m, struct chega *c)
{
	int espera;
	struct espera *e;
	struct desiste *d;

	if (heroi_morto(m, c->heroi))
		return;

	printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ",
	c->tempo, c->heroi, c->base, fila_tamanho(m->bases[c->base].fila_espera), m->bases[c->base].lotacao);

	m->herois[c->heroi].base = c->base; /* Muda ID da base que herói se encontra no momento*/

	if (fila_tamanho(m->bases[c->base].fila_espera) < m->bases[c->base].lotacao && //precisa dessa primeira verificação???!!!!!!!!!!!!!!!!!!!!!!
		fila_tamanho(m->bases[c->base].fila_espera) == 0)
		espera = 1;

	else //return? !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		espera =  m->herois[c->heroi].paciencia > 10 * fila_tamanho(m->bases[c->base].fila_espera);
    
    if (espera)
    {
		printf("ESPERA\n");

		//modular?!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        /* Cria evento espera e insere na LEF (mesmos atributos do evento chega) */
		if(!(e = malloc(sizeof(struct espera))))
			return;
		e->tempo = c->tempo;
		e->heroi = c->heroi;
		e->base = c->base;
        
		fprio_insere(m->LEF, e, ESPERA, e->tempo);

		return;
    }

	printf("DESISTE\n");
	
	/* Cria evento desiste e insere na LEF (mesmos atributos do evento chega) */
	if(!(d = malloc(sizeof(struct desiste))))
		return;
	d->tempo = c->tempo;
	d->heroi = c->heroi;
	d->base = c->base;
	
	fprio_insere(m->LEF, d, DESISTE, d->tempo);
}

/* O herói H entra na fila de espera da base B. Assim que H entrar na fila, o
porteiro da base B deve ser avisado para verificar a fila: */
void evento_espera(struct Mundo *m, struct espera *e)
{
	struct avisa *a;

	if (heroi_morto(m, e->heroi))
		return;

	printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n",
			e->tempo, e->heroi, e->base, fila_tamanho(m->bases[e->base].fila_espera));
	
	fila_insere(m->bases[e->base].fila_espera, e->heroi); //algum caso de erro???!!!!!!!!

	/* Cria evento avisa e insere na LEF */
	if (!(a = malloc(sizeof(struct avisa))))
		return;
	a->tempo = e->tempo;
	a->base = e->base;

	fprio_insere(m->LEF, a, AVISA, a->tempo);
}

/*O herói H desiste de entrar na base B, escolhe uma base aleatória D e viaja
para lá*/
void evento_desiste(struct Mundo *m, struct espera *d)
{
	struct viaja *v;
	int destino; //precisa?!!!!!!!!!!!!!!!!!!!!!!!!!!

	if (heroi_morto(m, d->heroi))
		return;

	destino = rand() % m->nbases; /* Escolhe uma base aleatória */

	/* Cria evento viaja e insere na LEF */
	if(!(v = malloc(sizeof(struct viaja))))
		return;
	v->tempo = d->tempo;
	v->heroi = d->heroi;
	v->destino = destino; //pode colocar direto o rand aqui!!!!!!!!!!!!!!!!!!!!!!!!!!

	fprio_insere(m->LEF, v, VIAJA, v->tempo);

	printf("%6d: DESISTE HEROI %2d BASE %d\n",
			d->tempo, d->heroi, d->base);

}

/* O porteiro da base B trata a fila de espera: */
void evento_avisa(struct Mundo *m, struct avisa *a)
{
	struct entra *in;
	int h;
	
	//arrumar aqui
	printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", 
			a->tempo, a->base, fila_tamanho(m->bases[a->base].fila_espera), m->bases[a->base].lotacao);
			//FILA [ %2d %2d  ]"
	
	fila_imprime(m->bases[a->base].fila_espera); //verificar se deu boa!!!!!!!!!!!!!!!!!!!!!!!!!!
	printf (" ]\n");

	//m->bases[a->base].lotacao ou m->bases[a->base].presentes->cap???!!!!!!!!!!!!!!!!!!!!!!!
	while (m->bases[a->base].lotacao > m->bases[a->base].presentes->num 
			&& fila_tamanho(m->bases[a->base].fila_espera) != 0)
	{
		fila_retira(m->bases[a->base].fila_espera, &h);
		cjto_insere(m->bases[a->base].presentes, h);

		/* Cria evento entra e insere na LEF */
		if(!(in = malloc(sizeof(struct entra))))
			return;
		in->tempo = a->tempo;
		in->heroi = h;
		in->base = a->base;

		fprio_insere(m->LEF, in, ENTRA, in->tempo);

		printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n",
				a->tempo, a->base, h);
	}
}

/*O herói H entra na base B. Ao entrar, o herói decide quanto tempo vai ficar e
agenda sua saída da base*/
void evento_entra(struct Mundo *m, struct entra *in)
{
	struct sai *s;
	int TPB;

	if (heroi_morto(m, in->heroi))
		return;

	TPB = 15 + m->herois[in->heroi].paciencia * (1 + rand() % 20); //1 a 20

	/* Cria evento sai e insere na LEF */
	if(!(s = malloc(sizeof(struct entra))))
		return;
	s->tempo = in->tempo + TPB;
	s->heroi = in->heroi;
	s->base = in->base;

	fprio_insere(m->LEF, s, SAI, s->tempo);

	printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n",
		in->tempo, in->heroi, in->base, fila_tamanho(m->bases[in->base].fila_espera),
		m->bases[in->base].lotacao, s->tempo);
}

/*O herói H sai da base B. Ao sair, escolhe uma base de destino para viajar; o
porteiro de B é avisado, pois uma vaga foi liberada*/
void evento_sai(struct Mundo *m, struct sai *s)
{
	struct viaja *v;
	struct avisa *a;
	int destino, status;

	if (heroi_morto(m, s->heroi))
		return;

	status = cjto_retira(m->bases[s->base].presentes, s->heroi);

	//if (status == -1) ????!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	destino = rand() % m->nbases; /* Escolhe uma base aleatória */

	/* Cria evento viaja e insere na LEF */
	if(!(v = malloc(sizeof(struct viaja))))
		return;
	v->tempo = s->tempo;
	v->heroi = s->heroi;
	v->destino = destino;

	fprio_insere(m->LEF, v, VIAJA, v->tempo);

	/* Cria evento avisa e insere na LEF */
	if (!(a = malloc(sizeof(struct avisa))))
		return;
	a->tempo = s->tempo;
	a->base = s->base;

	fprio_insere(m->LEF, a, AVISA, a->tempo);

	printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n",
			s->tempo, s->heroi, s->base, m->bases[s->base].presentes->num, m->bases[s->base].lotacao);
}

//qual o sentido disso?????!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
/*O herói H se desloca para uma base D (que pode ser a mesma onde já está)*/
void evento_viaja(struct Mundo *m, struct viaja *v)
{
	struct chega *c;
	int distancia, duracao;

	if (heroi_morto(m, v->heroi))
		return;

	/* Cálculo da distância e da duração */
	//modular distância??!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//Ta errado esse cálculo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	distancia = sqrt(pow(m->herois[v->heroi].base, 2) + pow(v->destino, 2));

	duracao = distancia / m->herois[v->heroi].velocidade;

	/* Cria evento chega e insere na LEF */
	if(!(c = malloc(sizeof(struct chega))))
		return;
	c->tempo = v->tempo + duracao;
	c->heroi = v->heroi;
	c->base = v->destino;

	fprio_insere(m->LEF, c, CHEGA, c->tempo);

	printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",
			v->tempo, v->heroi, m->herois[v->heroi].base, v->destino, 
			distancia, m->herois[v->heroi].velocidade, c->tempo);
}

//Decrementar número de heróis!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*O herói H morre no instante T.*/
void evento_morre(struct Mundo *m, struct morre *mo)
{
	struct avisa *a;

	if (heroi_morto(m, mo->heroi)) //será??!!!!!!!!!!!!!!!!!!!!!
		return;

	cjto_retira(m->bases[mo->base].presentes, mo->heroi); /* Retira herói da base em que se encontra */

	//Como mudo status do herói??!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/* Cria evento avisa e insere na LEF */
	if (!(a = malloc(sizeof(struct avisa))))
		return;
	a->tempo = mo->tempo;
	a->base = mo->base;

	fprio_insere(m->LEF, a, AVISA, a->tempo);

	printf("%6d: MORRE HEROI %2d MISSAO %d\n", mo->tempo, mo->heroi, 0);
}

//verificar aterramentos
//manipulação de ponteiro de bases e etc!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/*Uma missão M é disparada no instante T*/
void evento_missao(struct Mundo *m, struct Missao *M) //Manter esse m maiusculo????!!!!!!!!!!!!!!
{
	struct fprio_t *distancia_bases; //esqueci de liberar
	struct cjto_t *habilidades_base;
	struct morre *mo;
	struct Base *primeira_base, *base; //!!
	int i, distancia, BMP, b, primeira_id, id_base, escolhido, xp_atual; //!!

	M->tentativas++;

	printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", M->tempo, M->id, M->tentativas);
	cjto_imprime(M->habilidades_m);
	printf(" ]\n");

	distancia_bases = fprio_cria();

	if (distancia_bases == NULL) //?????
		return;

	/* Calcula a distância de cada base ao local da missão e insere em uma fila, ordenada pela distancia */
	for (i = 0; i < m->nbases; i++)
	{
		//avaliar retorno de tipo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//modular distância??!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		distancia = sqrt(pow(m->bases[i].local.x - M->local.x, 2) + pow(m->bases[i].local.y - M->local.y, 2));

		printf("%6d: MISSAO %d BASE %d DIST %d HEROIS [ ", M->tempo, M->id, i, distancia);
		cjto_imprime(m->bases[i].presentes);
		printf(" ]\n");

		if (cjto_card(m->bases[i].presentes) != 0)	
			fprio_insere(distancia_bases, &(m->bases[i]), i, distancia);
	}

	/* Se não existe nenhum herói em nenhuma base, é marcada como impossível*/
	if (fprio_tamanho(distancia_bases) == 0)
	{
		fprio_destroi(distancia_bases);

		/* Adia missão em 1 dia */
		printf("%6d: MISSAO %d IMPOSSIVEL\n", M->tempo, M->id);
		M->tempo = M->tempo + 1440;
		fprio_insere(m->LEF, M, MISSAO, M->tempo);

		return;
	}

	/* Guarda base mais próxima - Caso precise usar composto V*/
	primeira_base = fprio_retira(distancia_bases, &id_base ,&distancia); //isso é gambiarra??!!!!!!!!!!!!!!1
	primeira_id = id_base;
	fprio_insere(distancia_bases, &m->bases[id_base], id_base, distancia);

	BMP = 0; /* "Base mais próxima com heróis capazes" <- Falso */

	/* Verifica se existe alguma base com todas as habilidades necessárias para a missão */
	while (!BMP && fprio_tamanho(distancia_bases) > 0)
	{
		base = fprio_retira(distancia_bases, &id_base, &distancia);

		/* Criação do conjunto de habilidades da base retirada*/
		habilidades_base = cjto_cria(NHABILIDADES);		
		for (i = 0; i < m->nherois; i++) //Ta bom acessar os herois da base desse jeito??!!!!!!!!!!!!!!!!!!
		{
			/* Se o herói pertecente a base, então suas habilidades são unidas as da base*/
			if (cjto_pertence(m->bases[id_base].presentes, i))
			{
				printf("%6d: MISSAO %d HAB HEROI %2d: [ ", M->tempo, M->id, i);
				cjto_imprime(m->herois[i].habilidades);
				printf(" ]\n");

				habilidades_base = cjto_uniao(habilidades_base, m->herois[i].habilidades);

				printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ", M->tempo, M->id, id_base);
				cjto_imprime(habilidades_base);
				printf(" ]\n");
			}
		}

		/* Verifica se as habilidades da missão estão contidas no conjunto de habilidades da base*/
		if (cjto_contem(habilidades_base, M->habilidades_m))
			BMP = 1; /* Base é marcada como BMP (o id dela está na variável id) */
		else
			cjto_destroi(habilidades_base); //ou colocar um break no if de cima???!!!!!!!!!!!!!!!!!!!!!!!
	}

	fprio_destroi(distancia_bases);

	/* Se existe base cujos heróis conseguem cumprir a missão: */
	//id dessa base está salvo
	if (BMP)
	{
		//marcar missão como cumprida?!!!!!!!!!!!!!!!!!!!

		printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", M->tempo, M->id, id_base);
		cjto_imprime(habilidades_base);
		printf(" ]\n");
		cjto_destroi(habilidades_base);

		for (i = 0; i < m->nherois; i++) //Ta bom acessar os herois da base desse jeito??!!!!!!!!!!!!!!!!!!
		{
			/* Se o herói pertecente a base, então sua experiência aumenta*/
			if (cjto_pertence(m->bases[id_base].presentes, i) && !heroi_morto(m, i))
				m->herois[i].xp++;
		}

		return;
	}

	/* Se não, verifica se é possível usar composto V*/
	if (m->ncompostos != 0 && M->tempo % 2500 == 0)
	{
		m->ncompostos--;

		//marcar missão como cumprida?!!!!!!!!!!!!!!!!!!!

		/* Criação do conjunto de habilidades da base mais próxima mais as habilidades do herói com composto V*/
		habilidades_base = cjto_cria(NHABILIDADES);		
		for (i = 0; i < m->nherois; i++) //Ta bom acessar os herois da base desse jeito??!!!!!!!!!!!!!!!!!!
		{
			/* Se o herói pertecente a base, então suas habilidades são unidas as da base*/
			if (cjto_pertence(m->bases[primeira_id].presentes, i))
				habilidades_base = cjto_uniao(habilidades_base, m->herois[i].habilidades);
		}
		habilidades_base = cjto_uniao(habilidades_base, M->habilidades_m); /* Adiciona ao conjunto de habilidades da base as habilidades da missão*/

		printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", M->tempo, M->id, primeira_id);
		cjto_imprime(habilidades_base);
		printf(" ]\n");
		cjto_destroi(habilidades_base);

		/* Procura herói mais experiente da base mais próxima */
		//base mais próxima tem heróis presentes
		xp_atual = -1;	/* Variável para buscar maior xp */
		for (i = 0; i < m->nherois; i++) //Ta bom acessar os herois da base desse jeito??!!!!!!!!!!!!!!!!!!
		{
			/* Se o herói pertecente a base e tem xp maior que o atual escolhido, então ele passa a ser o escolhido*/
			if (cjto_pertence(m->bases[primeira_id].presentes, i) && m->herois[i].xp > xp_atual && !heroi_morto(m, i))
			{
				xp_atual = m->herois[i].xp;
				escolhido = i;
			}
		}

		for (i = 0; i < m->nherois; i++) //Ta bom acessar os herois da base desse jeito??!!!!!!!!!!!!!!!!!!
		{
			/* Se o herói pertecente a base, então sua experiência aumenta*/
			if (cjto_pertence(m->bases[primeira_id].presentes, i) && !heroi_morto(m, i))
				m->herois[i].xp++;
		}

		/* Cria evento morre e insere na LEF */
		if (!(mo = malloc(sizeof(struct morre))))
			return;
		mo->tempo = M->tempo;
		mo->base = m->herois[escolhido].base;
		mo->heroi = escolhido;

		fprio_insere(m->LEF, mo, MORRE, mo->tempo);
		
		return;
	}

	/* Se não, adia missão por 1 dia*/
	printf("%6d: MISSAO %d IMPOSSIVEL\n", M->tempo, M->id);
	M->tempo = M->tempo + 1440;
	fprio_insere(m->LEF, M, MISSAO, M->tempo);
}