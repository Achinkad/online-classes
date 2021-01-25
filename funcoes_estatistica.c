#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "constantes.h"
#include "funcoes_auxiliares.h"
#include "funcoes_aulasOnline.h"

int obterMediaPresencasAulasRealizadas(tipoAulasOnline aulasOnline[], int quantAulas, int quantAulasRealizadas){
    int i, contPresencas=0, resultado=0;
    if(quantAulasRealizadas!=0){
        for(i=0;i<quantAulas;i++){
            contPresencas+=aulasOnline[i].contEstudantesPresentes;
        }
        resultado=contPresencas/quantAulasRealizadas;
    }

    return resultado;
}

int obterPercentagemUcsGravadas(tipoUC ucs[], int quantUC){
    int i, contUcsGravadas=0, resultado=0;
    if(quantUC!=0){
        for(i=0;i<quantUC;i++){
            if(ucs[i].aulasPL.contGravadas>0||ucs[i].aulasT.contGravadas>0||ucs[i].aulasTP.contGravadas>0){
                contUcsGravadas++;
            }
        }
        resultado=(contUcsGravadas*100)/quantUC;
    }

    return resultado;
}

void rankingUcs(tipoUC ucs[], int quantUC)
{
    int i, j, posMenor;
    tipoUC vAux;

    for(i=0; i < quantUC-1; i++)
    {
        posMenor = i;
        for(j=i+1; j < quantUC; j++)
        {
            if((ucs[j].contAcessosGravacoes) > (ucs[posMenor].contAcessosGravacoes))
            {
                posMenor = j;
            }
        }

        if(posMenor != i)
        {
            vAux = ucs[posMenor];
            ucs[posMenor] = ucs[i];
            ucs[i] = vAux;
        }
        printf("-> Designação da UC: %s\n", ucs[i].designacao);
    }
}

void ucMenorAulas(tipoUC ucs[], int quantUC)
{
    int i, j, posMenor;
    tipoUC vAux;

    for(i=0; i < quantUC-1; i++)
    {
        posMenor = i;
        for(j=i+1; j < quantUC; j++)
        {
            if((ucs[j].aulasT.contRealizadas + ucs[j].aulasPL.contRealizadas + ucs[j].aulasTP.contRealizadas) > (ucs[posMenor].aulasPL.contRealizadas + ucs[posMenor].aulasT.contRealizadas + ucs[posMenor].aulasTP.contRealizadas))
            {
                posMenor = j;
            }
        }

        if(posMenor != i)
        {
            vAux = ucs[posMenor];
            ucs[posMenor] = ucs[i];
            ucs[i] = vAux;
        }
    }
    printf("\nUC com menor quantidade de aulas online realizadas: %s\n", ucs[i].designacao);
}

void tipoAulaMaiorGravacao(tipoAulasOnline aulas[], int quantAulas)
{
    int i, j, posMenor;
    tipoAulasOnline vAux;

    for(i=0; i < quantAulas-1; i++)
    {
        posMenor = i;
        for(j=i+1; j < quantAulas; j++)
        {
            if((aulas[j].contAcessosGravacoes) < (aulas[posMenor].contAcessosGravacoes))
            {
                posMenor = j;
            }
        }

        if(posMenor != i)
        {
            vAux = aulas[posMenor];
            aulas[posMenor] = aulas[i];
            aulas[i] = vAux;
        }
    }
    printf("\nTipo de aula com mais gravações: %s\n", aulas[i].tipo);
}

void aulasOnlineMaisTempo(tipoAulasOnline aulas[], int quantAulas)
{
    int i, j, posMenor;
    tipoAulasOnline vAux;

    for(i=0; i < quantAulas-1; i++)
    {
        posMenor = i;
        for(j=i+1; j < quantAulas; j++)
        {
            if(strcmp(aulas[j].estado, "R") == 0)
            {
                if((aulas[j].data.ano) < (aulas[posMenor].data.ano))
                {
                    if((aulas[j].data.mes) < (aulas[posMenor].data.mes))
                    {
                        if((aulas[j].data.dia) < (aulas[posMenor].data.dia))
                        {
                            posMenor = j;
                        }
                    }
                }
            }
        }

        if(posMenor != i)
        {
            vAux = aulas[posMenor];
            aulas[posMenor] = aulas[i];
            aulas[i] = vAux;
        }
    }
    printf("\nAula online realizada a mais tempo: %s\n", aulas[i].designacao);
}
