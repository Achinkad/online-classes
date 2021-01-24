#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "constantes.h"
#include "funcoes_auxiliares.h"

tipoAcesso *registarAcesso(tipoAcesso acessos[], int *quantAcessos, tipoAulasOnline aulasOnline[], int *quantAulas, int quantAulasADecorrer, int quantAulasGravadas){
    int i, pos;
    tipoAcesso acesso;
    tipoAcesso *pAcessos=acessos;
    FILE *f;
    acesso.numEstudante=lerInteiro("Indique o número de Estudante:",1,10000);
    //mostrar as aulas a decorrer no momento
    printf("\n\nAulas a Decorrer neste momento:\n");
    if(quantAulasADecorrer>0){
        for(i=0;i<*quantAulas;i++){
            if(strcmp(aulasOnline[i].estado,"D")==0){
                printf("\n|  Designacao:%s", aulasOnline[i].designacao);
                printf("\n|\tInicio: %d:%d", aulasOnline[i].horaInicio.hora, aulasOnline[i].horaInicio.minuto);
                printf("\n|\tDocente: %s", aulasOnline[i].nomeDocente);
            }
        }
    }
    else{
        printf("\n -> Não existem Aulas a decorrer neste momento!");
    }
    //mostrar as aulas gravadas disponíveis
    printf("\n\nAulas realizadas e gravadas:\n");
    if(quantAulasGravadas>0){
        for(i=0;i<*quantAulas;i++){
            if(strcmp(aulasOnline[i].estado,"R")==0&&strcmp(aulasOnline[i].gravacao,"S")==0){
                printf("\n|  Designacao:%s", aulasOnline[i].designacao);
                printf("\n|\tInicio: %d:%d", aulasOnline[i].horaInicio.hora, aulasOnline[i].horaInicio.minuto);
                printf("\n|\tDocente: %s", aulasOnline[i].nomeDocente);
            }
        }
    }else{
        printf("\n -> Não existem Aulas gravadas disponíveis!");
    }
    //Se não houver aulas a decorrer ou gravadas, não vale a pena pedir a designacao da aula
    if(quantAulasGravadas!=0||quantAulasADecorrer!=0){
        //pedir designação da aula
        do{
            lerString("\n\nIndique a aula que deseja assistir (a decorrer ou gravada) através da sua designacao:", &(acesso.desigacaoAula), MAX_STRING);
            pos=procuraAula(acesso.desigacaoAula,aulasOnline,*quantAulas);
            if(pos==-1){
                printf("\n\nAula nao encontrada!");
            }
        }while(pos==-1);
        //verifica se a aula está a decorrer ou se já decorreu e se foi gravada
        if(strcmp(aulasOnline[pos].estado,"D")!=0&&strcmp(aulasOnline[pos].estado,"R")!=0||strcmp(aulasOnline[pos].gravacao,"S")!=0){
            printf("\nEsta aula nao se encontra disponivel!");
        }else{
            if(strcmp(aulasOnline[pos].estado,"D")==0){
                strcpy(acesso.tipoAcesso,"ON");
            }else{
                strcpy(acesso.tipoAcesso,"OFF");
            }
            acessos = realloc(acessos,(*quantAcessos+1)*sizeof(tipoAcesso));
            if(acessos == NULL){
                printf("\n\nErro! (erro ao reservar a memória)");
                acessos=pAcessos;
            }else{
                acessos[*quantAcessos]=acesso;
                (*quantAcessos)++;

                f = fopen("log_acessos.txt", "a");
                if(f==NULL){
                    printf("\n\nImpossivel aceder ao ficheiro de logs");
                }else{
                    if(strcmp(acesso.tipoAcesso,"ON")==0){
                        fprintf(f, "Estudante %d - Aula %s (Online)\n", acesso.numEstudante, acesso.desigacaoAula);
                    }else{
                        fprintf(f, "Estudante %d - Aula %s (Ofline)\n", acesso.numEstudante, acesso.desigacaoAula);
                    }
                    fclose(f);
                }

                printf("\n\nRegisto de acesso adicionado com sucesso!!");
            }
        }
    }
    return acessos;
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
