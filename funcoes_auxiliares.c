#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "funcoes_auxiliares.h"
#include "funcoes_uc.h"

// Acrescentada variavel controlo para repetir insercao se ao for inserido numero int
int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo)
{
    int numero, controlo;
    do
    {
        printf("%s (%d a %d) :", mensagem, minimo, maximo);
        controlo = scanf ("%d", &numero);  // scanf devolve quantidade de valores vàlidos obtidos
        limpaBufferStdin();     //limpa todos os caracteres do buffer stdin (nomeadamente o \n)

        if (controlo == 0)
        {
            printf("Devera inserir um numero inteiro \n");
        }
        else
        {

            if(numero<minimo || numero>maximo)
            {
                printf("Numero invalido. Insira novamente:\n");
            }

        }
    }
    while(numero<minimo || numero>maximo || controlo == 0);

    return numero;
}

float lerFloat(char mensagem[MAX_STRING], float minimo, float maximo)
{
    float numero;
    int controlo;
    do
    {
        printf("%s (%.2f a %.2f) :", mensagem, minimo, maximo);
        controlo = scanf ("%f", &numero);  // scanf devolve quantidade de valores vàlidos obtidos
        limpaBufferStdin();

        if (controlo == 0)
        {
            printf("Devera inserir um numero decimal (float) \n");
        }
        else
        {

            if(numero<minimo || numero>maximo)
            {
                printf("Numero invalido. Insira novamente:\n");
            }

        }
    }
    while(numero<minimo || numero>maximo || controlo ==0);

    return numero;
}

void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres)
{
    int tamanhoString;

    do 			// Repete leitura caso sejam obtidas strings vazias
    {
        //   puts(mensagem);
        printf("%s", mensagem);
        fgets(vetorCaracteres, maximoCaracteres, stdin);

        tamanhoString = strlen(vetorCaracteres);

        if (tamanhoString == 1)
        {
            printf("Nao foram introduzidos caracteres!!! . apenas carregou no ENTER \n\n");  // apenas faz sentido limpar buffer se a ficarem caracteres
        }

    }
    while (tamanhoString == 1);

    if(vetorCaracteres[tamanhoString-1] != '\n')  // ficaram caracteres no buffer....
    {
        limpaBufferStdin();  // apenas faz sentido limpar buffer se a ficarem caracteres
    }
    else
    {
        vetorCaracteres[tamanhoString-1] ='\0';          //substitui \n da string armazenada em vetor por \0
    }
}


tipoData lerData(void)
{
    tipoData data;
    int maxDiasMes;

    data.ano = lerInteiro(" ano", 2014, 2021);
    data.mes = lerInteiro(" mes", 1, 12);

    switch (data.mes)
    {
    case 2:
        if ((data.ano % 400 == 0) || (data.ano % 4 == 0 && data.ano % 100 != 0))
        {
            maxDiasMes = 29;
        }
        else
        {
            maxDiasMes = 28;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        maxDiasMes = 30;
        break;
    default:
        maxDiasMes = 31;
    }

    data.dia = lerInteiro(" dia:", 1, maxDiasMes);


    return data;
}

void limpaBufferStdin(void)
{
    char chr;
    do
    {
        chr = getchar();
    }
    while (chr != '\n' && chr != EOF);
}

void lerOpcao(char mensagem[MAX_STRING], char opcoes[][MAX_STRING], int quantos, char opcao[MAX_STRING])
{
    int i, tamanhoString;
    char opcaoSelecionada[MAX_STRING];
    int opcaoInvalida=1;

    do 			// Repete leitura caso sejam obtidas strings vazias
    {
        //   puts(mensagem);
        printf("%s", mensagem);
        scanf("%s", opcaoSelecionada);


        tamanhoString = strlen(opcaoSelecionada);
        if (tamanhoString == 1 && opcaoSelecionada[0] == '\n')
        {
            printf("Nao foram introduzidos caracteres!!! . apenas carregou no ENTER \n\n");  // apenas faz sentido limpar buffer se a ficarem caracteres
        }
        else
        {
            if(opcao[tamanhoString-1] != '\n')  // ficaram caracteres no buffer....
            {
                limpaBufferStdin();  // apenas faz sentido limpar buffer se a ficarem caracteres
            }
            else
            {
                opcao[tamanhoString-1] ='\0';          //substitui \n da string armazenada em vetor por \0
            }
            i=0;
            while(opcaoSelecionada[i])
            {
                opcaoSelecionada[i]=toupper(opcaoSelecionada[i]);
                i++;
            }
            for(i=0; i<quantos; i++)
            {
                if(strcmp(opcoes[i],opcaoSelecionada)==0)
                {
                    strcpy(opcao, opcaoSelecionada);
                    opcaoInvalida=0;
                }
            }

            if (opcaoInvalida == 1)
            {
                printf("OPCAO INVALIDA!! Insira uma opcao valida\n\n");  // apenas faz sentido limpar buffer se a ficarem caracteres
            }
        }

    }
    while (tamanhoString == 1 && opcaoSelecionada[0] == '\n' || opcaoInvalida == 1 );
}
