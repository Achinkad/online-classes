#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>
#include "funcoes_auxiliares.h"

int main()
{
    char opcao;
    setlocale(LC_ALL, "");

    printf("(G)estao de Unidades Curriculares\n");
    scanf("%c", &opcao);
    limpaBufferStdin();
    opcao = toupper(opcao);

    switch(opcao){
        case 'G': printf("test");
        break;
    }

    return 0;
}
