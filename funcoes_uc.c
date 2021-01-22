#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "constantes.h"
#include "funcoes_auxiliares.h"
#include "funcoes_tipoAula.h"

void mostrarUC(tipoUC uc){
    if(strcmp(uc.tipoUC,"OB")==0){
       printf("\nTipo de UC: Obrigat�ria");
    }else if(strcmp(uc.tipoUC,"OP")==0){
        printf("\nTipo de UC: Opcional");
    }
    printf("\nSemestre:%d", uc.semestre);
    if(strcmp(uc.regime,"D")==0){
       printf("\nRegime: Diurno");
    }else if(strcmp(uc.regime,"PL")==0){
        printf("\nRegime: Pos-laboral");
    }
    printf("\n%d Aulas T - %d minutos", uc.aulasT.quantAulas, uc.aulasT.duracao);
    printf("\n%d Aulas TP - %d minutos", uc.aulasTP.quantAulas, uc.aulasTP.duracao);
    printf("\n%d Aulas PL - %d minutos", uc.aulasPL.quantAulas, uc.aulasPL.duracao);
}

char menuGeralUC(){
    char op;
    printf("\n\n--------- GESTAO DE UC'S ---------\n\n");
    printf("\tI - Inserir nova UC\n");
    printf("\tL - Listar UC's\n");
    printf("\tE - Editar UC\n");
    printf("\tS - Sair\n\n");
    printf("Insira uma op��o: ");
    scanf("%c", &op);
    limpaBufferStdin();
    op=toupper(op);
    return op;
}

char menuEditarUC(tipoUC uc){
    char op;
    printf("\n\n--------- EDITAR UC %s - %s ---------\n", uc.codigo, uc.designacao);
    mostrarUC(uc);
    printf("\n\n\tA - Editar Designacao UC\n");
    printf("\tB - Editar tipo de UC\n");
    printf("\tC - Editar Semestre\n");
    printf("\tD - Editar Regime\n");
    printf("\tE - Editar Aulas T\n");
    printf("\tF - Editar Aulas TP\n");
    printf("\tG - Editar Aulas PL\n");
    printf("\tS - Concluir Edicao\n");
    printf("\nInsira uma op��o: ");
    scanf("%c", &op);
    limpaBufferStdin();
    op=toupper(op);
    return op;
}

int procuraUC(char codigo[MAX_STRING], tipoUC vetor[MAX_UC], int quantos){
    int i, posicao=-1;
    for(i=0;i<quantos;i++){
        if(strcmp(vetor[i].codigo,codigo) == 0){
            posicao = i;
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
    e.aulasT=criarTipoAula("T");
    e.aulasTP=criarTipoAula("TP");
    e.aulasPL=criarTipoAula("PL");
    return e;
}

void listarUCs(tipoUC ucs[MAX_UC], int quantUCs){
    int i;
    if(quantUCs>0){
        printf("\n\n------------------ In�cio de Resultados --------------------\n");
        for(i=0;i<quantUCs;i++){
            printf("\nC�digo: %s - %s", ucs[i].codigo, ucs[i].designacao);
            mostrarUC(ucs[i]);
            if(quantUCs-1!=i){
                printf("\n------");
            }
        }
        printf("\n\n-------------------- Fim de Resultados --------------------\n\n");
    }else{
        printf("\n\nNao existem UC's Inseridas!\n\n");
    }
}



void gestaoUCs(tipoUC ucs[MAX_UC], int *quantUC){
    char opcao, opcaoMenuEditar, codigo[MAX_STRING];
    int posicao;
    char opcoesTipoUC[2][MAX_STRING]={"OB","OP"};
    char opcoesRegime[2][MAX_STRING]={"D","PL"};
    do{
        opcao=menuGeralUC();
        switch(opcao){
            case 'I':
                do{
                    lerString("Indique o c�digo da UC: ",codigo,MAX_STRING);
                    posicao=procuraUC(codigo,ucs,*quantUC);
                    if(posicao==-1){
                        ucs[*quantUC]=lerDadosUC();
                        strcpy(ucs[*quantUC].codigo,codigo);
                        (*quantUC)++;
                    }else{
                        printf("C�digo UC j� existe!\n");
                    }
                }while(posicao!=-1);
            break;
            case 'L':
                listarUCs(ucs,*quantUC);
            break;
            case 'E':
                lerString("Indique o c�digo da UC a editar: ",codigo,MAX_STRING);
                posicao=procuraUC(codigo,ucs,*quantUC);
                if(posicao!=-1){
                    do{
                        opcaoMenuEditar=menuEditarUC(ucs[posicao]);
                        switch(opcaoMenuEditar){
                            case 'A':
                                lerString("Indique a designacao da UC: ", ucs[posicao].designacao, MAX_STRING);
                            break;
                            case 'B':
                                lerOpcao("Indique o tipo de UC (OB)rigatoria ou (OP)cional: ", opcoesTipoUC, 2, ucs[posicao].tipoUC);
                            break;
                            case 'C':
                                ucs[posicao].semestre=lerInteiro("Indique o Semestre (1-6)",1,6);
                            break;
                            case 'D':
                                lerOpcao("Indique o Regime (D)iurno ou (PL)Pos-laboral: ", opcoesRegime, 2, ucs[posicao].regime);
                            break;
                            case 'E':
                                ucs[posicao].aulasT=criarTipoAula("T");
                            break;
                            case 'F':
                                ucs[posicao].aulasTP=criarTipoAula("TP");
                            break;
                            case 'G':
                                ucs[posicao].aulasPL=criarTipoAula("PL");
                            break;
                            case 'S':
                            break;
                            default:
                                printf("Op��o Inv�lida");
                            break;
                        }
                    }while(opcaoMenuEditar!='S');
                    printf("\n\nEdicao concluida com sucesso! \n\n");
                }else{
                    printf("C�digo UC n�o encontrado!\n");
                }
            break;
            case 'S': break;
            default:
                printf("Op��o Inv�lida");
            break;
        }
    }while(opcao!='S');
}

void leFichBinUCs(tipoUC ucs[MAX_UC], int *quantUC){
    FILE *f;
    f=fopen("dadosUC.dat", "rb");
    if(f==NULL){
        printf("\n\nNao foi possivel encontrar o ficheiro de UC's!\n\n");
    }else{
        fread(&(*quantUC),sizeof(int),1,f);
        fread(ucs,sizeof(tipoUC),*quantUC,f);
        fclose(f);
    }
}

void escreveFichBinUCs(tipoUC ucs[MAX_UC], int quantUC){
    FILE *f;
    f=fopen("dadosUC.dat", "wb");
    if(f==NULL){
        printf("\n\nNao foi possivel encontrar o ficheiro de UC's!\n\n");
    }else{
        fwrite(&quantUC,sizeof(int),1,f);
        fwrite(ucs,sizeof(tipoUC),quantUC,f);
        fclose(f);
    }
}
