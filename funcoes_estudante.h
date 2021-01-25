#ifndef FUNCOES_ESTUDANTE_H_INCLUDED
#define FUNCOES_ESTUDANTE_H_INCLUDED

#include "constantes.h"

int procuraEstudante(tipoEstudantes estudante[MAX_STRING], int numeroEstudante, int quantEstudantes);
void editarEstudante(tipoEstudantes estudante[MAX_STRING], int pos, int quantEstudantes);
char menuEditarEstudante(tipoEstudantes estudante);
void leFichBinEstudantes(tipoEstudantes estudante[MAX_STRING], int *quantEstudantes);
void escreveFichBinEstudantes(tipoEstudantes estudante[MAX_STRING], int quantEstudantes);

#endif // FUNCOES_ESTUDANTE_H_INCLUDED
