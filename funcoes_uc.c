#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "constantes.h"
#include "funcoes_auxiliares.h"
#include "funcoes_tipoAula.h"

int obterTotalAgendado(tipoUC uc){
    int total=0;
    total+=uc.aulasT.contAgendadas;
    total+=uc.aulasTP.contAgendadas;
    total+=uc.aulasPL.contAgendadas;
    return total;
}
int obterTotalRealizado(tipoUC uc){
    int total=0;
    total+=uc.aulasT.contRealizadas;
    total+=uc.aulasTP.contRealizadas;
    total+=uc.aulasPL.contRealizadas;
    return total;
}
int obterTotalGravadas(tipoUC uc){
    int total=0;
    total+=uc.aulasT.contGravadas;
    total+=uc.aulasTP.contGravadas;
    total+=uc.aulasPL.contGravadas;
    return total;
}
int obterTotalDecorrer(tipoUC uc){
    int total=0;
    total+=uc.aulasT.aDecorrer;
    total+=uc.aulasTP.aDecorrer;
    total+=uc.aulasPL.aDecorrer;
    return total;
}
int obterAulasRestantes(tipoAula tipoAula){
    int restantes;
    restantes=tipoAula.quantAulas-(tipoAula.contAgendadas+tipoAula.aDecorrer+tipoAula.contRealizadas);
    return restantes;
}

void mostrarUC(tipoUC uc){
    int i;
    if(strcmp(uc.tipoUC,"OB")==0){
       printf("\nTipo de UC: Obrigatória");
    }else if(strcmp(uc.tipoUC,"OP")==0){
        printf("\nTipo de UC: Opcional");
    }
    printf("\nSemestre:%d", uc.semestre);
    if(strcmp(uc.regime,"D")==0){
       printf("\nRegime: Diurno");
    }else if(strcmp(uc.regime,"PL")==0){
        printf("\nRegime: Pos-laboral");
    }
    printf("\n%d Aulas T - %d minutos (%d realizadas)", uc.aulasT.quantAulas, uc.aulasT.duracao, uc.aulasT.contRealizadas);
    printf("\n%d Aulas TP - %d minutos (%d realizadas)", uc.aulasTP.quantAulas, uc.aulasTP.duracao, uc.aulasTP.contRealizadas);
    printf("\n%d Aulas PL - %d minutos (%d realizadas)", uc.aulasPL.quantAulas, uc.aulasPL.duracao, uc.aulasPL.contRealizadas);
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
    printf("\nInsira uma opção: ");
    scanf("%c", &op);
    limpaBufferStdin();
    op=toupper(op);
    return op;
}

int procuraUC(char codigo[MAX_UC_CODIGO], tipoUC vetor[MAX_UC], int quantos){
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
    e.contAcessosGravacoes=0;
    return e;
}

void listarUCs(tipoUC ucs[MAX_UC], int quantUCs, tipoAulasOnline aulasOnline[], int quantAulas){
    int i, i2;
    if(quantUCs>0){
        printf("\n\n------------------ Início de Resultados --------------------\n");
        for(i=0;i<quantUCs;i++){
            printf("\nCódigo: %s - %s", ucs[i].codigo, ucs[i].designacao);
            mostrarUC(ucs[i]);
            if(obterTotalAgendado(ucs[i])>0){
                printf("\n\tAulas Agendadas:");
                for(i2=0;i2<quantAulas;i2++){
                    if(strcmp(aulasOnline[i2].codigoUC, ucs[i].codigo)==0&&strcmp(aulasOnline[i2].estado,"A")==0){
                        printf("\n\t\t-%s (%s) - %s -", aulasOnline[i2].designacao, aulasOnline[i2].tipo, aulasOnline[i2].nomeDocente);
                        printf(" %.2d-%.2d-%.2d %.2d:%.2d", aulasOnline[i2].data.dia, aulasOnline[i2].data.mes, aulasOnline[i2].data.ano, aulasOnline[i2].horaInicio.hora, aulasOnline[i2].horaInicio.minuto);
                    }
                }
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



void editarUC(tipoUC ucs[MAX_UC], int *quantUC){
    char opcao, codigo[MAX_STRING];
    int posicao;
    char opcoesTipoUC[2][MAX_STRING]={"OB","OP"};
    char opcoesRegime[2][MAX_STRING]={"D","PL"};

    lerString("Indique o código da UC a editar: ",codigo,MAX_STRING);
    posicao=procuraUC(codigo,ucs,*quantUC);
    if(posicao!=-1){
        do{
            opcao=menuEditarUC(ucs[posicao]);
            switch(opcao){
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
                    ucs[posicao].aulasT=editarTipoAula(ucs[posicao].aulasT, "T");
                break;
                case 'F':
                    ucs[posicao].aulasTP=editarTipoAula(ucs[posicao].aulasTP, "TP");
                break;
                case 'G':
                    ucs[posicao].aulasPL=editarTipoAula(ucs[posicao].aulasPL, "PL");
                break;
                case 'S':
                break;
                default:
                    printf("Opção Inválida");
                break;
            }
        }while(opcao!='S');
        printf("\n\nEdicao concluida com sucesso! \n\n");
    }else{
        printf("Código UC não encontrado!\n");
    }
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
