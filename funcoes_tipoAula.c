#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "constantes.h"
#include "funcoes_auxiliares.h"

tipoAula criarTipoAula(char tipo[MAX_STRING]){
    tipoAula tipoAula;
    printf("---> Aulas %s\n\t", tipo);
    tipoAula.quantAulas=lerInteiro("Indique a quantidade de aulas",1,100);
    printf("\t");
    tipoAula.duracao=lerInteiro("Indique a duracao(minutos) de aulas",1,300);
    tipoAula.contAgendadas=0;
    tipoAula.contRealizadas=0;
    return tipoAula;
}
