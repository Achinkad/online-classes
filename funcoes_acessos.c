#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "constantes.h"
#include "funcoes_auxiliares.h"

tipoAcesso *registarAcesso(tipoAcesso acessos[], int *quantAcessos, tipoAulasOnline aulasOnline[], int *quantAulas){

    return aulasOnline;
}

tipoAcesso *leFichBinAcessos(tipoAcesso acessos[], int *quantAcessos){
    FILE *f;
    tipoAcesso *pAcessos;
    f=fopen("dadosAcessos.dat", "rb");
    if(f==NULL){
        printf("\n\nNao foi possivel encontrar o ficheiro de Dados dos Acessos às Aulas Online!\n\n");
    }else{
        fread(&(*quantAcessos),sizeof(int),1,f);
        pAcessos = acessos;
        acessos = realloc(acessos,(*quantAcessos)*sizeof(tipoAcesso));
        if(acessos == NULL && *quantAcessos != 0){
            printf("\nErro! (erro ao reservar a memória)");
            acessos=pAcessos;
        }else{
            fread(acessos,sizeof(tipoAcesso),*quantAcessos,f);
        }
        fclose(f);
    }
    return acessos;
}

void escreveFichBinAcessos(tipoAcesso acessos[], int quantAcessos){
    FILE *f;
    f=fopen("dadosAcessos.dat", "wb");
    if(f==NULL){
        printf("\n\nNao foi possivel encontrar o ficheiro de Dados dos Acessos às Aulas Online!\n\n");
    }else{
        fwrite(&quantAcessos,sizeof(int),1,f);
        fwrite(acessos,sizeof(tipoAcesso),quantAcessos,f);
        fclose(f);
    }
}
