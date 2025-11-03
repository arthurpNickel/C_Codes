/*Interface pela qual a efermeira chefe irá interagir com o heap*/
#include <stdio.h>
#include <heap.h>

/*Chama a função que remove o paciente com maior prioridade da fila e imprime.
 *Caso a fila esteja vazia, avisa.
 **/
void remove()
{

}

/*Chama a função que insere um novo paciente na fila.
 *Pede o nome do paciente para a enfermeira.
 **/
void insere()
{

}

/*Chama a função que altera a prioridade de um paciente já existente na fila.
 *Pede o nome do paciente para a enfermeira.
 **/
void altera()
{

}

/*Chama a função que imprime a fila de pacientes.
 **/
void imprime() //acho que nem precisa
{

}

/*Chama a função que inicializa a fila de pacientes.
 **/
void inicializa() //acho que nem precisa
{

}

/*Chama a função que libera a fila de pacientes.
 **/
void libera()
{

}

/*Chama a função que verifica se a fila está ordenada por prioridade.
 *Informa a enfermeira do resultado.
 **/
void verifica()
{

}

/*Chama a função que transforma o conjunto de pacientes em uma fila ordenada por prioridade.
 **/
void heapfica()
{

}

/*Chama a função que coloca o primeiro paciente em sua ordem de prioridade correta.
 **/
void sacode()
{
	
}

/*Chama a função que ordena a fila de pacientes por ordem crescente de prioridade.
 **/
void ordena()
{
	
}

int main ()
{
	/*While com diversos if's
	 *O if que entrar será uma ação que se pode fazer com o heap
	 *A enfermeira irá discar um número e em seguida fazer a ação
	 *Tudo cheio de printf e bem guiado
	 *Encapsular ações em funções
	 *Ordem:Remover, Inserir, Alterar, Imprimir, Inicializar?, Encerrar, Verificar,
	 *Heapficar, Sacodir, Ordenar
	 
	 *Pensar na comparação que professor quer
	 	*Outra interface,dentro do mesmo programa? -> if
	 **/
	 
	int codigo;
	
	do {
		printf("Entre com o código de acordo com a ação que você quer realizar na fila:"\n\n);

		printf("0, se quiser encerrar a fila e sair do programa"\n\n);

		printf("1, se quiser mostrar o paciente com maior prioridade e removê-lo da fila"\n);

		printf("2, se quiser inserir um novo paciente na fila"\n);
		
		printf("3, se quiser alterar a prioridade de um paciente já existente na fila"\n);
		
		printf("4, se quiser imprimir a fila de pacientes"\n);
		
		printf("5, se quiser inicializar a fila de pacientes"\n);
		
		printf("6, se quiser verificar se a fila está ordenada por prioridade"\n);
		
		printf("7, se quiser transformar a o conjunto de pacientes em uma fila ordenada por prioridade"\n);
		
		printf("8, se quiser colocar o primeiro paciente em sua ordem de prioridade correta"\n);
		
		printf("9, se quiser ordenar a fila de pacientes por ordem crescente de prioridade"\n);
		
		
		scanf("%d", codigo);
		
		if (codigo == 0) break;
		
		else if (codigo == 1) remove();

		else if (codigo == 2) insere();
		
		else if (codigo == 3) altera();
		
		else if (codigo == 4) imprime();
		
		else if (codigo == 5) inicializa();
		
		else if (codigo == 6) verifica();
		
		else if (codigo == 7) heapfica();
		
		else if (codigo == 8) sacode();
		
		else if (codigo == 9) ordena();
		
		else printf("Código inválido, tente novamente."\n);
		
	} while (codigo != 0);
	
	return 0;
}
