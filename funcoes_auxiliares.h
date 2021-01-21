#ifndef FUNCOES_AUXILIARES_H_INCLUDED
#define FUNCOES_AUXILIARES_H_INCLUDED

#include "constantes.h"

int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo);
float lerFloat(char mensagem[MAX_STRING], float minimo, float maximo);
void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres);
tipoData lerData(void);
tipoHora lerHora(void);
void limpaBufferStdin(void);
void lerOpcao(char mensagem[MAX_STRING], char opcoes[][MAX_STRING], int quantos, char opcao[MAX_STRING]);
char menu();
void verificaOpcao(char opcao, tipoUC ucs[MAX_UC], int quantUC);

#endif // FUNCOES_AUXILIARES_H_INCLUDED
