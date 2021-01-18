#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "constantes.h"
#include "funcoes_auxiliares.h"

// Apresentação da estrutura do menu das aulas online
char menuAulas()
{
    char opcao;
    printf("\n\n------------------ Aulas Online ------------------\n\n");
    printf("\tA - Agendar aula online\n\tB - Alterar aula agendada\n\tC - Registar inicio de uma aula\n");
    printf("\tD - Registar o fim de uma aula\n\tE - Listar dados das aula online\n");
    printf("\tS - Sair\n");
    printf("\nInsira uma opcao: ");
    scanf("%c", &opcao);
    limpaBufferStdin();
    opcao = toupper(opcao);
    return opcao;
}

// Verifica a opção escolhida na função "menuAulas"
void verificaOpcaoAula(char opcao)
{
    if(opcao == 'A' || opcao == 'B' || opcao == 'C' || opcao == 'D' || opcao == 'E' || opcao == 'S')
    {
        switch(opcao)
        {
        case 'A':
            printf("Agendar aula online\n\n");
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
            printf("\n\n");
            break;
        }
    }
    else
    {
        printf("Opcao invalida. Por favor, insira uma opcao valida: ");
        scanf("%c", &opcao);
        limpaBufferStdin();
        opcao = toupper(opcao);
        verificaOpcaoAula(opcao);
    }
}

// Gera as funções do "menuAula" e "verificaOpcaoAula"
void gestaoAulas()
{
    char opcao;
    do
    {
        opcao = menuAulas();
        verificaOpcaoAula(opcao);
    }
    while(opcao != 'S');
}
