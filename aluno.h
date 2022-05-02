#ifndef ALUNO_H
#define ALUNO_H

#define NUM_ALUNOS_POR_TELA 4
#define ARQUIVO_BANCO "banco_de_alunos"

    // definição da struct
    struct Aluno {	// tipo de dados
        char nome[40];	//Nome do aluno
        char pais[80];	//Nome dos pais do aluno
        int ativo;	//Numero do aluno
        float notas;	//Nota do aluno
        char area;	//Area cientifica - I ou M ou F
    };

    extern FILE *p_arq;	// arquivo com a base de alunos

    // Funções auxiliares
    int			grava_alunos(const struct Aluno *aluno, int num);
    int			le_alunos(struct Aluno *aluno, int num);
    int			vai_ao_inicio_do_banco(void);
    int			vai_ao_aluno_N(long n);
    int			vai_ao_fim_do_banco(void);
    struct Aluno *	busca_aluno_por_nome(char *nome);
    int			apaga_aluno_por_nome(char *nome);
    int			imprime_alunos(struct Aluno *aluno, int num, int ord);
    char *		tira_newline(char *str);

    // Funções 'principais', chamadas a partir do menu
    void inscrever(void);
    void anular(void);
    void gravar(void);
    void listagem(void);
    void propinas(void);
    void sair(void);
#endif
