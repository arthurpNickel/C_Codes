/*revisar lógica*/
maior_v(int maior, int n, int v[])
{
	if (n <= 0)
		return maior;
	
	if (v[n-1] > v[n-2])
		return maior_v(v[n-1], n-2, v);
	
	return maior_v(v[n-2], n-2, v);
}
