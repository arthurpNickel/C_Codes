/*melhorar nome dessa função*/
/*Nesse caso n é tam+1 do vetor, o que não é muito legal*/
/*v[0] fica meio "privilegiado" ao retornar, 
 *poderia ter sido 1 o retorno*/
int multiplica_v(int v[], int n);
{
	if (n == 0)
		return v[n];
	
	return v[n]*multiplica_v(v, n-1);
}
