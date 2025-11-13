/* Implementação dos eventos */

//cria dentro ou fora do evento os eventos???

void evento_chega(struct mundo *m, struct chega *c)
{
	int espera;

	mundo.herois[b].base = c->base; /* Muda ID da base que herói se encontra no momento*/

	if (mundo.bases[b].fila_espera->fila_tamanho < mundo.bases[b].lotacao && //precisa dessa primeira verificação???!!!!!!!!!!!!!!!!!!!!!!
		mundo.bases[b].fila_espera->fila_tamanho == 0)
		espera = 1;
	else //return? !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		espera =  mundo.heroi[h].paciencia > 10 * mundo.bases[b].fila_espera->fila_tamanho;
    
    if (espera)
    {
        //criar evento e espera
        //inserir na LEF
    }
}
