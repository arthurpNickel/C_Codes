int maior_v(int v[], int i)
{
	if (i == 1)
		return v[0];
	
	int maior = maior_v(v, i-1);
	
	if (v[i-1] > maior)
		return v[v, i-1];
	
	return maior;
}

/*seria melhor usar n em vez de i*/
