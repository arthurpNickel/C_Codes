/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 * Atualizado em 09/09/2025 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

#include <stdio.h>
#include <stdlib.h>

struct racional {
  long num;          /* numerador   */
  long den;          /* denominador */
};

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


int valido_r (struct racional *r)
{
	if ((r == NULL) || (r->den == 0))
		return 0;	
		
	return 1;
}


int simplifica_r (struct racional *r)
{
	/*testa número inválido ou ponteiro nulo*/
        if (!valido_r(r))
        	return 0;
        
        /*simplifica a fração*/
        long vmdc;
	vmdc = mdc(r->num, r->den);
	r->num = r->num/vmdc;
	r->den = r->den/vmdc;
	
	/*muda sinal, se negativo for numerador ou se os dois forem negativos*/
	if (((r->num < 0) && (r->den < 0)) || ((r->num > 0) && (r->den < 0)))
	{
		r->num = -r->num;
		r->den = -r->den;
	}
	
	return 1;
}


/* Retorna o numerador do racional r */
long numerador_r (struct racional *r)
{
        return r->num;
}


/* Retorna o denominador do racional r */
long denominador_r (struct racional *r)
{
        return r->den;
}


struct racional *cria_r (long numerador, long denominador)
{
	struct racional *r;
	
	if (!(r = malloc(sizeof(struct racional))))
		return NULL;
	
	/*atribui num e den nos espaços reservados pelo malloc*/
	r->num = numerador;
	r->den = denominador;
	
	return r; /*retorna r, que é endereço para o racional*/
}


void destroi_r (struct racional **r)
{
	if (r != NULL && *r != NULL)
	{
		free(*r);
		*r = NULL;
	}
}


void imprime_r (struct racional *r) /*recebe um ponteiro para um racional*/
{
	simplifica_r(r);
	
	if (r == NULL)
	{
		printf("NULL");
		return;
	}
	
        if (!valido_r(r))
        {
              printf("NaN");
              return;
        }
        
        if (r->num == 0)
        {
              printf("%d", 0);
              return;
        }
        
        if (r->den == 1)
        {
              printf("%ld", r->num);
	      return;
        }
        
        printf("%ld/%ld", r->num, r->den);
        
        return;
}


int compara_r (struct racional *r1, struct racional *r2)
{
	long n1, n2;
	
	if (!(valido_r(r1) && valido_r(r2)))
		return -2;
	    
	n1 = r1->num * r2->den;
	n2 = r2->num * r1->den;

	if (n1 < n2) 
		return -1;
		
	if (n1 > n2) 
		return 1;
		
	return 0;	
}


int soma_r (struct racional *r1, struct racional *r2, struct racional *r3)
{
	if (!(valido_r(r1) && valido_r(r2)))
		return 0;
	
	r3->den = r1->den * r2->den;
	r3->num = r1->num * r2->den + r2->num * r1->den;
	
	simplifica_r(r3);
	
	return 1;
}


int subtrai_r (struct racional *r1, struct racional *r2, struct racional *r3)
{	
	if (!(valido_r(r1) && valido_r(r2)))
		return 0;
	/*soma com o opsto do segundo termo*/
	r2->num = -r2->num;
	
	soma_r(r1, r2, r3);
	
	/*volta segundo termo ao normal*/
	r2->num = -r2->num;
	
	return 1;
}


int multiplica_r (struct racional *r1, struct racional *r2, struct racional *r3)
{
	if (!(valido_r(r1) && valido_r(r2)))
		return 0;
	
	r3->num = r1->num * r2->num;
	r3->den = r1->den * r2->den;
	
	simplifica_r(r3);
	
	return 1;
}


int divide_r (struct racional *r1, struct racional *r2, struct racional *r3)
{
	long aux;

	if (!(valido_r(r1) && valido_r(r2)))
		return 0;
	
	/*inverte r2*/
	aux = r2->num;
	r2->num = r2->den;
	r2->den = aux;
	
	multiplica_r(r1, r2, r3);
	
	/*desinverte r2*/
	r2->den = r2->num;
	r2->num = aux;
	
	return 1;
}
