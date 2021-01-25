#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "constantes.h"
#include "funcoes_auxiliares.h"
#include "funcoes_aulasOnline.h"
#include "funcoes_uc.h"
#include "funcoes_estudante.h"

tipoAcesso *registarAcesso(tipoAcesso acessos[], int *quantAcessos, tipoAulasOnline aulasOnline[], int quantAulas, tipoUC ucs[], int quantUCs, tipoEstudantes estudantes[], int quantEstudantes, int quantAulasADecorrer, int quantAulasGravadas){
    int i, pos, posUC, posEstudante;
    tipoAcesso acesso;
    tipoAcesso *pAcessos=acessos;
    char designacao[MAX_STRING];
    FILE *f;
    acesso.numEstudante=lerInteiro("Indique o n�mero de Estudante:",1,tamanhoNumEstudantes);
    posEstudante = procuraEstudante(estudantes,acesso.numEstudante,quantEstudantes);
    if(posEstudante!=-1){
        //mostrar as aulas a decorrer no momento
        printf("\n\nAulas a Decorrer neste momento:\n");
        if(quantAulasADecorrer>0){
            for(i=0;i<quantAulas;i++){
                if(strcmp(aulasOnline[i].estado,"D")==0){
                    printf("\n|  Designacao:%s", aulasOnline[i].designacao);
                    printf("\n|\tInicio: %d:%d", aulasOnline[i].horaInicio.hora, aulasOnline[i].horaInicio.minuto);
                    printf("\n|\tDocente: %s", aulasOnline[i].nomeDocente);
                }
            }
        }
        else{
            printf("\n -> N�o existem Aulas a decorrer neste momento!");
        }
        //mostrar as aulas gravadas dispon�veis
        printf("\n\nAulas realizadas e gravadas:\n");
        if(quantAulasGravadas>0){
            for(i=0;i<quantAulas;i++){
                if(strcmp(aulasOnline[i].estado,"R")==0&&strcmp(aulasOnline[i].gravacao,"S")==0){
                    printf("\n|  Designacao:%s", aulasOnline[i].designacao);
                    printf("\n|\tInicio: %d:%d", aulasOnline[i].horaInicio.hora, aulasOnline[i].horaInicio.minuto);
                    printf("\n|\tDocente: %s", aulasOnline[i].nomeDocente);
                }
            }
        }else{
            printf("\n -> N�o existem Aulas gravadas dispon�veis!");
        }
        //Se n�o houver aulas a decorrer ou gravadas, n�o vale a pena pedir a designacao da aula
        if(quantAulasGravadas!=0||quantAulasADecorrer!=0){
            //pedir designa��o da aula
            do{
                lerString("\n\nIndique a aula que deseja assistir (a decorrer ou gravada) atrav�s da sua designacao:", designacao, MAX_STRING);
                pos=procuraAula(designacao, aulasOnline, quantAulas);
                if(pos==-1){
                    printf("\n\nAula nao encontrada!");
                }
            }while(pos==-1);
            //verifica se a aula est� a decorrer ou se j� decorreu e se foi gravada
            if(strcmp(aulasOnline[pos].estado,"D")!=0&&strcmp(aulasOnline[pos].estado,"R")!=0){
                printf("\nEsta aula nao se encontra disponivel!");
            }else{
                if(strcmp(aulasOnline[pos].estado,"R")==0 && strcmp(aulasOnline[pos].gravacao,"N")==0){
                    printf("\nEsta aula nao foi gravada!");
                }else{
                    if(strcmp(aulasOnline[pos].estado,"D")==0){
                        strcpy(acesso.tipoAcesso,"ON");
                    }else{
                        strcpy(acesso.tipoAcesso,"OFF");

                        //incrementar acessos na uc quando s�o acessos a grava��es
                        posUC=procuraUC(designacao,ucs,quantUCs);
                        ucs[posUC].contAcessosGravacoes++;
                        printf("\n\nAcessos: %d\n\n", ucs[posUC].contAcessosGravacoes);
                    }
                    strcpy(acesso.desigacaoAula, designacao);
                    acessos = realloc(acessos,(*quantAcessos+1)*sizeof(tipoAcesso));
                    if(acessos == NULL){
                        printf("\n\nErro! (erro ao reservar a mem�ria)");
                        acessos=pAcessos;
                    }else{
                        acessos[*quantAcessos]=acesso;
                        (*quantAcessos)++;

                        if(strcmp(acesso.tipoAcesso,"ON")==0){
                            (aulasOnline[pos].contEstudantesPresentes)++;
                        }else{
                            (aulasOnline[pos].contAcessosGravacoes)++;
                        }

                        f = fopen("log_acessos.txt", "a");
                        if(f==NULL){
                            printf("\n\nImpossivel aceder ao ficheiro de logs");
                        }else{
                            if(strcmp(acesso.tipoAcesso,"ON")==0){
                                fprintf(f, "Estudante %d - Aula %s (Online)\n", acesso.numEstudante, acesso.desigacaoAula);
                            }else{
                                fprintf(f, "Estudante %d - Aula %s (Offline)\n", acesso.numEstudante, acesso.desigacaoAula);
                            }
                            fclose(f);
                        }

                        printf("\nRegisto de acesso adicionado com sucesso!!");
                    }
                }
            }
        }
    }else{
        printf("O numero de Estudante que colocou n�o existe.\nEstudantes registados:\n");
        for(i=0; i<quantEstudantes; i++)
        {
            printf("-> %s\n", estudantes[i].nome);

        }
        printf("\n");
    }

    return acessos;
}

tipoAcesso *leFichBinAcessos(tipoAcesso acessos[], int *quantAcessos){
    FILE *f;
    tipoAcesso *pAcessos;
    f=fopen("dadosAcessos.dat", "rb");
    if(f==NULL){
        printf("\n\nNao foi possivel encontrar o ficheiro de Dados dos Acessos �s Aulas Online!\n\n");
    }else{
        fread(&(*quantAcessos),sizeof(int),1,f);
        pAcessos = acessos;
        acessos = realloc(acessos,(*quantAcessos)*sizeof(tipoAcesso));
        if(acessos == NULL && *quantAcessos != 0){
            printf("\nErro! (erro ao reservar a mem�ria)");
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
        printf("\n\nNao foi possivel encontrar o ficheiro de Dados dos Acessos �s Aulas Online!\n\n");
    }else{
        fwrite(&quantAcessos,sizeof(int),1,f);
        fwrite(acessos,sizeof(tipoAcesso),quantAcessos,f);
        fclose(f);
    }
}

void verificarPresencas(tipoAulasOnline aulasOnline[], int quantAulas, tipoAcesso acessos[], int quantAcessos, tipoEstudantes estudantes[], int quantEstudante){
    int pos, posEstudante, i;
    char designacao[MAX_STRING];
    if(quantAulas==0){
        printf("\n\nNao existem aulas!");
    }else{
        lerString("Indique a designacao da Aula Online:", designacao,MAX_STRING);
        pos = procuraAula(designacao, aulasOnline, quantAulas);

        if(pos != -1)
        {
            if(strcmp(aulasOnline[pos].estado,"A")==0){
                printf("\nEsta aula ainda nao foi iniciada!");
            }else{
                printf("\n------------ Presencas na Aula %s -----------\n", aulasOnline[pos].designacao);
                printf("Data: %.2d-%.2d-%.2d %.2d:%.2d \tDocente:%s", aulasOnline[pos].data.dia, aulasOnline[pos].data.mes, aulasOnline[pos].data.ano, aulasOnline[pos].horaInicio.hora, aulasOnline[pos].horaInicio.minuto, aulasOnline[pos].nomeDocente);
                printf("\n\nPresen�as(%d):", aulasOnline[pos].contEstudantesPresentes);
                for(i=0;i<quantAcessos;i++){
                    if(strcmp(acessos[i].desigacaoAula, aulasOnline[pos].designacao)==0&&strcmp(acessos[i].tipoAcesso, "ON")==0){
                        printf("\n\t- n%d ", acessos[i].numEstudante);
                        posEstudante=procuraEstudante(estudantes,acessos[i].numEstudante,quantEstudante);
                        if(posEstudante!=-1)
                        {
                            printf("- %s", estudantes[posEstudante].nome);
                        }
                    }
                }
                printf("\n\n---------------------------------------------\n\n\n");
            }
        }
        else
        {
            printf("A designa��o da aula que colocou n�o existe.\nAulas registadas:\n");
            for(i=0; i<quantAulas; i++)
            {
                printf("-> %s\n", aulasOnline[i].designacao);

            }
            printf("\n");
        }
    }
}
