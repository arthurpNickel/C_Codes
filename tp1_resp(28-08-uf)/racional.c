/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>


/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

//terminado
/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max)
{
  return min + rand()%(max - min + 1);
}

//terminado
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
	return a
}

//terminado
/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
  return (a * b / mdc(a, b));
}

//terminado
//avaliar se vai funcionar o mdc
/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r)
{
        int mdc;
        if (valido_r(r))
        {
		mdc = mdc(r.num, r.den); //módulo deles??
		r.num = r.num/mdc;
		r.den = r.den/mdc;
		if (((r.num < 0) && (r.den < 0)) || ((r.num > 0) && (r.den < 0))) //colocar negativo no numerador ou tirar do número
		{
			r.num = -r.num;
			r.den = -r.den;
		}
	}
	return r
}

/* implemente as demais funções aqui */

#ifndef RACIONAL
#define RACIONAL

/* estrutura que representa um número racional */
struct racional {
  long num;          /* numerador   */
  long den;          /* denominador */
};

//Terminado
/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r (long numerador, long denominador);
{
        struct racional r;
        r.num = numerador;
        r.den = denominador;
	return r;
}

//Terminado
/* Retorna 1 se o racional r for válido ou 0 se for inválido.
 * Um racional é inválido se seu denominador for zero */
int valido_r (struct racional r);
{
	if (r.den = 0)
		return 0;
	return 1;
}

//Terminado
/* Retorna um número racional aleatório na forma simplificada.
 * Deve ser sorteado o numerador e depois o denominador.
 * o racional gerado pode ser válido ou inválido.
 * O numerador e o denominador devem ser inteiros entre min e max. */
struct racional sorteia_r (long min, long max);
{
	struct racional r;
	r.num = aleat(min, max);
	r.den = aleat(min, max);
	return simplifica_r(r);
}

//Terminado
/* Imprime um racional r, respeitando estas regras:
   - o racional deve ser impresso na forma simplificada;
   - não imprima espaços em branco e não mude de linha;
   - a saída deve ter o formato "num/den", a menos dos casos abaixo:
     - se o racional for inválido, deve imprimir a mensagem "INVALIDO";
     - se o numerador for 0, deve imprimir somente "0";
     - se o denominador for 1, deve imprimir somente o numerador;
     - se o numerador e denominador forem iguais, deve imprimir somente "1"; //simplifica_r
     - se o racional for negativo, o sinal "-" deve vir antes do numerador;  //simplifica_r
     - se numerador e denominador forem negativos, o racional é positivo. */  //simplifica_r
void imprime_r (struct racional r);
{
	simplifica_r(r);
        if (not valido_r(r))
        {
              printf("%c", "INVALIDO");
              return;
        }
        if (r.num = 0)
        {
              printf("%d", 0);
              return;
        }
        if (r.den = 1)
        {
              printf("%d", r.num);
	      return;
        }
        printf("%d %c %d", r.num, "/", r.den);
        return;
}


/* Retorna a soma dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */            //Não funciona nesse
struct racional soma_r (struct racional r1, struct racional r2);
{
	struct racional soma;
	soma.den = mmc(r1.den, r2.den);
	soma.num = r1.num*soma.den/r1.den + r2.num*soma.den/r2.den;
	return soma;
}

//Terminado
//segunda implementação
//mais otimizada!!
/* Retorna a soma dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional soma_r (struct racional r1, struct racional r2);
{
	struct racional soma;
	soma.den = r1.den*r2.den;
	soma.num = r1.num*r2.den + r2.num*r1.den;
	return soma;
}

//terminado
/* Retorna a subtração dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional subtrai_r (struct racional r1, struct racional r2);
{
	struct racional soma;
	soma.den = mmc(r1.den, r2.den);
	soma.num = r1.num*soma.den/r1.den - r2.num*soma.den/r2.den;
	return soma;
}

//terminado
/* Retorna a subtração dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional subtrai_r (struct racional r1, struct racional r2);
{
	//declarar variável
	r2.num = -r2.num;
	return soma_r(r1, r2);
}

//terminado
/* Retorna a multiplicação dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional multiplica_r (struct racional r1, struct racional r2);
{
	struct racional produto;
	produto.num = r1.num*r2.num;
	produto.den = r1.den*r2.den;
	return produto
}

//terminado
/* Retorna a divisão dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido.
 * observe que a divisão com r1 e r2 válidos pode gerar um racional inválido */
struct racional divide_r (struct racional r1, struct racional r2);
{
	struct racional quociente;
	int aux = r2.num;  //inverter segundo racional
	r2.num = r2.den;
	r2.den = r2.num;
	quociente = multiplica_r(r1, r2);
	return quociente;
}

#endif
