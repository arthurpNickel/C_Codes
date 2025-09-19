/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

long aleat (long min, long max)
{
	return min + rand()%(max - min + 1);
}


long mdc (long a, long b)
{
	long aux;
	while (b != 0)
	{
		aux = a;
		a = b;
		b = aux % b;
	}
	return a;
}


long mmc (long a, long b)
{
	return (a * b / mdc(a, b));
}


int valido_r (struct racional r)
{
	if (r.den == 0)
		return 0;
	return 1;
}


struct racional simplifica_r (struct racional r)
{
        long vmdc;
        if (valido_r(r))
        {
		vmdc = mdc(r.num, r.den);
		r.num = r.num/vmdc;
		r.den = r.den/vmdc;
		if (((r.num < 0) && (r.den < 0)) || ((r.num > 0) && (r.den < 0)))
		{
			r.num = -r.num;
			r.den = -r.den;
		}
	}
	return r;
}


long numerador_r (struct racional r)
{
        return r.num;
}


long denominador_r (struct racional r)
{
        return r.den;
}


struct racional cria_r (long numerador, long denominador)
{
        struct racional r;
        r.num = numerador;
        r.den = denominador;
	return simplifica_r(r);
}


struct racional sorteia_r (long min, long max)
{
	struct racional r;
	r.num = aleat(min, max);
	r.den = aleat(min, max);
	return simplifica_r(r);
}


void imprime_r (struct racional r)
{
	r = simplifica_r(r);
	
        if (!valido_r(r))
        {
              printf("NaN");
              return;
        }
        if (r.num == 0)
        {
              printf("%d", 0);
              return;
        }
        if (r.den == 1)
        {
              printf("%ld", r.num);
	      return;
        }
        printf("%ld/%ld", r.num, r.den);
        return;
}


int compara_r(struct racional r1, struct racional r2) 
{
	if (!(valido_r(r1) && valido_r(r2)))
		return -2;
	       
	long n1 = r1.num*r2.den;
	long n2 = r2.num*r1.den;

	if (n1 < n2) 
		return -1;
		
	if (n1 > n2) 
		return 1;
		
	return 0;
}


int soma_r (struct racional r1, struct racional r2, struct racional *r3)
{	
	if (!(valido_r(r1) && valido_r(r2)))
		return 1;
	
	r3->den = r1.den*r2.den;
	r3->num = r1.num*r2.den + r2.num*r1.den;
	*r3 = simplifica_r(*r3);
	
	if (r3->num == 0)
		return 1;
		
	return 0;
}


/*soma com o oposto do segundo racional*/
int subtrai_r (struct racional r1, struct racional r2, struct racional *r3)
{	
	if (!(valido_r(r1) && valido_r(r2)))
		return 1;
	
	r2.num = -r2.num;
	soma_r(r1, r2, r3);
	
	if ( r3->num == 0) 
		return 1;
	
	return 0;
}


int multiplica_r (struct racional r1, struct racional r2, struct racional *r3)
{
	if (!(valido_r(r1) && valido_r(r2)))
		return 1;
	
	r3->num = r1.num*r2.num;
	r3->den = r1.den*r2.den;
	*r3 = simplifica_r(*r3);
	
	if (r3->num == 0)
		return 1;
	
	return 0;
}


/*calcula o quociente com a múltiplicação entre r1 e o inverso de r2*/
int divide_r (struct racional r1, struct racional r2, struct racional *r3)
{
	if (!(valido_r(r1) && valido_r(r2)))
		return 1;
	
	/*inverte r2*/
	long aux = r2.num;
	r2.num = r2.den;
	r2.den = aux;
	
	multiplica_r(r1, r2, r3);
	
	if (r3->num == 0)
		return 1;
	
	return 0;
}
