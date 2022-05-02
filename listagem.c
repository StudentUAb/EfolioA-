#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"

void listagem()
{
    struct Aluno aluno;
    int i = 0;

    if( vai_ao_inicio_do_banco() ) {
	perror("Erro ao reposicionar o arquivo no início");
	return;
    }

    printf("Listagem de inscrições por aluno\n");

    while( le_alunos(& aluno, 1) == 1 )
    {
	imprime_alunos(& aluno, 1, ++i);

	// NUM_ALUNOS_POR_TELA alunos por tela
	if( (i % NUM_ALUNOS_POR_TELA) == 0 )
	{
	    printf("Presione uma tecla para continuar...");
	    getchar();
	}
    }

    // Se não fez isso na última iteração do loop,
    // espera até que uma tecla seja pressionada.
    if( (i % NUM_ALUNOS_POR_TELA) != 0 )
    {
	printf("Presione uma tecla para continuar...");
	getchar();
    }
}
