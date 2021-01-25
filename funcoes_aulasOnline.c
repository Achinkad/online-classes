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

    printf("\nData da aula: %.2d/%.2d/%d", aulasOnline.data.dia, aulasOnline.data.mes, aulasOnline.data.ano);

    if(aulasOnline.horaInicio.hora != -1 && aulasOnline.horaInicio.minuto != -1 && aulasOnline.horaInicio.segundo != -1)
    {
        printf("\nHora de inicio: %.2d:%.2d:%.2d", aulasOnline.horaInicio.hora, aulasOnline.horaInicio.minuto, aulasOnline.horaInicio.segundo);
    }
    else
    {
        printf("\nHora de inicio: N/A");
    }

    if(aulasOnline.horaFim.hora != -1 && aulasOnline.horaFim.minuto != -1 && aulasOnline.horaFim.segundo != -1)
    {
        printf("\nHora de fim: %.2d:%.2d:%.2d", aulasOnline.horaFim.hora, aulasOnline.horaFim.minuto, aulasOnline.horaFim.segundo);
    }
    else
    {
        printf("\nHora de inicio: N/A");
    }

    if(strcmp(aulasOnline.estado, "R")==0)
    {
        printf("\n\tEstudantes Presentes: %d", aulasOnline.contEstudantesPresentes);
        if(strcmp(aulasOnline.gravacao, "S")==0)
        {
            printf("\n\tAcessos a Gravacao: %d", aulasOnline.contEstudantesPresentes);
        }
    }
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

tipoAulasOnline lerDadosAulas(tipoUC uc, char codigo[], tipoAulasOnline aulas[], int quantAulas)
{
    tipoAulasOnline e;
    int i, pos = -1, quantTipoTotal;
    lerString("Indique o nome do docente: ", e.nomeDocente, MAX_STRING);
    printf("Indique a data da aula a agendar.\n");
    e.data = lerData();

    if(strcmp(uc.regime, "D") == 0)
    {
        printf("Indique a hora de início da aula.\n");
        e.horaInicio = lerHora(8, 18);
    }
    else
    {
        printf("Indique a hora de início da aula.\n");
        e.horaInicio = lerHora(18, 24);
    }

    for(i=0; i<quantAulas; i++)
    {
        if(strcmp(aulas[i].codigoUC, codigo) == 0 && aulas[i].data.ano == e.data.ano && aulas[i].data.mes == e.data.mes && aulas[i].data.dia == e.data.dia)
        {
            pos = i;
        }
    }

    if(pos != -1 && aulas[pos].horaInicio.hora == e.horaInicio.hora && aulas[pos].horaInicio.minuto == e.horaInicio.minuto)
    {
        printf("Já existe uma aula da mesma UC agendada para este horário.\n\n");
    }
    else
    {
        return e;
    }
}

char verificaTipoAula(tipoUC uc, int *verificaTipo)
{
    char tipo[MAX_STRING];
    char opcoesTipo[3][MAX_STRING] = {"T","TP","PL"};
    int quantTipoTotal;

    lerOpcao("Indique o tipo de aula.\n\tT - Teorica \n\tTP - Teorico-Pratica\n\tPL - Pratica laboratorial\nOpção: ", opcoesTipo, 3, tipo);

    if(strcmp(tipo, "TP") == 0)
    {
        quantTipoTotal = uc.aulasTP.contAgendadas + uc.aulasTP.contRealizadas;
        if(quantTipoTotal > uc.aulasTP.quantAulas)
        {
            printf("Não é possível adicionar mais aulas TP para esta UC.\n");
            *verificaTipo = 0;
        }
        else
        {
            *verificaTipo = 1;
        }
    }

    if(strcmp(tipo, "T") == 0)
    {
        quantTipoTotal = uc.aulasT.contAgendadas + uc.aulasT.contRealizadas;
        if(quantTipoTotal > uc.aulasT.quantAulas)
        {
            printf("Não é possível adicionar mais aulas T para esta UC.\n");
            *verificaTipo = 0;
        }
        else
        {
            *verificaTipo = 1;
        }
    }

    if(strcmp(tipo, "PL") == 0)
    {
        quantTipoTotal = uc.aulasPL.contAgendadas + uc.aulasPL.contRealizadas;
        if(quantTipoTotal > uc.aulasPL.quantAulas)
        {
            printf("Não é possível adicionar mais aulas PL para esta UC.\n");
            *verificaTipo = 0;
        }
        else
        {
            *verificaTipo = 1;
        }
    }
    return tipo[MAX_STRING];
}

tipoAulasOnline *agendaAula(tipoAulasOnline aulasOnline[], int *quantAulas, tipoUC ucs[MAX_UC], int quantUC, int *quantAulasAgendadas)
{
    int posAula, posUC, i, verificaTipo=0;
    char designacao[MAX_STRING], codigoUC[MAX_UC_CODIGO], tipo[MAX_STRING];
    tipoAulasOnline *pAulasOnline, dados;
    pAulasOnline = aulasOnline;

    lerString("Indique a designação da aula: ", designacao, MAX_STRING);
    posAula = procuraAula(designacao, pAulasOnline, *quantAulas);

    if(posAula != -1)
    {
        printf("Desginação da aula já existe!\n");
    }
    else
    {
        lerString("Indique o código da UC: ", codigoUC, MAX_UC_CODIGO);
        posUC = procuraUC(codigoUC, ucs, quantUC);

        if(posUC == -1)
        {
            if(quantUC > 0)
            {
                printf("\nCódigo da UC não existente! Há %d opções possíveis:\n", quantUC);
                for(i = 0; i < quantUC; i++)
                {
                    printf("- %s -> %s\n", ucs[i].designacao, ucs[i].codigo);
                }
                printf("\n");
            }
            else
            {
                printf("\nO código da UC não existe, visto não haver UC's inseridas!\n");
            }
        }
        else
        {
            tipo[MAX_STRING] = verificaTipoAula(ucs[posUC], &verificaTipo);
            if(verificaTipo == 1)
            {
                dados = lerDadosAulas(ucs[posUC], codigoUC, aulasOnline, *quantAulas);
                aulasOnline = realloc(aulasOnline, (*quantAulas+1)*sizeof(tipoAulasOnline));
                if(aulasOnline == NULL)
                {
                    printf("Erro! Impossivel agendar aula.");
                    aulasOnline = pAulasOnline;
                }
                else
                {
                    aulasOnline[*quantAulas] = dados;
                    strcpy(aulasOnline[*quantAulas].designacao, designacao);
                    strcpy(aulasOnline[*quantAulas].codigoUC, codigoUC);
                    strcpy(aulasOnline[*quantAulas].estado, "A");
                    strcpy(aulasOnline[*quantAulas].gravacao, "N");
                    aulasOnline[*quantAulas].horaFim.hora = -1;
                    aulasOnline[*quantAulas].horaFim.minuto = -1;
                    aulasOnline[*quantAulas].horaFim.segundo = -1;

                    if(strcmp(tipo, "T") == 0)
                    {
                        (ucs[posUC].aulasT.contAgendadas)++;
                    }
                    else if(strcmp(tipo, "TP") == 0)
                    {
                        (ucs[posUC].aulasTP.contAgendadas)++;
                    }
                    else if(strcmp(tipo, "PL") == 0)
                    {
                        (ucs[posUC].aulasPL.contAgendadas)++;
                    }
                    (*quantAulas)++;
                    (*quantAulasAgendadas)++;
                }
            }
        }
    }
    printf("Aula agendada com sucesso!\n\n");
    return aulasOnline;
}

void listaAulas(tipoAulasOnline aulasOnline[], int quantAulas)
{
    int i;
    if(quantAulas > 0)
    {
        printf("\n\n------------------ Inicio dos Resultados ------------------\n\n");
        printf("Quantidade de aulas: %d\n\n", quantAulas);
        for(i=0; i<quantAulas; i++)
        {
            mostraAulas(aulasOnline[i]);
            if(quantAulas-1 != i)
            {
                printf("\n\n-----------\n");
            }
        }
        printf("\n\n------------------ Fim dos Resultados ------------------\n\n\n");
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
    f = fopen("dadosAulasOnline.dat", "rb");
    if(f == NULL)
    {
        printf("Não foi possível encontrar o ficheiro de dados das aulas online.\n\n");
    }
    else
    {
        fread(&(*quantAulas), sizeof(int), 1, f);
        pAulasOnline = aulasOnline;
        aulasOnline = realloc(aulasOnline, (*quantAulas)*sizeof(tipoAulasOnline));
        if(aulasOnline == NULL && *quantAulas != 0)
        {
            printf("\nErro ao reservar a memória!\n\n");
            aulasOnline = pAulasOnline;
        }
        else
        {
            fread(aulasOnline, sizeof(tipoAulasOnline), *quantAulas, f);
        }
        fclose(f);
    }
    return aulasOnline;
}

void escreveFichBinAulasOnline(tipoAulasOnline aulasOnline[], int quantAulas)
{
    FILE *f;
    f = fopen("dadosAulasOnline.dat", "wb");
    if(f == NULL)
    {
        printf("Não foi possível encontrar o ficheiro de dados das aulas online!\n\n");
    }
    else
    {
        fwrite(&quantAulas, sizeof(int), 1, f);
        fwrite(aulasOnline, sizeof(tipoAulasOnline), quantAulas, f);
        fclose(f);
    }
}

char menuEditarAula(tipoAulasOnline aula)
{
    char op;

    printf("\n\n----------------- Edicao da aula: %s -----------------\n", aula.designacao);

    // Dados da aula online a editar
    printf("\nDesignacao da aula: %s", aula.designacao);
    printf("\t\tCodigo da UC associada: %s", aula.codigoUC);
    printf("\nNome do docente: %s", aula.nomeDocente);

    // Apresentação do tipo de aula (T/TP/PL)
    if(strcmp(aula.tipo, "T") == 0)
    {
        printf("\t\tTipo de aula: Teorica");
    }
    else if(strcmp(aula.tipo, "TP") == 0)
    {
        printf("\t\tTipo de aula: Teorica-Pratica");
    }
    else
    {
        printf("\t\tTipo de aula: Pratica");
    }

    // Apresentação do estado da aula (A/D/R)
    if(strcmp(aula.estado, "A") == 0)
    {
        printf("\nEstado da aula: Agendada");
    }
    else if(strcmp(aula.estado, "D") == 0)
    {
        printf("\nEstado da aula: A decorrer");
    }
    else
    {
        printf("\nEstado da aula: Realizada");
    }

    // Apresentação da decisão da gravação da aula (S/N)
    if(strcmp(aula.gravacao, "S") == 0)
    {
        printf("\t\tGravacao: Sim");
    }
    else
    {
        printf("\t\tGravacao: Nao");
    }

    printf("\nData da aula: %.2d/%.2d/%.2d", aula.data.dia, aula.data.mes, aula.data.ano);
    if(aula.horaInicio.hora != -1 && aula.horaInicio.minuto != -1 && aula.horaInicio.segundo != -1)
    {
        printf("\nHora de inicio: %.2d:%.2d:%.2d", aula.horaInicio.hora, aula.horaInicio.minuto, aula.horaInicio.segundo);
    }

    if(aula.horaFim.hora != -1 && aula.horaFim.minuto != -1 && aula.horaFim.segundo != -1)
    {
        printf("\nHora de fim: %.2d:%.2d:%.2d", aula.horaFim.hora, aula.horaFim.minuto, aula.horaFim.segundo);
    }

    printf("\n\n\tA - Editar codigo da UC associada");
    printf("\n\tB - Editar o nome do docente");
    printf("\n\tC - Editar tipo de aula");
    printf("\n\tD - Editar a data da aula");
    printf("\n\tS - Concluir edição");
    printf("\n\nInsira uma opcao: ");
    scanf("%c", &op);
    limpaBufferStdin();
    op = toupper(op);
    return op;
}

void editarAula(tipoAulasOnline aulasOnline[], int quantAulas, int quantAulasAgendadas, tipoUC ucs[MAX_UC], int quantUC)
{
    char opcoesTipo[3][MAX_STRING] = {"T","TP","PL"};
    char designacao[MAX_STRING], opcaoMenu, novoCodigoUC[MAX_UC_CODIGO];
    int pos, posUC, i;

    lerString("Indique a designacao da aula a editar: ", designacao, MAX_STRING);
    pos = procuraAula(designacao, aulasOnline, quantAulas);

    if(pos != -1)
    {
        do
        {
            opcaoMenu = menuEditarAula(aulasOnline[pos]);
            switch(opcaoMenu)
            {
            case 'A':
                lerString("Indique o codigo da UC a substituir: ", novoCodigoUC, MAX_UC_CODIGO);
                posUC = procuraUC(novoCodigoUC, ucs, quantUC);
                if(posUC != -1)
                {
                    strcpy(aulasOnline[pos].codigoUC, novoCodigoUC);
                    printf("Codigo da UC editado com sucesso!\n");
                }
                else
                {
                    if(quantUC > 0)
                    {
                        printf("Código da UC não existe! Há %d opcões possíveis:\n", quantUC);
                        for(i = 0; i < quantUC; i++)
                        {
                            printf("-> %s: %s\n", ucs[i].designacao, ucs[i].codigo);
                        }
                    }
                    else
                    {
                        printf("O código da UC não existe, porque não existem UC'S no sistema.\n");
                    }
                }
                break;
            case 'B':
                lerString("Indique o novo nome do docente: ", aulasOnline[pos].nomeDocente, MAX_STRING);
                printf("Nome do docente editado com sucesso!\n");
                break;
            case 'C':
                lerOpcao("Indique o novo tipo de aula.\n\tT - Teorica \n\tTP - Teorico-Pratica\n\tPL - Pratica laboratorial\nOpcao: ", opcoesTipo, 3, aulasOnline[pos].tipo);
                printf("Tipo de aula editado com sucesso!\n");
                break;
            case 'D':
                aulasOnline[pos].data = lerData();
                printf("Data da aula editada com sucesso!\n");
                break;
            case 'S':
                break;
            default:
                printf("Opção invalida!");
                break;
            }
        }
        while(opcaoMenu != 'S');
    }
    else
    {
        printf("A designação da aula que colocou não existe.\nOpções possíveis:\n");
        for(i=0; i<quantAulas; i++)
        {
            if(strcmp(aulasOnline[i].estado, "A") == 0)
            {
                printf("-> %s\n", aulasOnline[i].designacao);
            }
        }
        printf("\n");
    }
}

tipoAulasOnline *eliminaAula(tipoAulasOnline aulasOnline[], int *quantAulas, tipoUC ucs[], int quantUC)
{
    tipoAulasOnline *pAulasOnline;
    char designacao[MAX_STRING], verificao;
    int i, pos, posUC, pQuantAulas;

    pAulasOnline = aulasOnline;

    lerString("Indique a designação da aula que pretende eliminar: ", designacao, MAX_STRING);
    pos = procuraAula(designacao, pAulasOnline, *quantAulas);

    if(pos != -1)
    {
        printf("Pretende mesmo eliminar a aula \"%s\"? (S)im / (N)ão: ", aulasOnline[pos].designacao);
        scanf("%s", &verificao);
        limpaBufferStdin();
        verificao = toupper(verificao);

        switch(verificao)
        {
        case 'S':
            for(i=pos; i < *quantAulas-1; i++)
            {
                aulasOnline[i] = aulasOnline[i+1];
            }
            aulasOnline = realloc(aulasOnline, (*quantAulas-1)*sizeof(tipoAulasOnline));

            if(aulasOnline == NULL && (*quantAulas-1) != 0)
            {
                printf("Erro na alocação de memória!\n\n");
                aulasOnline = pAulasOnline;
            }

            posUC = procuraUC(aulasOnline[pos].codigoUC, ucs, quantUC);
            if(strcmp(aulasOnline[pos].tipo, "T") == 0)
            {
                (ucs[posUC].aulasT.contAgendadas)--;
            }
            else if(strcmp(aulasOnline[pos].tipo, "TP") == 0)
            {
                (ucs[posUC].aulasTP.contAgendadas)--;
            }
            else if(strcmp(aulasOnline[pos].tipo, "PL") == 0)
            {
                (ucs[posUC].aulasPL.contAgendadas)--;
            }
            (*quantAulas)--;
            break;

        case 'N':
            printf("O sistema avisa que a aula não foi eliminada.\n\n");
            break;

        default:
            printf("Opção inválida!\n\n");
            break;
        }
    }
    else
    {
        pQuantAulas = *quantAulas;
        printf("A designação da aula que colocou não existe.\nOpções possíveis:\n");
        for(i=0; i<pQuantAulas; i++)
        {
            if(strcmp(aulasOnline[i].estado, "A") == 0)
            {
                printf("-> %s\n", aulasOnline[i].designacao);
            }
        }
        printf("\n");
    }
    return aulasOnline;
}

void iniciarAula(tipoAulasOnline aulasOnline[], int quantAulas, tipoUC ucs[], int quantUC, int *quantAulasDecorrer, int *quantAulasAgendadas)
{
    int pos, posUC, i;
    char designacao[MAX_STRING];
    char opcoesGravacao[2][MAX_STRING] = {"S","N"};

    lerString("Indique a designação da aula para registar o seu início: ", designacao, MAX_STRING);
    pos = procuraAula(designacao, aulasOnline, quantAulas);

    if(pos != -1 && strcmp(aulasOnline[pos].estado, "A") == 0)
    {
        lerOpcao("Pretende gravar a aula? (S)im/(N)ão: ", opcoesGravacao, 2, aulasOnline[pos].gravacao);
        strcpy(aulasOnline[pos].estado, "D");
        printf("Início de aula registada com sucesso!\n\n");
        posUC = procuraUC(aulasOnline[pos].codigoUC, ucs, quantUC);
        if(strcmp(aulasOnline[pos].tipo, "T") == 0)
        {
            (ucs[posUC].aulasT.contAgendadas)--;
        }
        else if(strcmp(aulasOnline[pos].tipo, "TP") == 0)
        {
            (ucs[posUC].aulasTP.contAgendadas)--;
        }
        else if(strcmp(aulasOnline[pos].tipo, "PL") == 0)
        {
            (ucs[posUC].aulasPL.contAgendadas)--;
        }
        (*quantAulasDecorrer)++;
        (*quantAulasAgendadas)--;
    }
    else
    {
        printf("A designação da aula que colocou não existe para dar início a mesma.\nOpções possíveis:\n");
        for(i=0; i<quantAulas; i++)
        {
            if(strcmp(aulasOnline[i].estado, "A") == 0)
            {
                printf("-> %s\n", aulasOnline[i].designacao);
            }
        }
        printf("\n");
    }
}

void finalizarAula(tipoAulasOnline aulasOnline[], int quantAulas, tipoUC ucs[], int quantUC, int *quantAulasDecorrer, int *quantAulasRealizadas, int *quantAulasGravadas)
{
    int pos, posUC, i;
    char designacao[MAX_STRING];

    lerString("Indique a designacao da aula para registar o seu término: ", designacao, MAX_STRING);
    pos = procuraAula(designacao, aulasOnline, quantAulas);

    if(pos != -1 && strcmp(aulasOnline[pos].estado, "D") == 0)
    {
        printf("Insira a hora de término da aula.\n");
        aulasOnline[pos].horaFim = lerHora(0, 23);
        strcpy(aulasOnline[pos].estado, "R");
        printf("Término da aula registada com sucesso!\n\n");

        posUC = procuraUC(aulasOnline[pos].codigoUC, ucs, quantUC);
        if(strcmp(aulasOnline[pos].tipo, "T") == 0)
        {
            (ucs[posUC].aulasT.contRealizadas)++;
        }
        else if(strcmp(aulasOnline[pos].tipo, "TP") == 0)
        {
            (ucs[posUC].aulasTP.contRealizadas)++;
        }
        else if(strcmp(aulasOnline[pos].tipo, "PL") == 0)
        {
            (ucs[posUC].aulasPL.contRealizadas)++;
        }

        if(strcmp(aulasOnline[pos].gravacao, "S") == 0)
        {
            if(strcmp(aulasOnline[pos].tipo, "T") == 0)
            {
                (ucs[posUC].aulasT.contGravadas)++;
            }
            else if(strcmp(aulasOnline[pos].tipo, "TP") == 0)
            {
                (ucs[posUC].aulasTP.contGravadas)++;
            }
            else if(strcmp(aulasOnline[pos].tipo, "PL") == 0)
            {
                (ucs[posUC].aulasPL.contGravadas)++;
            }
            (*quantAulasGravadas)++;
        }

        (*quantAulasDecorrer)--;
        (*quantAulasRealizadas)++;
    }
    else
    {
        printf("A designação da aula que colocou não existe para dar o seu término.\nOpções possíveis:\n");
        for(i=0; i<quantAulas; i++)
        {
            if(strcmp(aulasOnline[i].estado, "D") == 0)
            {
                printf("-> %s\n", aulasOnline[i].designacao);
            }
        }
        printf("\n");
    }
}
