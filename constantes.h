#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#define MAX_STRING 100
#define MAX_UC 40
#define MAX_UC_CODIGO 20

typedef struct{
    int dia, mes, ano;
}tipoData;

//Declaração do Tipo de Aula
typedef struct{
    int quantAulas;
    int duracao; //em minutos
}tipoAula;

//Declaração das UC's
typedef struct{
    char codigo[MAX_UC_CODIGO];
    char designacao[MAX_STRING];
    char tipoUC[2];
    int semestre;
    char regime[2];
    tipoAula aulasT;
    tipoAula aulasTP;
    tipoAula aulasPL;
}tipoUC;

#endif // CONSTANTES_H_INCLUDED
