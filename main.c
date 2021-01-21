#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

#include "funcoes_auxiliares.h"
#include "funcoes_tipoAula.h"
#include "funcoes_uc.h"
#include "funcoes_aulasOnline.h"

char menu(int quantUC);
char menuGestaoFicheiro();
char menuAulas();

int main()
{
    tipoUC ucs[MAX_UC];
    tipoAulasOnline *aulasOnline = NULL;
    int quantUC=0, quantAulas=0;
    char opcao, opcaosubMenu;
    setlocale(LC_ALL, "");

    leFichBinUCs(ucs, &quantUC);

    do
    {
        opcao = menu(quantUC);
        switch(opcao)
        {
        case 'A':
            gestaoUCs(ucs, &quantUC);
            break;

        case 'B':
            printf("\n\n");
            do
            {
                opcaosubMenu = menuAulas();
                switch(opcaosubMenu)
                {
                case 'A':
                    aulasOnline = agendaAula(aulasOnline, &quantAulas);
                    break;

                case 'B':
                    printf("Alterar aula agendada\n\n");
                    break;

                case 'C':
                    printf("Registar início de uma aula\n\n");
                    break;

                case 'D':
                    printf("Registar o fim de uma aula\n\n");
                    break;

                case 'E':
                    listaAulas(aulasOnline, quantAulas);
                    break;

                case 'S':
                    printf("\n\n");
                    break;
                }

            }
            while(opcaosubMenu != 'S');
            break;

        case 'C':
            do
            {
                opcaosubMenu = menuGestaoFicheiro();
                switch(opcaosubMenu)
                {
                case 'E':
                    escreveFichBinUCs(ucs,quantUC);
                    break;
                case 'L':
                    leFichBinUCs(ucs,&quantUC);
                    break;
                case 'R':
                    printf("Limpar dados da Aplicação!");
                    break;
                case 'S':
                    break;
                default:
                    printf("\nOpcao Invalida!\n");
                    break;
                }
            }
            while(opcaosubMenu!='S');
            break;

        case 'D':
            printf("Gestao de Dados Estatisticos\n\n");
            break;

        case 'E':
            printf("Gestao de Acesso as Aulas Online\n\n");
            break;

        case 'S':
            break;
        default:
            printf("\nOpcao Invalida!\n");
            break;
        }
    }
    while(opcao != 'S');

    free(aulasOnline);

    return 0;
}

// Apresentação da estrutura do menu geral
char menu(int quantUC)
{
    char opcao;
    printf("------------------ Menu Principal ------------------\n\n");
    printf("Unidade Curriculares: %d \tAulas agendadas: 12\n", quantUC);
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

// Apresentação da estrutura do menu das aulas online
char menuAulas()
{
    char opcao;
    printf("------------------ Aulas Online ------------------\n\n");
    printf("\tA - Agendar aula online\n\tB - Alterar aula agendada\n\tC - Registar inicio de uma aula\n");
    printf("\tD - Registar o fim de uma aula\n\tE - Listar dados das aula online\n");
    printf("\tS - Sair\n");
    printf("\nInsira uma opcao: ");
    scanf("%c", &opcao);
    limpaBufferStdin();
    opcao = toupper(opcao);
    return opcao;
}

// Apresentação da estrutura do submenu C
char menuGestaoFicheiro()
{
    char opcao;
    printf("\n\n------------------ Gestao de Ficheiros ------------------\n\n");
    printf("\tE - Escrever Ficheiros\n");
    printf("\tL - Ler Ficheiro\n");
    printf("\tR - Reiniciar dados da Aplicacao\n");
    printf("\tS - Sair\n");
    printf("\nInsira uma opcao: ");
    scanf("%c", &opcao);
    limpaBufferStdin();
    opcao = toupper(opcao);
    return opcao;
}
