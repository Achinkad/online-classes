#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "constantes.h"
#include "funcoes_auxiliares.h"

void mostraAulas(tipoAulasOnline aulasOnline)
{
    printf("\nUC associada: %s", aulasOnline.codigoUC);
    if(strcmp(aulasOnline.tipo, "T") == 0)
    {
        printf("\nTipo de aula: Teorica");
    }
    else if(strcmp(aulasOnline.tipo, "TP") == 0)
    {
        printf("\nTipo de aula: Teorica-Pratica");
    }
    else
    {
        printf("\nTipo de aula: Pratica");
    }
}

int procuraAula(char designacao[MAX_STRING], tipoAulasOnline aulasOnline[], int quantAulas)
{
    int i, pos = -1;
    for(i=0; i < quantAulas; i++){
        if(strcmp(aulasOnline[i].designacao, designacao) == 0){
            pos = i;
        }
    }
    return pos;
}

tipoAulasOnline lerDadosAulas()
{
    tipoAulasOnline e;
    char opcoesTipo[3][MAX_STRING] = {"T","TP","PL"};
    char opcoesEstado[3][MAX_STRING] = {"A","D","R"};
    char opcoesGravacao[2][MAX_STRING] = {"S","N"};
    lerString("Indique o codigo da UC: ", e.codigoUC, MAX_UC_CODIGO);
    lerString("Indique o nome do docente: ", e.nomeDocente, MAX_STRING);
    lerOpcao("Indique o tipo de aula.\n\tT - Teorica \n\tTP - Teorico-Pratica\n\tPL - Pratica laboratorial\nOpcao: ", opcoesTipo, 3, e.tipo);
    lerOpcao("Indique o estado da aula.\n\tA - Agendada \n\tD - A decorrer\n\tR - Realizada\nOpcao: ", opcoesEstado, 3, e.estado);
    lerOpcao("Pretende que a aula seja gravada?\n\tS - Sim \n\tN - Nao\nOpcao: ", opcoesGravacao, 2, e.gravacao);
    printf("Inserir data da aula.\n");
    e.data = lerData();
    printf("Inserir hora do inicio de aula.\n");
    e.horaInicio = lerHora();
    printf("Inserir hora do termino da aula.\n");
    e.horaFim = lerHora();
    return e;
}

tipoAulasOnline *agendaAula(tipoAulasOnline aulasOnline[], int *quantAulas)
{
    int pos;
    char designacao[MAX_STRING];
    tipoAulasOnline *pAulasOnline, dados;
    pAulasOnline = aulasOnline;

    lerString("Indique a designacao da aula: ", designacao, MAX_STRING);
    pos = procuraAula(designacao, pAulasOnline, *quantAulas);

    if(pos != -1){
        printf("Designacao da aula já existe!\n");
    }else{
        dados = lerDadosAulas();
        aulasOnline = realloc(aulasOnline,(*quantAulas+1)*sizeof(tipoAulasOnline));
        if(aulasOnline == NULL){
            printf("Erro! Impossivel agendar aula.");
            aulasOnline = pAulasOnline;
        }else{
            aulasOnline[*quantAulas] = dados;
            strcpy(aulasOnline[*quantAulas].designacao, designacao);
            (*quantAulas)++;
        }
    }

    return aulasOnline;
}

void listaAulas(tipoAulasOnline aulasOnline[], int quantAulas)
{
    int i;
    if(quantAulas > 0)
    {
        printf("------------------ Inicio dos Resultados ------------------\n\n");
        for(i=0; i<quantAulas; i++)
        {
            printf("Quantidade de aulas: %d", quantAulas);
            mostraAulas(aulasOnline[i]);
        }
        printf("------------------ Fim dos Resultados ------------------\n\n");
    }
    else
    {
        printf("Nao existem aulas registadas no sistema.\n\n");
    }
}
