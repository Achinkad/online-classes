#include <stdio.h>
#include <ctype.h>

#include "constantes.h"
#include "funcoes_auxiliares.h"

char menuGeralUC(){
    char op;
    printf("\n\n*********************** GESTAO DE UC'S ***********************\n");
    printf("(I)nserir nova UC\n");
    printf("(L)istar UC's\n");
    printf("(E)ditar UC\n");
    printf("(S)air\n");
    printf("Selecione a opção -> ");
    scanf("%c", &op);
    limpaBufferStdin();
    op=toupper(op);
    return op;
}

void gestaoUCs(tipoUC ucs[MAX_UC], int quantUC){
    char opcao;
    do{
        opcao=menuGeralUC();
        switch(opcao){
            case 'I':
                printf("Inserir UC");
            break;
            case 'L':
                printf("Listar UCs");
            break;
            case 'E':
                printf("Editar UC");
            break;
            case 'S':

            break;
            default:
                printf("Opção Inválida");
            break;
        }
    }while(opcao!='S');
}
