#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "aluno.h"

/************************************************************
    Variáveis globais
************************************************************/
FILE *p_arq;

/************************************************************
    Funções auxiliares
************************************************************/

//--------------------------------------------------
// Retira caractere de newline do final de uma
// string (se houver um lá).
//--------------------------------------------------
char *tira_newline(char *str)
{
    char *s = str;

    while( *s )
	++s;

    if( s > str && *--s == '\n' )
	*s = '\0';

    return str;
}

//--------------------------------------------------
// Grava um ou mais alunos
//
// Retorna o número de alunos efetivamente gravados.
//--------------------------------------------------
int grava_alunos(const struct Aluno *aluno, int num)
{
    return fwrite(aluno,
	    (long) sizeof(struct Aluno),
	    num,
	    p_arq);
}

//--------------------------------------------------
// Lê um ou mais alunos
//
// retorna o número de alunos efetivamente lidos.
//--------------------------------------------------
int le_alunos(struct Aluno *aluno, int num)
{
    return fread(aluno,
	    (long) sizeof(struct Aluno),
	    num,
	    p_arq);
}

//--------------------------------------------------
// Posiciona o arquivo de modo a ler ou a sobrescrever
// o n-ésimo registro de aluno nele contido
//
// retorna 0 se conseguiu, -1 em caso de erro.
//--------------------------------------------------
int vai_ao_aluno_N(long n)
{
    return (fseek(p_arq,
	    n * (long)sizeof(struct Aluno),
	    SEEK_SET) == -1) ?
	-1 : 0;
}

//--------------------------------------------------
// Posiciona o arquivo de modo ler/gravar do início
//
// retorna 0 se conseguiu, -1 em caso de erro.
//--------------------------------------------------
int vai_ao_inicio_do_banco(void)
{
    return fseek(p_arq, 0L, SEEK_SET);
}

//--------------------------------------------------
// Posiciona o arquivo de modo a gravar ao final
//
// retorna 0 se conseguiu, -1 em caso de erro.
//--------------------------------------------------
int vai_ao_fim_do_banco(void)
{
    return (fseek(p_arq, 0L, SEEK_END) == -1) ?
	-1 : 0;
}

//--------------------------------------------------
// busca um aluno por seu nome, e retorna um
// ponteiro para uma área estática contendo os
// dados relativos a esse aluno
//--------------------------------------------------
struct Aluno *busca_aluno_por_nome(char *nome)
{
    // Área estática contendo o aluno a ser retornado
    static struct Aluno aluno;

    // Temos que procurá-lo desde o começo do arquivo
    int ret = vai_ao_inicio_do_banco();

    if( ret )
	return (struct Aluno *) 0;

    while( le_alunos(& aluno, 1) == 1 )
    {
	// Se for o que procuramos, termina por aqui
	if( strcmp(nome, aluno.nome) == 0 )
	    return & aluno;
    }

    // Se saiu do while significa que não o encontramos:
    // retornamos um ponteiro nulo, então.
    return (struct Aluno *) 0;
}

//--------------------------------------------------
// Apaga um aluno cujo nome é fornecido
//--------------------------------------------------
int apaga_aluno_por_nome(char *nome)
{
    FILE   *novo_arq;
    struct Aluno aluno;

    printf("Apagando '%s'...\n", nome);
    getchar();

    novo_arq = fopen("novo_banco", "a+");
    if( novo_arq == NULL )
    {
	perror("Erro ao criar o novo banco de alunos");
	getchar();
	return errno;
    }

    // Temos que procurá-lo desde o começo do arquivo
    int ret = vai_ao_inicio_do_banco();

    if( ret )
    {
	perror("Erro ao voltar ao início do banco de alunos");
	getchar();
	return errno;
    }

    printf("Entrando no while()\n");
    getchar();
    while( le_alunos(& aluno, 1) == 1 )
    {
	// Só gravamos se o nome for diferente do que procuramos
	if( strcmp(nome, aluno.nome) != 0 )
	{
	    if( fwrite(& aluno, sizeof(struct Aluno), 1, novo_arq) != 1 )
	    {
		perror("Erro ao gravar o aluno");
		getchar();
		return errno;
	    }
	}
    }
    // parte criada para debug na eliminação do aluno no 
    // arquivo binário, contém dados em formato binário.
    // Por exemplo, o número do aluno é um int. No caso do aluno 1, 
    // ao contrario de estar armazenado um caracter 1 (ascii 0x31 -> 49, em decimal -> byte = 49), 
    // o que fica armazenado é o número 1 (byte = 1).
    
    printf("Saí do while()\n");
    getchar();
    // Se saiu do while significa que tudo correu bem.

    // Aqui é onde fecha o arquivo anterior
    // renomea o novo banco, e atribuir o novo
    // arquivo ao ponteiro global de arquivo corrente.
    printf("Fechando o arquivo.\n");
    getchar();
    fclose(p_arq);
    fflush(novo_arq);

    printf("Renomeando 'novo_banco' como '" ARQUIVO_BANCO "'.\n");
    getchar();
    if( rename("novo_banco", ARQUIVO_BANCO) )
    {
	perror("Não consegui renomear 'novo banco' para '"
		ARQUIVO_BANCO "'");
	getchar();
	fprintf(stderr, "Apagando '%s'.\n", ARQUIVO_BANCO);
	getchar();
	unlink("novo_banco");
	return -1;
    }
    printf("Reatribuindo o file pointer.\n");
    getchar();

    p_arq = novo_arq;

    // Retornamos zero, para indicar que tudo correu bem.
    return 0;
}

//--------------------------------------------------
// Mostra os dados de um ou mais alunos na tela
//--------------------------------------------------
int imprime_alunos(struct Aluno *aluno, int num, int ord)
{
    int i = 0;

    while( i < num )
    {
	//  As 2 strings constantes seguidas, sem
	// vírgulas nem nada, são concatenadas na hora da
	// compilação. Ou seja, são tratadas como uma só.
	printf("%dº Aluno: %s\n\tpais: %s\n\tAtivo: %d\n"
		"\tnota: %.2f\n\tCarteira: %c\n",
	    ord++,
	    aluno->nome,
	    aluno->pais,
	    aluno->ativo,
	    aluno->notas,
	    aluno->area
	);

	// NUM_ALUNOS_POR_TELA alunos por tela
	if( (++i % NUM_ALUNOS_POR_TELA) == 0 )
	{
	    printf("Presione uma tecla para continuar...");
	    getchar();
	}
    }

    // Se não fez isso na última iteração do loop,
    // espera até que uma tecla seja pressionada.
    if( (num > NUM_ALUNOS_POR_TELA) &&
	((i % NUM_ALUNOS_POR_TELA) != 0) )
    {
	printf("Presione uma tecla para continuar...");
	getchar();
    }
    return i;
}

/************************************************************
    Funções principais
************************************************************/

//--------------------------------------------------
// Faz o que deve ser feito ao término
// da execução do programa
//--------------------------------------------------
void sair()
{
    printf("Obrigado por utlizar nosso sistema...\n");

    // fechando arquivo
   
    fclose(p_arq);
}
