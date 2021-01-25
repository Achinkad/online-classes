#ifndef FUNCOES_ESTATISTICA_H_INCLUDED
#define FUNCOES_ESTATISTICA_H_INCLUDED

int obterMediaPresencasAulasRealizadas(tipoAulasOnline aulasOnline[], int quantAulas, int quantAulasRealizadas);
int obterPercentagemUcsGravadas(tipoUC ucs[], int quantUC, tipoAulasOnline aulasOnline[], int quantAulas);
void rankingUcs(tipoUC ucs[], int quantUC, tipoAulasOnline aulasOnline[], int quantAulas);

#endif // FUNCOES_ESTATISTICA_H_INCLUDED
