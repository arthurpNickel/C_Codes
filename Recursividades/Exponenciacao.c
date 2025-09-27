int pot_rec(int base, int exp)
{
	if (exp == 0)
		return 1;
	
	return base*pot_rec(base, exp-1);
}
