#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <locale.h>

#include "funcoes_auxiliares.h"
#include "funcoes_tipoAula.h"
#include "funcoes_uc.h"
#include "funcoes_aulasOnline.h"
#include "funcoes_acessos.h"

char menu(int quantUC, int quantAulasAgendadas, int quantAulasRealizadas, int quantAulasGravadas);
char menuGestaoFicheiro();
char menuAulas(int quantAulas);
char menuGestaoAcessos();

int main()
{
    tipoUC ucs[MAX_UC];
    tipoAulasOnline *aulasOnline = NULL;
    tipoAcesso *acessos = NULL;
    int quantUC=0, quantAulas=0, quantAcessos=0, quantAulasAgendadas=0, quantAulasRealizadas=0, quantAulasGravadas=0, quantAulasDecorrer=0, pos, i;
    char opcao, opcaosubMenu, designacao[MAX_STRING];
    setlocale(LC_ALL, "");

    leFichBinUCs(ucs, &quantUC);
    aulasOnline = leFichBinAulasOnline(aulasOnline, &quantAulas);
    acessos=leFichBinAcessos(acessos, &quantAcessos);

    for(i=0; i<quantAulas; i++)
    {
        if(strcmp(aulasOnline[i].estado, "A") == 0)
        {
            quantAulasAgendadas++;
        }

        if(strcmp(aulasOnline[i].estado, "R") == 0)
        {
            quantAulasRealizadas++;
        }

        if(strcmp(aulasOnline[i].estado, "D") == 0)
        {
            quantAulasDecorrer++;
        }

        if(strcmp(aulasOnline[i].gravacao, "S") == 0 && strcmp(aulasOnline[i].estado, "R") == 0)
        {
            quantAulasGravadas++;
        }
    }

    do
    {
        opcao = menu(quantUC, quantAulasAgendadas, quantAulasRealizadas, quantAulasGravadas);
        switch(opcao)
        {
        case 'A':
            gestaoUCs(ucs, &quantUC);
            break;

        case 'B':
            printf("\n\n");
            do
            {
                opcaosubMenu = menuAulas(quantAulas);
                switch(opcaosubMenu)
                {
                case 'A':
                    aulasOnline = agendaAula(aulasOnline, &quantAulas,  ucs, quantUC);
                    break;

                case 'B':
                    if(quantAulasAgendadas > 0)
                    {
                        printf("Pretende (A)lterar ou (E)liminar uma aula: ");
                        scanf("%c", &opcaosubMenu);
                        limpaBufferStdin();
                        opcaosubMenu = toupper(opcaosubMenu);
                        switch(opcaosubMenu)
                        {
                            case 'A':
                                editarAula(aulasOnline, quantAulas, quantAulasAgendadas, ucs, quantUC);
                            break;

                            case 'E':
                                eliminaAula(aulasOnline, &quantAulas);
                            break;

                            default:
                            printf("Opção inválida!\n\n");
                            break;
                        }
                    }
                    else
                    {
                        printf("Não existem aulas agendadas registadas no sistema para edição.\n\n");
                    }
                    break;

                case 'C':
                    if(quantAulas > 0 && quantAulasAgendadas > 0)
                    {
                        iniciarAula(aulasOnline, quantAulas, &quantAulasDecorrer, &quantAulasAgendadas);
                    }
                    else
                    {
                        printf("Não existem aulas agendadas para registar o seu início.\n\n");
                    }
                    break;

                case 'D':
                    if(quantAulas > 0 && quantAulasDecorrer > 0)
                    {
                        finalizarAula(aulasOnline, quantAulas, &quantAulasDecorrer, &quantAulasRealizadas, &quantAulasGravadas);
                    }
                    else
                    {
                        printf("Não existem aulas a decorrer para dar o seu término.\n\n");
                    }
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
                    acessos = registarAcesso(acessos, &quantAcessos, aulasOnline, &quantAulas, quantAulasDecorrer, quantAulasGravadas);
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
char menu(int quantUC, int quantAulasAgendadas, int quantAulasRealizadas, int quantAulasGravadas)
{
    char opcao;
    printf("------------------ Menu Principal ------------------\n\n");
    printf("Unidades Curriculares: %d \tAulas agendadas: %d\n", quantUC, quantAulasAgendadas);
    printf("Aulas realizadas: %d\t\tAulas gravadas: %d\n\n", quantAulasRealizadas, quantAulasGravadas);
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
char menuAulas(int quantAulas)
{
    char opcao;
    printf("------------------ Aulas Online ------------------\n\n");
    printf("Quantidade de aulas registadas: %d\n\n", quantAulas);
    printf("\tA - Agendar aula online\n\tB - Alterar/Eliminar aula agendada\n\tC - Registar inicio de uma aula\n");
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
