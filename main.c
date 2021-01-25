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
#include "funcoes_estudante.h"

char menu(int quantUC, int quantAulasAgendadas, int quantAulasRealizadas, int quantAulasGravadas);
char menuUC();
char menuGestaoFicheiro();
char menuAulas(int quantAulas);
char menuGestaoAcessos();
char menuEstudantes();

int main()
{
    tipoUC ucs[MAX_UC];
    tipoEstudantes estudante[MAX_STRING];
    tipoAulasOnline *aulasOnline = NULL;
    tipoAcesso *acessos = NULL;

    int quantUC=0, quantAulas=0, quantEstudantes=0, quantAcessos=0, quantAulasAgendadas=0, quantAulasRealizadas=0, quantAulasGravadas=0, quantAulasDecorrer=0, pos, i, numero;
    char opcao, opcaosubMenu, designacao[MAX_STRING], codigo[MAX_STRING], nome[MAX_STRING];

    setlocale(LC_ALL, "");

    leFichBinUCs(ucs, &quantUC);
    leFichBinEstudantes(estudante, &quantEstudantes);
    aulasOnline = leFichBinAulasOnline(aulasOnline, &quantAulas);
    acessos=leFichBinAcessos(acessos, &quantAcessos);

    for(i=0; i<quantUC; i++)
    {
        quantAulasAgendadas += obterTotalAgendado(ucs[i]);
        quantAulasRealizadas += obterTotalRealizado(ucs[i]);
        quantAulasGravadas += obterTotalGravadas(ucs[i]);
    }

    for(i=0; i<quantAulas; i++)
    {
        if(strcmp(aulasOnline[i].estado, "D") == 0)
        {
            quantAulasDecorrer++;
        }
    }

    do
    {
        opcao = menu(quantUC, quantAulasAgendadas, quantAulasRealizadas, quantAulasGravadas);
        switch(opcao)
        {
        case 'A':
            printf("\n");
            do{
                opcaosubMenu=menuUC();
                switch(opcaosubMenu){
                    case 'I':
                        if(quantUC<MAX_UC){
                            do{
                                lerString("Indique o código da UC: ",codigo,MAX_STRING);
                                pos=procuraUC(codigo,ucs,quantUC);
                                if(pos==-1){
                                    ucs[quantUC]=lerDadosUC();
                                    strcpy(ucs[quantUC].codigo,codigo);
                                    quantUC++;
                                }else{
                                    printf("Código UC já existe!\n");
                                }
                            }while(pos!=-1);
                        }else{
                            printf("\n\nNao e possivel adicionar mais ucs (limite de 40 atingido!\n\n");
                        }
                    break;
                    case 'L':
                        listarUCs(ucs,quantUC, aulasOnline,quantAulas);
                    break;
                    case 'E':
                        editarUC(ucs, &quantUC);
                    break;
                    case 'S':
                        printf("\n");
                    break;
                    default:
                        printf("Opção Inválida");
                    break;
                }
            }while(opcaosubMenu!='S');
            break;

        case 'B':
            printf("\n\n");
            do
            {
                opcaosubMenu = menuAulas(quantAulas);
                switch(opcaosubMenu)
                {
                case 'A':
                    aulasOnline = agendaAula(aulasOnline, &quantAulas,  ucs, quantUC, &quantAulasAgendadas);
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
                                eliminaAula(aulasOnline, &quantAulas, ucs, quantUC);
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
                        iniciarAula(aulasOnline, quantAulas, ucs, quantUC, &quantAulasDecorrer, &quantAulasAgendadas);
                    }
                    else
                    {
                        printf("Não existem aulas agendadas para registar o seu início.\n\n");
                    }
                    break;

                case 'D':
                    if(quantAulas > 0 && quantAulasDecorrer > 0)
                    {
                        finalizarAula(aulasOnline, quantAulas, ucs, quantUC, &quantAulasDecorrer, &quantAulasRealizadas, &quantAulasGravadas);
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
                    escreveFichBinUCs(ucs, quantUC);
                    escreveFichBinEstudantes(estudante, quantEstudantes);
                    escreveFichBinAulasOnline(aulasOnline, quantAulas);
                    escreveFichBinAcessos(acessos, quantAcessos);
                    printf("Dados registados no ficheiro com sucesso!\n");
                    break;
                case 'L':
                    leFichBinUCs(ucs, &quantUC);
                    printf("Dados lidos com sucesso!\n\n");
                    break;
                case 'R':
                    printf("Limpar dados da Aplicação!");
                    break;
                case 'S':
                    printf("\n");
                    break;
                default:
                    printf("Opção inválida!\n");
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

        case 'F':
            printf("\n");
            do
            {
                opcaosubMenu = menuEstudantes();
                switch(opcaosubMenu)
                {
                    case 'A':
                        if(quantEstudantes > 100)
                        {
                            printf("Não é possível criar mais estudantes!\n\n");
                        }
                        else
                        {
                            numero = lerInteiro("Insira o número do novo estudante", 1, 1000);
                            pos = procuraEstudante(estudante, numero, quantEstudantes);
                            if(pos == -1)
                            {
                                lerString("Insira o nome do novo estudante: ", nome, MAX_STRING);
                                strcpy(estudante[quantEstudantes].nome, nome);
                                estudante[quantEstudantes].numero = numero;
                                quantEstudantes++;
                                printf("Estudante criado com sucesso!\n\n");
                            }
                            else
                            {
                                printf("Já existe um estudante com o mesmo número.\n\n");
                            }
                        }
                        break;

                    case 'B':
                        if(quantEstudantes > 0)
                        {
                            numero = lerInteiro("Indique o número do estudante que pretende editar", 1, 1000);
                            pos = procuraEstudante(estudante, numero, quantEstudantes);
                            if(pos == -1)
                            {
                                printf("Número de estudante inexistente!\n\n");
                            }
                            else
                            {
                                printf("\n");
                                editarEstudante(estudante, pos, quantEstudantes);
                            }
                        }
                        else
                        {
                            printf("Não existem estudantes registados nos sistema.\n\n");
                        }
                        break;

                    case 'C':
                        if(quantEstudantes > 0)
                        {
                            numero = lerInteiro("Indique o número do estudante a eliminar", 1, 1000);
                            pos = procuraEstudante(estudante, numero, quantEstudantes);

                            if(pos != -1)
                            {
                                printf("Têm a certeza que pretende eliminar o estudante? (S)im/(N)ão: ");
                                scanf("%s", &opcao);
                                limpaBufferStdin();
                                opcao = toupper(opcao);

                                if(opcao == 'S')
                                {
                                    for(i = pos; i < quantEstudantes - 1; i++)
                                    {
                                        estudante[i] = estudante[i+1];
                                    }
                                    quantEstudantes--;
                                    printf("Estudante eliminado com sucesso!\n\n");
                                }
                                else
                                {
                                    printf("Eliminação do estudante cancelada!\n\n");
                                }
                            }
                            else
                            {
                                printf("Número de estudante inexistente!\n\n");
                            }
                        }
                        else
                        {
                            printf("Não existem estudantes registados no sistema!\n\n");
                        }
                        break;

                    case 'D':
                        if(quantEstudantes > 0)
                        {
                            printf("Quantidade total de estudantes: %d\n", quantEstudantes);
                            for(i = 0; i < quantEstudantes; i++)
                            {
                                printf("Estudante número %d -> %s\n", estudante[i].numero, estudante[i].nome);
                            }
                            printf("\n");
                        }
                        else
                        {
                            printf("Não existem estudantes registados no sistema!\n\n");
                        }
                        break;

                    case 'S':
                        printf("\n\n");
                        break;

                    default:
                        printf("Opção inválida! Tente outra vez.\n\n");
                        break;
                }
            }
            while(opcaosubMenu != 'S');
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
    printf("\tD - Gestao de Dados Estatisticos\n\tE - Gestao de Acesso as Aulas Online\n\tF - Gestao de Estudantes\n");
    printf("\tS - Sair\n");
    printf("\nInsira uma opcao: ");
    scanf("%c", &opcao);
    limpaBufferStdin();
    opcao = toupper(opcao);
    return opcao;
}

// Apresentação da estrutura do submenu das UCs
char menuUC(){
    char op;
    printf("--------- Gestão de unidades curriculares ---------\n\n");
    printf("\tI - Inserir nova UC\n");
    printf("\tL - Listar UC's\n");
    printf("\tE - Editar UC\n");
    printf("\tS - Sair\n\n");
    printf("Insira uma opção: ");
    scanf("%c", &op);
    limpaBufferStdin();
    op=toupper(op);
    return op;
}

// Apresentação da estrutura do submenu das aulas online
char menuAulas(int quantAulas)
{
    char opcao;
    printf("------------------ Gestão de Aulas Online ------------------\n\n");
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

// Apresentação da estrutura do submenu da gestão de estudantes
char menuEstudantes()
{
    char opcao;
    printf("------------------ Gestão de Estudantes ------------------\n\n");
    printf("\tA - Adicionar novo estudante\n");
    printf("\tB - Editar estudante\n");
    printf("\tC - Eliminar estudante\n");
    printf("\tD - Listar estudantes\n");
    printf("\tS - Sair\n");
    printf("\nInsira uma opção: ");
    scanf("%c", &opcao);
    limpaBufferStdin();
    opcao = toupper(opcao);
    return opcao;
}
