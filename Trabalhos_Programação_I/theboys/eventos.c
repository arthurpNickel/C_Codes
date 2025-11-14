/* Implementação dos eventos */

//cria dentro ou fora do evento os eventos???

void evento_chega(struct Mundo *m, struct chega *c)
{
	int espera;
	struct espera *e;
	struct desiste *d;

	mundo.herois[b].base = c->base; /* Muda ID da base que herói se encontra no momento*/

	if (mundo.bases[b].fila_espera->fila_tamanho < mundo.bases[b].lotacao && //precisa dessa primeira verificação???!!!!!!!!!!!!!!!!!!!!!!
		mundo.bases[b].fila_espera->fila_tamanho == 0)
		espera = 1;

	else //return? !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		espera =  mundo.heroi[h].paciencia > 10 * mundo.bases[b].fila_espera->fila_tamanho;
    
    if (espera)
    {
        /* Cria evento espera e insere na LEF*/
		if(!(e = malloc(sizeof(struct espera))))
			return;
		e->tempo = c->tempo;
		e->heroi = c->heroi;
		e->base = c->base;
        
		fprio_insere(mundo.LEF, e, ESPERA, e->tempo);

		return;
    }
	
	/* Cria evento desiste e insere na LEF*/
	if(!(d = malloc(sizeof(struct desiste))))
		return;
	d->tempo = c->tempo;
	d->heroi = c->heroi;
	d->base = c->base;
	
	fprio_insere(mundo.LEF, d, DESISTE, d->tempo);
}

/*O herói H entra na fila de espera da base B. Assim que H entrar na fila, o
porteiro da base B deve ser avisado para verificar a fila:*/
void evento_espera(struct Mundo *m, struct espera *e)
{
	fila_insere(mundo.bases[e->base].fila_espera); //algum caso de erro???!!!!!!!!

}

/*O porteiro da base B trata a fila de espera:*/
void evento_avisa(struct Mundo *m, struct avisa *a);
