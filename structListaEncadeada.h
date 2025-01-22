#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct No{
    int chave;
    struct No *prox;
}No;

typedef struct listaEncadeada{
    No *cabeca;
}listaEncadeada;

