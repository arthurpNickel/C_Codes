/*Divisão recursiva que retorna quociente e resto*/

int quociente(int dividendo, int divisor, int *resto)
{
	if (dividendo < divisor)
	{
		*resto = dividendo;
		return 0;
	}
	return quociente(dividendo - divisor, divisor, resto) + 1;
}
