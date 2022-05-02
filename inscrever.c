#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"

void inscrever(){
    struct Aluno
	aluno;
    int i;
    int result;

    printf("\n-------------- Cadastro de Aluno --------------\n\n");
    printf("\n");

    fflush(stdin);
    printf("\n Nome do aluno ........: ");
    fflush(stdout);
    //pega a String nome do aluno do teclado
    fgets(aluno.nome, sizeof(aluno.nome), stdin);
    tira_newline(aluno.nome);

    printf("\n Pais do aluno ........: ");
    fflush(stdout);
    //pega a String nome do aluno do teclado
    fgets(aluno.pais, sizeof(aluno.pais), stdin);
    tira_newline(aluno.pais);

    printf("\nNumero do aluno .......: ");
    scanf("%d", &aluno.ativo);
    getchar();

    printf("\n Notas do aluno .......: ");
    scanf("%f", &aluno.notas);
    getchar();

    printf("\nArea cientifica - I ou M ou F .......: ");
    scanf("%c", &aluno.area);
    getchar();

    printf("\n");
    printf("\n");

    printf("\n\n-------------- Mostrando os Dados de Aluno Cadastrado --------------\n\n");
    printf("Nome do aluno ..........: %s \n", aluno.nome);
    printf("Pais do aluno ..........: %s \n", aluno.pais);
    printf("Numero do aluno ........: %d \n", aluno.ativo);
    printf("Nota do aluno ..........: %f \n", aluno.notas);
    printf("Area cientifica - I ou M ou F......: %c \n", aluno.area);
    printf("\n\n-Presione uma tecla para continuar...\n\n-");
    printf("\n");
    printf("\n");
    printf("\n");
    getchar();

    printf("\n\n---- Salvando os Dados de Aluno no Arquivo alunos6.txt ----\n\n");

    if( vai_ao_fim_do_banco() || (grava_alunos(& aluno, 1) != 1) )
	perror("Erro ao cadastrar o aluno");
    else
	printf("------ Cadastro executado com SUCESSO!!! ------\n\n");
    printf("Presione uma tecla para continuar...");
    getchar();
}
