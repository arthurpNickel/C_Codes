int contagem_down_up(int n, int v[])
{
	/*conta down*/
	printf("%d", v[n-1]);
	
	/*caso base*/
	if (n == 1)
		return 1;

	/*ideia: só ter resultado depois de chegar no caso base,
	  então, só imprimir na volta*/
	if (contagem_down_up(n-1, v) != 0)
		printf("%d", v[n-1]);
	return 1;
}

/*Não precisava desse if, acertei na ideia de chamar função antes de outra impressão,
  contudo, era só preciso chamar, não precisa de condicional nem retorno inteiro
 
 *Só chamar a função entre duas impressões. cuidaria do problema -> pensar no fluxo de execução*/
