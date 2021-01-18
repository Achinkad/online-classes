#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

#include "funcoes_auxiliares.h"
#include "funcoes_tipoAula.h"
#include "funcoes_uc.h"

int main()
{
    tipoUC ucs[MAX_UC];
    int quantUC=0;
    char opcao;
    setlocale(LC_ALL, "");

    opcao = menu();
    verificaOpcao(opcao, ucs, quantUC);

    return 0;
}

// Apresentação da estrutura do menu
char menu()
{
    char opcao;
    printf("------------------ Menu Principal ------------------\n\n");
    printf("Unidade Curriculares: 12\tAulas agendadas: 12\n");
    printf("Aulas realizadas: 21\t\tAulas gravadas: 3\n\n");
    printf("\tA - Gestao de Unidades Curriculares\n\tB - Gestao de Aulas Online\n\tC - Gestao de Ficheiros\n");
    printf("\tD - Gestao de Dados Estatisticos\n\tE - Gestao de Acesso as Aulas Online\n");
    printf("\tS - Sair\n");
    printf("\nInsira uma opcao: ");
    scanf("%c", &opcao);
    limpaBufferStdin();
    opcao = toupper(opcao);
    return opcao;
}

// Verifica a opção escolhida na função "menu"
void verificaOpcao(char opcao, tipoUC ucs[MAX_UC], int quantUC)
{
    if(opcao == 'A' || opcao == 'B' || opcao == 'C' || opcao == 'D' || opcao == 'E' || opcao == 'S')
    {
        switch(opcao)
        {
        case 'A':
            gestaoUCs(ucs,quantUC);
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
            break;
        }
    }
    else
    {
        printf("Opcao invalida. Por favor, insira uma opcao valida: ");
        scanf("%c", &opcao);
        limpaBufferStdin();
        opcao = toupper(opcao);
        verificaOpcao(opcao, ucs, quantUC);
    }
}
