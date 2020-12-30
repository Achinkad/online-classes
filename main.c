#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>

#include "funcoes_auxiliares.h"
#include "funcoes_tipoAula.h"
#include "funcoes_uc.h"

int main()
{
    tipoUC ucs[MAX_UC];
    int quantUC=0;
    char opcao;
    setlocale(LC_ALL, "");

    opcao = menu();
    verificaOpcao(opcao, ucs, quantUC);

    return 0;
}
