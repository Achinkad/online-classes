#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "constantes.h"
#include "funcoes_auxiliares.h"

char menuGeralUC(){
    char op;
    printf("\n\n--------- GESTAO DE UC'S ---------\n");
    printf("I - Inserir nova UC\n");
    printf("L - Listar UC's\n");
    printf("E - Editar UC\n");
    printf("S - Sair\n");
    printf("Insira uma opção: ");
    scanf("%c", &op);
    limpaBufferStdin();
    op=toupper(op);
    return op;
}

int procuraUC(char codigo[MAX_STRING], tipoUC vetor[MAX_UC], int quantos){
    int i, posicao=-1;
    for(i=0;i<quantos;i++){
        if(strcmp(vetor[i].codigo,codigo)==0){
            posicao=i;
        }
    }
    return posicao;
}

tipoUC lerDadosUC(){
    tipoUC e;
    char opcoesTipoUC[2][MAX_STRING]={"OB","OP"};
    char opcoesRegime[2][MAX_STRING]={"D","PL"};
    lerString("Indique a designacao da UC: ", e.designacao, MAX_STRING);
    lerOpcao("Indique o tipo de UC (OB)rigatoria ou (OP)cional: ", opcoesTipoUC, 2, e.tipoUC);
    e.semestre=lerInteiro("Indique o Semestre (1-6)",1,6);
    lerOpcao("Indique o Regime (D)iurno ou (PL)Pos-laboral: ", opcoesRegime, 2, e.regime);
    return e;
}

void listarUCs(tipoUC ucs[MAX_UC], int quantUCs){
    int i;
    if(quantUCs>0){
        printf("\n\n------------------ Início de Resultados --------------------\n");
        for(i=0;i<quantUCs;i++){
            printf("\nCódigo: %s - %s", ucs[i].codigo, ucs[i].designacao);
            if(strcmp(ucs[i].tipoUC,"OB")==0){
               printf("\nTipo de UC: Obrigatória");
            }else if(strcmp(ucs[i].tipoUC,"OP")==0){
                printf("\nTipo de UC: Opcional");
            }
            printf("\nSemestre:%d", ucs[i].semestre);
            if(strcmp(ucs[i].regime,"D")==0){
               printf("\nRegime: Diurno");
            }else if(strcmp(ucs[i].regime,"PL")==0){
                printf("\nRegime: Pos-laboral");
            }
            if(quantUCs-1!=i){
                printf("\n------");
            }
        }
        printf("\n\n-------------------- Fim de Resultados --------------------\n\n");
    }else{
        printf("\n\nNao existem UC's Inseridas!\n\n");
    }
}

void gestaoUCs(tipoUC ucs[MAX_UC], int quantUC){
    char opcao, codigo[MAX_STRING];
    int posicao;
    do{
        opcao=menuGeralUC();
        switch(opcao){
            case 'I':
                do{
                    lerString("Indique o código da UC: ",codigo,MAX_STRING);
                    posicao=procuraUC(codigo,ucs,quantUC);
                    if(posicao==-1){
                        ucs[quantUC]=lerDadosUC();
                        strcpy(ucs[quantUC].codigo,codigo);
                        quantUC++;
                    }else{
                        printf("Código UC já existe!\n");
                    }
                }while(posicao!=-1);
            break;
            case 'L':
                listarUCs(ucs,quantUC);
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
