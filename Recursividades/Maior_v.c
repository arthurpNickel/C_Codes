int maior_v(int maior, int n, int v[])
{
	if (n == 0)
		return maior;
	
	if (v[n-1] > maior)
		return maior_v(v[n-1], n-1, v);
	
	return maior_v(maior, n-1, v);
}
