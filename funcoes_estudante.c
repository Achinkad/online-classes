#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "constantes.h"
#include "funcoes_auxiliares.h"

int procuraEstudante(tipoEstudantes estudantes[MAX_STRING], int numeroEstudante, int quantEstudantes)
{
    int i, pos = -1;
    for(i = 0; i<quantEstudantes; i++){
        if(estudantes[i].numero == numeroEstudante){
            pos = i;
        }
    }
    return pos;
}

char menuEditarEstudante(tipoEstudantes estudante)
{
    char opcao;
    printf("------------------ Edição do Estudante ------------------\n\n");
    printf("Edição do estudante número %d -> %s\n\n", estudante.numero, estudante.nome);
    printf("\tA - Editar o número do estudante\n");
    printf("\tB - Editar o nome do estudante\n");
    printf("\tS - Concluir edição do estudante\n");
    printf("\nInsira uma opção: ");
    scanf("%c", &opcao);
    limpaBufferStdin();
    opcao = toupper(opcao);
    return opcao;
}

void editarEstudante(tipoEstudantes estudante[MAX_STRING], int pos, int quantEstudantes)
{
    char opcao;
    int numero, posVerifica;
    do
    {
        opcao = menuEditarEstudante(estudante[pos]);
        switch(opcao)
        {
            case 'A':
                    numero = lerInteiro("Indique o novo número para o estudante", 1, 1000);
                    posVerifica = procuraEstudante(estudante, numero, quantEstudantes);
                    if(posVerifica != -1)
                    {
                        printf("Número de estudante já existe. Por favor, insira um número diferente!\n");
                    }
                    else
                    {
                        estudante[pos].numero = numero;
                        printf("Número de estudante editado com sucesso!\n\n");
                    }
                break;

            case 'B':
                break;

            default:
                printf("Edição concluída com sucesso!\n\n");
                break;
        }
    }
    while(opcao != 'S');
}

void leFichBinEstudantes(tipoEstudantes estudante[MAX_STRING], int *quantEstudante){
    FILE *f;
    f = fopen("dadosEstudantes.dat", "rb");
    if(f == NULL)
    {
        printf("Não foi possível encontrar o ficheiro dos dados dos estudantes!\n\n");
    }
    else
    {
        fread(&(*quantEstudante), sizeof(int), 1, f);
        fread(estudante, sizeof(tipoEstudantes), *quantEstudante, f);
        fclose(f);
    }
}

void escreveFichBinEstudantes(tipoEstudantes estudante[MAX_STRING], int quantEstudante){
    FILE *f;
    f = fopen("dadosEstudantes.dat", "wb");
    if(f == NULL)
    {
        printf("Não foi possível encontrar o ficheiro dos dados dos estudantes!\n\n");
    }
    else
    {
        fwrite(&quantEstudante, sizeof(int), 1, f);
        fwrite(estudante, sizeof(tipoEstudantes), quantEstudante, f);
        fclose(f);
    }
}

