#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

#include "funcoes_auxiliares.h"
#include "funcoes_tipoAula.h"
#include "funcoes_uc.h"
#include "funcoes_aulasOnline.h"
#include "funcoes_acessos.h"

char menu(int quantUC, int quantAulas);
char menuGestaoFicheiro();
char menuAulas();
char menuGestaoAcessos();

int main()
{
    tipoUC ucs[MAX_UC];
    tipoAulasOnline *aulasOnline = NULL;
    tipoAcesso *acessos = NULL;
    int quantUC=0, quantAulas=0, quantAcessos=0;
    char opcao, opcaosubMenu;
    setlocale(LC_ALL, "");

    leFichBinUCs(ucs, &quantUC);
    aulasOnline=leFichBinAulasOnline(aulasOnline, &quantAulas);
    acessos=leFichBinAcessos(acessos, &quantAcessos);

    do
    {
        opcao = menu(quantUC, quantAulas);
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
                    escreveFichBinAulasOnline(aulasOnline, quantAulas);
                    escreveFichBinAcessos(acessos, quantAcessos);
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
            do
            {
                opcaosubMenu = menuGestaoAcessos();
                switch(opcaosubMenu)
                {
                case 'A':
                    acessos = registarAcesso(acessos, &quantAcessos, aulasOnline, &quantAulas);
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
char menu(int quantUC, int quantAulas)
{
    char opcao;
    printf("------------------ Menu Principal ------------------\n\n");
    printf("Unidade Curriculares: %d \tAulas agendadas: %d\n", quantUC, quantAulas);
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

// Apresentação da estrutura do submenu das aulas online
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

// Apresentação da estrutura do submenu dos Ficheiros
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

// Apresentação da estrutura do submenu da gestao de acessos
char menuGestaoAcessos()
{
    char opcao;
    printf("\n\n------------------ Gestao de Acessos ------------------\n\n");
    printf("\tA - Registar Acessos de Estudante\n");
    printf("\tS - Sair\n");
    printf("\nInsira uma opcao: ");
    scanf("%c", &opcao);
    limpaBufferStdin();
    opcao = toupper(opcao);
    return opcao;
}
