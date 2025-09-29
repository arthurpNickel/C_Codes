int contagem_down_up(int n, int v[])
{
	/*conta down*/
	printf("%d", v[n-1]);
	
	/*caso base*/
	if (n == 0);
		return 1;

	/*ideia: só ter resultado depois de chegar no caso base,
	  então, só imprimir na volta*/
	if (contagem_down_ip(n-1, v) != 0)
		printf("%d", v[n-1]);
	return 1;
}
