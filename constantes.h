#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#define MAX_STRING 50
#define MAX 100

typedef struct{
    int dia, mes, ano;
}tipoData;


typedef struct{
    char nome[MAX_STRING];
    int numero;
    float nota;
    tipoData data;
}tipoEstudante;

#endif // CONSTANTES_H_INCLUDED
