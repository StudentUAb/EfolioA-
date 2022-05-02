#include <stdio.h>
#include <ctype.h>
#include "aluno.h"

void anular()
{
    struct Aluno aluno, *encontrado;

    printf("\n-------------- Remoção de Aluno --------------\n\n");
    printf("\n");

    printf("\n Nome do aluno ........: ");
    fflush(stdin);
    //captura a String nome do aluno do teclado
    fgets(aluno.nome, sizeof(aluno.nome), stdin);
    tira_newline(aluno.nome);

    encontrado = busca_aluno_por_nome(aluno.nome);
    if( ! encontrado )
	printf("Este aluno já não constava do banco.\n");
    else {
	printf("Aluno a ser removido:\n\n");
	imprime_alunos(encontrado, 1, 1);
	printf("Confirma (s/n)? ");
	if( toupper(getchar()) == 'S' )
	    if( apaga_aluno_por_nome(aluno.nome) == 0 )
		printf("Aluno removido com sucesso.\n");
	    else
		printf("Houve um erro ao remover o aluno.\n");
	else
	    printf("Remoção cancelada.\n");
    }

    printf("Presione uma tecla para continuar...");
    getchar();
}
