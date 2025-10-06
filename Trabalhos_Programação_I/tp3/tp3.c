/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 09/09/2025 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

void imprime_v(struct racional *v[], int tam)
{
	int i;
	printf("VETOR = ");
	for (i = 0; i < tam-1; i++)
	{
		imprime_r(v[i]);
		printf(" ");
	}
	if (tam > 0)
		imprime_r(v[tam-1]);
	printf("\n");
}

/*Entender porque isso dá certo*/

/*troca endereços entre dois PONTEIROS de racionais*/
void troca_r(struct racional **a, struct racional **b)
/* a = endereço do rótulo do vetor
  *a = ponteiro que aponta para conteúdo do rótulo do vetor (que é endereço do racional)
  **a = ponteiro de ponteiro, que aponta para o racional em si que se quer guardar*/
{
	struct racional *aux = *a;
	*a = *b;
	*b = aux;
}

/*elimina elementos inválidos do vetor, colocando todos os inválidos à direita*/
void elimina_v(struct racional *v[], int tam)
{
	int i = 0;
	int j = tam - 1;
	
	while (i < j) 
	{
		if (valido_r(v[i]))
        		i++; 
    		else if (!valido_r(v[j]))
        		j--;
    		else
    		{
        		/*mandar endereços, pois se quer trocar os endereços, não racionais*/
        		troca_r(&v[i], &v[j]);
        		i++;
        		j--;
    		}
	}
}

void particiona_v(struct racional *v[], int esq, int dir, int *pos_pivo)
{
	struct racional *pivo = v[esq];
	int i = esq + 1;
	int j = dir;
	
	while (1) {
        // avança i até achar algo >= pivo
        while (i <= dir && compara_r(v[i], pivo) == -1) i++;

        // recua j até achar algo <= pivo
        while (j >= esq && compara_r(v[j], pivo) == 1) j--;

        if (i >= j) break; // terminou

        troca_r(&v[i], &v[j]);
        i++;
        j--;
    }
	
	troca_r(&v[esq], &v[j]);
	*pos_pivo = j;
}

/*QuickSort implementado recursivamente, ordenando de forma crescente*/
void ordena_v(struct racional *v[], int esq, int dir)
{
	int pos_pivo;	
	
	if (esq < dir)
	{
		particiona_v(v, esq, dir, &pos_pivo);
		
		ordena_v(v, esq, pos_pivo-1);
		
		ordena_v(v, pos_pivo+1, dir);
	}
}

//Deu alguma merda muito errada
/*retorna a soma dos elementos de um vetor de racionais*/
void soma_v(struct racional *v[], struct racional **soma, int tam)
{
	int i;
	struct racional *novo, *antigo;
	
	for (i = 0; i < tam; i++) 
	{
	novo = cria_r(0, 1);
        
	if (novo == NULL) 
	{
		destroi_r(soma);
		return;
        }

	if (!soma_r(*soma, v[i], novo)) 
	{
		destroi_r(&novo);
		destroi_r(soma);
		return;
	}
	
	antigo = *soma;
	*soma = novo;
	destroi_r(&antigo);
	}
	
	//ver se agrega caso de NULL
	
	//free soma??
}

void libera_v(struct racional *v[], int tam) //precisa de caso de sucesso ou não???
{
	int i;
	for (i = 0; i < tam; i++)
		destroi_r(&v[i]);
}

/* programa principal */
int main ()
{
	/*lê tamanho e testa se é válido*/
	int n;
	scanf("%d", &n);
	
	if ((n < 0) || (n > 100))
		return 1;
	
	/*cria ponteiro para o primeiro elemento do vetor (que é um ponteiro)*/
	struct racional **v;
	
	/*aloca n espaços para o ponteiro para ponteiro v e testa
	 *ou seja, aloca n espaços de ponteiro para racional para *v e manda o endereço deles para v~*/
	if (!(v = malloc(sizeof(struct racional*)*n)))
		return 1;
	
	/*Modular isso*/
	/*cada ponteiro do vetor de structs recebe um endereço para apontar, 
	  com uma certa struct lida do teclado*/
	int i;
	long num, den;
	for (i = 0; i < n; i++)
	{
		scanf("%ld %ld", &num, &den);
		v[i] = cria_r(num, den);
	}
	
	imprime_v(v, n);
	
	elimina_v(v, n);
	
	//Precisa mesmo????
	/*conta elementos válidos*/
	int novo_tam = 0;
	while ((novo_tam < n) && valido_r(v[novo_tam])) novo_tam++;
	
	imprime_v(v, novo_tam);
	
	ordena_v(v, 0, novo_tam-1);
	
	imprime_v(v, novo_tam);
	
	struct racional *soma;
	//inicializa soma zerada
	soma = cria_r(0, 1); 
	//if se der errado?
	
	soma_v(v, &soma, novo_tam);
	
	printf("SOMA = ");
	imprime_r(soma);
	printf("\n");
	
	libera_v(v, n);
	
	imprime_v(v, novo_tam);

	free(v); //free ou destroi???
	
	free(soma);
	
	return 0;
}

/*Porque isso deu errado??

void troca_r(struct racional **a, struct racional **b)
{
    struct racional *aux;
    *aux = *a;
    *a = *b;
    *b = *aux;
}

while (((compara_r(v[*pos_pivo],v[i]) == 0) || (compara_r(v[*pos_pivo],v[i]) == 1)) && (i<dir)) i++;
		while (compara_r(v[*pos_pivo], v[j]) == -1) j--;
		
void particiona_v(struct racional *v[], int esq, int dir, int *pos_pivo)
{
	int i = esq + 1;
	int j = dir;
	*pos_pivo = esq;
	
	while (i < j)
	{
		while (i <= dir && compara_r(v[i], v[*pos_pivo]) == -1) i++;   // v[i] < pivo
		while (j >= esq && compara_r(v[j], v[*pos_pivo]) == 1) j--;    // v[j] > pivo
		if (i < j)
		{
			troca_r(&v[i], &v[j]);
			i++;
			j--;	
		}
	}
	
	troca_r(&v[esq], &v[j]);
	*pos_pivo = j;
}

void particiona_v(struct racional *v[], int esq, int dir, int *pos_pivo)
{
	struct racional *pivo = v[esq];
	int i = esq + 1;
	int j = dir;
	
	while (i < j)
	{
		while (i < dir && compara_r(v[i], pivo) == -1) i++;   // v[i] < pivo
		while (j > esq && compara_r(v[j], pivo) == 1) j--;    // v[j] > pivo
		if (i < j)
		{
			troca_r(&v[i], &v[j]);
		}
	}
	
	troca_r(&v[esq], &v[j]);
	*pos_pivo = j;
}

ISSO FUNCIONA:
void particiona_v(struct racional *v[], int esq, int dir, int *pos_pivo)
{
    struct racional *pivo = v[esq];
    int i = esq + 1;
    int j = dir;

    while (1) {
        // avança i até achar algo >= pivo
        while (i <= dir && compara_r(v[i], pivo) == -1) i++;

        // recua j até achar algo <= pivo
        while (j >= esq && compara_r(v[j], pivo) == 1) j--;

        if (i >= j) break; // terminou

        troca_r(&v[i], &v[j]);
        i++;
        j--;
    }

    // coloca pivo na posição final
    troca_r(&v[esq], &v[j]);
    *pos_pivo = j;
}

*/

