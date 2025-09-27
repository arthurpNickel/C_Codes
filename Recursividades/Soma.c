int soma_rec(int a, int b)
{
	if (b == 0)
		return a;
	
	return soma_rec(a, b-1) + 1;
}
