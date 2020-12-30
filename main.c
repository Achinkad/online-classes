#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>
#include "funcoes_auxiliares.h"

int main()
{
    char opcao;
    setlocale(LC_ALL, "");

    do
    {
        printf("--------- Menu Principal ---------\n\n");
        printf("Unidade Curriculares: 12\tAulas agendadas: 12\n");
        printf("Aulas realizadas: 21\t\tAulas gravadas: 3\n\n");
        printf("A - Gestao de Unidades Curriculares\nB - Gestao de Aulas Online\nC - Gestao de Ficheiros\n");
        printf("D - Gestao de Dados Estatisticos\nE - Gestao de Acesso as Aulas Online\n");
        printf("S - Sair\n");
        printf("\nInsira uma opcao: ");
        scanf("%c", &opcao);
        limpaBufferStdin();
        opcao = toupper(opcao);

        switch(opcao)
        {
        case 'A':
            printf("Gestao de Unidades Curriculares\n\n");
            break;

        case 'B':
            printf("Gestao de Aulas Online\n\n");
            break;

        case 'C':
            printf("Gestao de Ficheiros\n\n");
            break;

        case 'D':
            printf("Gestao de Dados Estatisticos\n\n");
            break;

        case 'E':
            printf("Gestao de Acesso as Aulas Online\n\n");
            break;

        case 'S':
            return 0;
            break;

        default:
            printf("Opcao invalida. Por favor, introduza uma opcao valida.\n\n");
            break;
        }
    }
    while(opcao != 'S');
    return 0;
}
