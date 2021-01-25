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

int obterPercentagemUcsGravadas(tipoUC ucs[], int quantUC, tipoAulasOnline aulasOnline[], int quantAulas){
    int i, i2, contUcsGravadas=0, resultado=0;
    if(quantUC!=0){
        for(i=0;i<quantUC;i++){
            for(i2=0; i<quantAulas; i++){
                if(strcmp(aulasOnline[i2].codigoUC, ucs[i].codigo)==0){
                    if(strcmp(aulasOnline[i2].codigoUC, "S")==0){
                        contUcsGravadas++;
                        i2=quantAulas;
                    }
                }
            }
        }
        resultado=(contUcsGravadas*100)/quantUC;
    }

    return resultado;
}
