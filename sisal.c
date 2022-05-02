#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "aluno.h"

int main()
{
    int cont=1;

    p_arq = fopen(ARQUIVO_BANCO, "a+");

    //testando se o arquivo foi realmente criado
    if(p_arq == NULL)
    {
        perror("Erro na abertura do arquivo");
        return 1;
    }

    do
    {
        system("clear");
        printf("====================================================\n");
        printf("*       Efolio-A - Laboratorio de Programação      *\n");
        printf("====================================================\n");
        printf("*                                                  *\n");
        printf("*           ...Menu Principal...                   *\n");
        printf("*                                                  *\n");
        printf("*        1. Inscrever Aluno                        *\n");
        printf("*        2. Anular aluno                           *\n");
        printf("*        3. Listagem de inscrições por UC/aluno    *\n");
        printf("*        4. Cacular propinas de um aluno          *\n");
        printf("*        0. Sair                                   *\n");
        printf("====================================================\n");
        printf("Introduzir a sua opção:");
        scanf("%d", &cont);
	    getchar();
    

        switch(cont)
        {
            case 1:
                system("clear");
                inscrever();
		getchar();
                break;

            case 2:
                system("clear");
                anular();
		getchar();
                break;

            case 3:
                system("clear");
                listagem();
		getchar();
                break;

            case 4:
                system("clear");
                propinas();
		getchar();
                break;

            case 0:
                system("clear");
                sair();
                break;

            default:
                printf("Digite uma opcao valida\n");
                getchar();
        }
    } while(cont);
}
