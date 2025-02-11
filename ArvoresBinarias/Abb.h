#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct No
{
    int valor;
    struct No *esq;
    struct No *dir;
    struct No *pai;
} No;

typedef struct Arvore
{
    No *raiz;
} Arvore;

typedef struct Fila
{
    No *vet[100];
    int inicio;
    int fim;
    int qtdElementos;
} Fila;

typedef struct Pilha
{
    int topo;
    int vet[100];
} Pilha;

int alturaAbb(No *arvore);

No *maximoAbb(No *aux);

No *minimoAbb(No *aux);

int sucessorAbb(Arvore *arvore);

int antecessorAbb(Arvore *arvore);

void insereAbb(int n, Arvore *arvore);

void deleteAbb(int n, Arvore *arvore);

// para arvore qualquer

int buscaEmLargura(int n, Arvore *arvore);

int buscaEmProfundidade(int n, Arvore *arvore);

void printArvore(Arvore *arvore);

void transplante(Arvore *arvore, No *a, No *b);

No *buscaAbb(int n, No * aux);

void percursoPosOrdem( No *aux);

void percursoEmOrdem( No *aux);