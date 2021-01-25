#ifndef FUNCOES_UC_H_INCLUDED
#define FUNCOES_UC_H_INCLUDED

#include "constantes.h"

int obterTotalAgendado(tipoUC uc);
int obterTotalRealizado(tipoUC uc);
int obterTotalGravadas(tipoUC uc);
int obterTotalDecorrer(tipoUC uc);
int obterAulasRestantes(tipoAula tipoAula);

void mostrarUC(tipoUC uc); //funcao para apresentar os dados de uma uc especifica
char menuGeralUC(); //funcao para apresentar as opcoes da gestao de ucs
char menuEditarUC(tipoUC uc); //funcao para apresentar as opcoes de editar uma uc especifica
int procuraUC(char codigo[MAX_UC_CODIGO], tipoUC vetor[MAX_UC], int quantos); //funcao para procurar o codigo da uc no vetor das ucs
tipoUC lerDadosUC(); //funcao para ler os dados e retornar uma uc
void listarUCs(tipoUC ucs[MAX_UC], int quantUCs, tipoAulasOnline aulasOnline[], int quantAulas); //funcao para listar as ucs
void editarUC(tipoUC ucs[MAX_UC], int *quantUC); //funcao "main" da gestao de ucs

void leFichBinUCs(tipoUC ucs[MAX_UC], int *quantUC); //ler ficheiro binário de ucs
void escreveFichBinUCs(tipoUC ucs[MAX_UC], int quantUC); //escrever ficheiro binário de ucs

#endif // FUNCOES_UC_H_INCLUDED
