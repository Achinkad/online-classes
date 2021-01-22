#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "constantes.h"
#include "funcoes_auxiliares.h"
#include "funcoes_uc.h"

// Funcao para apresentar os dados relativos a uma aula online
void mostraAulas(tipoAulasOnline aulasOnline)
{
    printf("\nDesignacao: %s", aulasOnline.designacao);
    printf("\nCodigo da UC: %s", aulasOnline.codigoUC);
    printf("\nNome do docente: %s", aulasOnline.nomeDocente);

    // Apresentação do tipo de aula (T/TP/PL)
    if(strcmp(aulasOnline.tipo, "T") == 0)
    {
        printf("\nTipo de aula: Teorica");
    }
    else if(strcmp(aulasOnline.tipo, "TP") == 0)
    {
        printf("\nTipo de aula: Teorica-Pratica");
    }
    else
    {
        printf("\nTipo de aula: Pratica");
    }

    // Apresentação do estado da aula (A/D/R)
    if(strcmp(aulasOnline.estado, "A") == 0)
    {
        printf("\nEstado da aula: Agendada");
    }
    else if(strcmp(aulasOnline.estado, "D") == 0)
    {
        printf("\nEstado da aula: A decorrer");
    }
    else
    {
        printf("\nEstado da aula: Realizada");
    }

    // Apresentação da decisão da gravação da aula (S/N)
    if(strcmp(aulasOnline.gravacao, "S") == 0)
    {
        printf("\nGravacao: Sim");
    }
    else
    {
        printf("\nGravacao: Nao");
    }

    printf("\nData da aula: %d/%d/%d", aulasOnline.data.dia, aulasOnline.data.mes, aulasOnline.data.ano);
    printf("\nHora de inicio: %d:%d:%d", aulasOnline.horaInicio.hora, aulasOnline.horaInicio.minuto, aulasOnline.horaInicio.segundo);
    printf("\nHora de fim: %d:%d:%d", aulasOnline.horaFim.hora, aulasOnline.horaFim.minuto, aulasOnline.horaFim.segundo);
}

// Funcao que procura a designacao de uma aula e verifica a sua existencia
int procuraAula(char designacao[MAX_STRING], tipoAulasOnline aulasOnline[], int quantAulas)
{
    int i, pos = -1;
    for(i=0; i < quantAulas; i++)
    {
        if(strcmp(aulasOnline[i].designacao, designacao) == 0)
        {
            pos = i;
        }
    }
    return pos;
}

// Funcao que le os dados da estrutura tipoAulasOnline e retorna os seus valores
tipoAulasOnline lerDadosAulas()
{
    tipoAulasOnline e;
    char opcoesTipo[3][MAX_STRING] = {"T","TP","PL"};
    lerString("Indique o nome do docente: ", e.nomeDocente, MAX_STRING);
    lerOpcao("Indique o tipo de aula.\n\tT - Teorica \n\tTP - Teorico-Pratica\n\tPL - Pratica laboratorial\nOpcao: ", opcoesTipo, 3, e.tipo);
    printf("Inserir data da aula.\n");
    e.data = lerData();
    printf("\n\n");
    return e;
}

// Funcao que armazena os dados
tipoAulasOnline *agendaAula(tipoAulasOnline aulasOnline[], int *quantAulas, tipoUC ucs[MAX_UC], int quantUC)
{
    int posAula, posUC, i;
    char designacao[MAX_STRING], codigoUC[MAX_UC_CODIGO];
    tipoAulasOnline *pAulasOnline, dados;
    pAulasOnline = aulasOnline;

    lerString("Indique a designacao da aula: ", designacao, MAX_STRING);
    posAula = procuraAula(designacao, pAulasOnline, *quantAulas);

    if(posAula != -1)
    {
        printf("Designacao da aula já existe!\n");
    }

    lerString("Indique o codigo da UC: ", codigoUC, MAX_UC_CODIGO);
    posUC = procuraUC(codigoUC, ucs, quantUC);

    if(posUC == -1)
    {
        if(quantUC > 0)
        {
            printf("Codigo da UC nao existente! %d opcoes possiveis:\n", quantUC);
            for(i = 0; i < quantUC; i++)
            {
                printf("%s: %s\n", ucs[i].designacao, ucs[i].codigo);
            }
            printf("\n");
        }
        else
        {
            printf("O codigo da UC nao existe, porque nao ha ucs inseridas!\n");
        }
    }
    else
    {
        dados = lerDadosAulas();
        aulasOnline = realloc(aulasOnline,(*quantAulas+1)*sizeof(tipoAulasOnline));
        if(aulasOnline == NULL)
        {
            printf("Erro! Impossivel agendar aula.");
            aulasOnline = pAulasOnline;
        }
        else
        {
            aulasOnline[*quantAulas] = dados;
            strcpy(aulasOnline[*quantAulas].designacao, designacao);
            (*quantAulas)++;
        }
    }
    return aulasOnline;
}

void listaAulas(tipoAulasOnline aulasOnline[], int quantAulas)
{
    int i;
    if(quantAulas > 0)
    {
        printf("\n\n------------------ Inicio dos Resultados ------------------\n\n");
        printf("Quantidade de aulas: %d\t\t", quantAulas);
        for(i=0; i<quantAulas; i++)
        {
            mostraAulas(aulasOnline[i]);
            if(quantAulas-1 != i)
            {
                printf("\n-----------");
            }
        }
        printf("\n\n------------------ Fim dos Resultados ------------------\n\n");
    }
    else
    {
        printf("Nao existem aulas registadas no sistema.\n\n");
    }
}

tipoAulasOnline *leFichBinAulasOnline(tipoAulasOnline aulasOnline[], int *quantAulas)
{
    FILE *f;
    tipoAulasOnline *pAulasOnline;
    f=fopen("dadosAulasOnline.dat", "rb");
    if(f==NULL)
    {
        printf("\n\nNao foi possivel encontrar o ficheiro de Dados das Aulas Online!\n\n");
    }
    else
    {
        fread(&(*quantAulas),sizeof(int),1,f);
        pAulasOnline = aulasOnline;
        aulasOnline = realloc(aulasOnline,(*quantAulas)*sizeof(tipoAulasOnline));
        if(aulasOnline == NULL && *quantAulas != 0)
        {
            printf("\nErro! (erro ao reservar a memória)");
            aulasOnline=pAulasOnline;
        }
        else
        {
            fread(aulasOnline,sizeof(tipoAulasOnline),*quantAulas,f);
        }
        fclose(f);
    }
    return aulasOnline;
}

void escreveFichBinAulasOnline(tipoAulasOnline aulasOnline[], int quantAulas)
{
    FILE *f;
    f=fopen("dadosAulasOnline.dat", "wb");
    if(f==NULL)
    {
        printf("\n\nNao foi possivel encontrar o ficheiro de Dados das Aulas Online!\n\n");
    }
    else
    {
        fwrite(&quantAulas,sizeof(int),1,f);
        fwrite(aulasOnline,sizeof(tipoAulasOnline),quantAulas,f);
        fclose(f);
    }
}
