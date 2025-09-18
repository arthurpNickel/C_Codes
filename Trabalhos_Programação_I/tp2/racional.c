/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/


/* estrutura que representa um número racional */

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max)
{
	return min + rand()%(max - min + 1);
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
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

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
	return (a * b / mdc(a, b));
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido.
 * Um racional é inválido se seu denominador for zero */
int valido_r (struct racional r)
{
	if (r.den == 0)
		return 0;
	return 1;
}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
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

/* implemente as demais funções de racional.h aqui */

/* Retorna o numerador do racional r */
long numerador_r (struct racional r)
{
        return r.num;
}
/* Retorna o denominador do racional r */
long denominador_r (struct racional r)
{
        return r.den;
}

/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r (long numerador, long denominador)
{
        struct racional r;
        r.num = numerador;
        r.den = denominador;
	return r;
}

/* Retorna um número racional aleatório na forma simplificada.
 * Deve ser sorteado o numerador e depois o denominador.
 * o racional gerado pode ser válido ou inválido.
 * O numerador e o denominador devem ser inteiros entre min e max. */
struct racional sorteia_r (long min, long max)
{
	struct racional r;
	r.num = aleat(min, max);
	r.den = aleat(min, max);
	return simplifica_r(r);
}

/* Imprime um racional r, respeitando estas regras:
   - o racional deve ser impresso na forma simplificada;
   - não imprima espaços em branco e não mude de linha;
   - a saída deve ter o formato "num/den", a menos dos casos abaixo:
     - se o racional for inválido, imprime a mensagem "NaN" (Not a Number);
     - se o numerador for 0, imprime somente "0";
     - se o denominador for 1, imprime somente o numerador;
     - se o numerador e denominador forem iguais, imprime somente "1";
     - se o racional for negativo, o sinal "-" vem antes do numerador;
     - se numerador e denominador forem negativos, o racional é positivo. */
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
        printf("%ld/%ld", r.num, r.den); //mudei aqui
        return;
}

/* Compara dois racionais r1 e r2. Retorno: -2 se r1 ou r2 for inválido,
 * -1 se r1 < r2, 0 se r1 = r2 ou 1 se r1 > r2 */
int compara_r(struct racional r1, struct racional r2) 
{
	if (!(valido_r(r1) && valido_r(r2)))
		return -2;

	r1 = simplifica_r(r1); //!!!!
	r2 = simplifica_r(r2);
	       
	long n1 = r1.num * r2.den;
	long n2 = r2.num * r1.den;

	if (n1 < n2) 
		return -1;
		
	if (n1 > n2) 
		return 1;
		
	return 0;
}


//Não está simplificado
/* Retorna a soma dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int soma_r (struct racional r1, struct racional r2, struct racional *r3)
{	
	if (!(valido_r(r1) && valido_r(r2))) //Parênteses?
		return 0;
	r3->den = r1.den*r2.den;
	r3->num = r1.num*r2.den + r2.num*r1.den;
	*r3 = simplifica_r(*r3);
	if (r3->num == 0) //Parênteses?
		return 0;
	return 1;
}

/* Retorna a subtracao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int subtrai_r (struct racional r1, struct racional r2, struct racional *r3)
{	
	r2.num = -r2.num;
	soma_r(r1, r2, r3); //*?
	if (!(valido_r(r1) && valido_r(r2)) || r3->num == 0) //Parênteses?
		return 0;
	return 1;
}

/* Retorna a multiplicacao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int multiplica_r (struct racional r1, struct racional r2, struct racional *r3)
{
	r3->num = r1.num*r2.num;
	r3->den = r1.den*r2.den;
	*r3 = simplifica_r(*r3);
	if (!(valido_r(r1) && valido_r(r2)) || r3->num == 0) //Parênteses?
		return 0;
	return 1;
}

/* Retorna a divisao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int divide_r (struct racional r1, struct racional r2, struct racional *r3)
{
	/*inverte segundo racional*/
	int aux = r2.num;
	r2.num = r2.den;
	r2.den = aux;
	
	multiplica_r(r1, r2, r3);
	if (!(valido_r(r1) && valido_r(r2)) || r3->num == 0) //Parênteses?
		return 0;
	return 1;
}

