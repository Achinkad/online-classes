#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "funcoes_auxiliares.h"

int main()
{
    setlocale(LC_ALL, "");    // para o texto sair bem (mesmo os acentos)

    printf("Hello Ad�o!\n");

    return 0;
}
