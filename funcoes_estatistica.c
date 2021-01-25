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
