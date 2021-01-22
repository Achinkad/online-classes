#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "constantes.h"
#include "funcoes_auxiliares.h"

// Funcao para apresentar os dados relativos a uma aula online
void mostraAulas(tipoAulasOnline aulasOnline)
{
    printf("\nDesignacao: %s", aulasOnline.designacao);
    printf("\nCodigo da UC: %s", aulasOnline.codigoUC);
    printf("\nNome do docente: %s", aulasOnline.nomeDocente);

    // Apresentação do tipo de aula (T/TP/PL)
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

    // Apresentação do estado da aula (A/D/R)
    if(strcmp(aulasOnline.estado, "A") == 0)
    {
        printf("\nEstado da aula: Agendada");
    }
    else if(strcmp(aulasOnline.estado, "D") == 0)
    {
        printf("\nEstado da aula: A decorrer");
    }
    else
    {
        printf("\nEstado da aula: Realizada");
    }

    // Apresentação da decisão da gravação da aula (S/N)
    if(strcmp(aulasOnline.gravacao, "S") == 0)
    {
        printf("\nGravacao: Sim");
    }
    else
    {
        printf("\nGravacao: Nao");
    }

    printf("\nData da aula: %d/%d/%d", aulasOnline.data.dia, aulasOnline.data.mes, aulasOnline.data.ano);
    printf("\nHora de inicio: %d:%d:%d", aulasOnline.horaInicio.hora, aulasOnline.horaInicio.minuto, aulasOnline.horaInicio.segundo);
    printf("\nHora de fim: %d:%d:%d", aulasOnline.horaFim.hora, aulasOnline.horaFim.minuto, aulasOnline.horaFim.segundo);
}

// Funcao que procura a designacao de uma aula e verifica a sua existencia
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

// Funcao que le os dados da estrutura tipoAulasOnline e retorna os seus valores
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
    printf("\n\n");
    return e;
}

// Funcao que armazena os dados
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
    return pAulasOnline;
}

void listaAulas(tipoAulasOnline aulasOnline[], int quantAulas)
{
    int i;
    if(quantAulas > 0)
    {
        printf("\n\n------------------ Inicio dos Resultados ------------------\n\n");
        for(i=0; i<quantAulas; i++)
        {
            mostraAulas(aulasOnline[i]);
        }
        printf("------------------ Fim dos Resultados ------------------\n\n");
    }
    else
    {
        printf("Nao existem aulas registadas no sistema.\n\n");
    }
}
