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


void rankingUcs(tipoUC ucs[], int quantUC, tipoAulasOnline aulasOnline[], int quantAulas)
{
    int i, j, posmenor;
    tipoUC aux;

    for(i=0; i < quantUC-1; i++)
    {
        posmenor = i;
        for(j=i+1; j < quantUC; j++)
        {
            if((ucs[j].aulasPL.contGravadas + ucs[j].aulasT.contGravadas + ucs[j].aulasTP.contGravadas) > (ucs[posmenor].aulasPL.contGravadas + ucs[posmenor].aulasT.contGravadas + ucs[posmenor].aulasTP.contGravadas))
            {
                posmenor = j;
            }
        }

        if(posmenor != i)
        {
            aux = ucs[posmenor];
            ucs[posmenor] = ucs[i];
            ucs[i] = aux;
        }
    }

    for(i=0; i < quantUC; i++)
    {
        printf("Designação da UC: %s\n", aux.designacao);
    }
}
