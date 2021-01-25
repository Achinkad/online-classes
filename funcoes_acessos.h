#ifndef FUNCOES_ACESSOS_H_INCLUDED
#define FUNCOES_ACESSOS_H_INCLUDED

#include "constantes.h"

tipoAcesso *registarAcesso(tipoAcesso acessos[], int *quantAcessos, tipoAulasOnline aulasOnline[], int *quantAulas, int quantAulasADecorrer, int quantAulasGravadas);

tipoAcesso *leFichBinAcessos(tipoAcesso acessos[], int *quantAcessos);
void escreveFichBinAcessos(tipoAcesso acessos[], int quanAcessos);

void verificarPresencas(tipoAulasOnline aulasOnline[], int quantAulas, tipoAcesso acessos[], int quantAcessos);

#endif // FUNCOES_ACESSOS_H_INCLUDED
