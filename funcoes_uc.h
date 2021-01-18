#ifndef FUNCOES_UC_H_INCLUDED
#define FUNCOES_UC_H_INCLUDED

#include "constantes.h"

void mostrarUC(tipoUC uc); //funcao para apresentar os dados de uma uc especifica
char menuGeralUC(); //funcao para apresentar as opcoes da gestao de ucs
char menuEditarUC(tipoUC uc); //funcao para apresentar as opcoes de editar uma uc especifica
int procuraUC(int codigo, tipoUC vetor[MAX_UC], int quantos); //funcao para procurar o codigo da uc no vetor das ucs
tipoUC lerDadosUC(); //funcao para ler os dados e retornar uma uc
void listarUCs(tipoUC ucs[MAX_UC], int quantUCs); //funcao para listar as ucs
void gestaoUCs(tipoUC ucs[MAX_UC], int quantUC); //funcao "main" da gestao de ucs

#endif // FUNCOES_UC_H_INCLUDED
