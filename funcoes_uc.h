#ifndef FUNCOES_UC_H_INCLUDED
#define FUNCOES_UC_H_INCLUDED

#include "constantes.h"


char menuGeralUC(); //funcao para apresentar as opcoes da gestao de ucs
int procuraUC(int codigo, tipoUC vetor[MAX_UC], int quantos);
tipoUC lerDadosUC();
void listarUCs(tipoUC ucs[MAX_UC], int quantUCs);

void gestaoUCs(tipoUC ucs[MAX_UC], int quantUC);

#endif // FUNCOES_UC_H_INCLUDED
