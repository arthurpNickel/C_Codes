/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include "racional.h"

int n;

/* coloque aqui as funções auxiliares que precisar neste arquivo */

int le_v(struct racional V[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		scanf("%ld %ld", &V[i].num, &V[i].den); //ta certo?
	return 1;
}

int imprime_v(struct racional V[], int n)
{
	int i;
	printf("VETOR = ");
	for (i = 0; i < n; i++)
	{
		imprime_r(V[i]);
		printf(" ");
	}
	printf("\n");
	return 1;
}

//aqui ou no TADS?
void troca_r(struct racional *a, struct racional *b)
{
	struct racional aux = *a;
	*a = *b;
	*b = aux;
	return;
}

//select sort
int ordena_v(struct racional V[], int tam)
{
	int pos_menor, i, j;
	
	//define posição da vez que será ordenada
	for (i = 0; i < tam - 1; i++)
	{
		//procura posição do menor elemento não ordenado no vetor
		pos_menor = i;
		for (j = i + 1; j < tam; j++)
			if (compara_r(V[j], V[pos_menor]) == -1) //se V[j] for menor que menor...
				pos_menor = j;
		
		//função de troca entre rótulos	
		troca_r(&V[i], &V[pos_menor]);
	}
	
	return 0;
}

//eliminar elementos inválidos
void elimina_v(struct racional V[], int tam)
{
	int i = 0;
	int j = tam - 1;

	while (i <= j) 
	{
		if (valido_r(V[i]))
        		i++; 
    		else if (!valido_r(V[j]))
        		j--;
    		else
    		{
        		troca_r(&V[i], &V[j]);
        		i++;
        		j--;
    		}
	}
	return; //!!!
}

struct racional soma_v(struct racional V[], int tam)
{
	int i;
	struct racional vsoma;
	
	if (tam == 0)
	{
		vsoma.num = 0;
		vsoma.den = 1;
	}
	else
	{	
		vsoma = V[0];
		for (i = 1; i < tam; i++)
			soma_r(vsoma, V[i], &vsoma);
	}
	return vsoma;
}


/* programa principal */
int main ()
{
	struct racional V[100];
	
	scanf("%d", &n);
	if (!( (n > 0) && (n < 100) ))
		return 0;
	
	le_v(V, n);
	imprime_v(V, n);
	
	elimina_v(V, n);

	/*conta elementos válidos*/
	int novo_tam = 0;
	while (valido_r(V[novo_tam])) novo_tam++;
	
	imprime_v(V, novo_tam);
	
	ordena_v(V, novo_tam);
	
	imprime_v(V, novo_tam);
	
	struct racional soma = soma_v(V, novo_tam);
	
	printf("SOMA = ");
	imprime_r(soma);
	printf("\n");

	return 0;
}

/*isso daqui não vai dar certo -> não considerei que vetor vai diminuindo
	for (i = 0; i < n; i++) //será que não é melhor de trás para frente?
		if (!valido_r(V[i]))
		{
			for (j = i; j < (n-invalidos); j++) //tá certa a condição?
				V[j] = J[j+1]; //assim é o melhor jeito?
			invalidos++;
		}
		
Outra forma:

while (i >= 0)
	{
		if (!valido_r(V[i]))
		{
		       //tirar elemento invalido do vetor, movendo todos os elementos da frente uma posição à esquerda
			for (j = i; j < ((n-1)-invalidos); j++) //tá certa a condição?
				V[j] = V[j+1]; //assim é o melhor jeito?
			
			invalidos++;
		}
		i--;
	}
	
Outra:
	int j = 0;
	int i;
	for (i = 0; i < n; i++)
		if (valido_r(V[i]))
		{
			V[j] = V[i];
			j++;
		}
		
E outra:

	//eliminar elementos inválidos
	int b = n - 1;
	int a = 0;
	int invalidos = 0;
	while (a < b)
	{
		while (valido_r(V[a]))
			a++;
		while (!valido_r(V[b]))
			b--;
		if (a < b)
		{
			troca_r(&V[a], &V[b]); //precisa dos &?
			a++;
			b--;
			invalidos++;
		}
	}
	
	int novo_tam = n - invalidos;
			
	*/
/*
/* Compara dois racionais r1 e r2. Retorno: -2 se r1 ou r2 for inválido,
 * -1 se r1 < r2, 0 se r1 = r2 ou 1 se r1 > r2 
int compara_r (struct racional r1, struct racional r2)
{
        if (!(valido_r(r1) && valido_r(r2)))
                return -2;
                
        long vmmc = mmc(r1.den, r2.den);
        
        
        if ( r1.num*vmmc < r2.num*vmmc )
        	return -1;
        	
        if ( r1.num*vmmc == r2.num*vmmc )
        	return 0;

        return 1;
}
*/
