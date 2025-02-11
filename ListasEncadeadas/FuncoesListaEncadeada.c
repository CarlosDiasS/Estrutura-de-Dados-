#include "structListaEncadeada.h"

listaEncadeada *criaLista()
{

    listaEncadeada *aux = malloc(sizeof(listaEncadeada));
    if (aux == NULL)
    {
        printf("erro ao alocar memoria.");
        exit(1);
    }
    aux->cabeca = NULL;
    return aux;
}

No *buscaElemento(listaEncadeada *L, int chave)
{

    No *no = L->cabeca;
    // percorre toda a lista
    while (no != NULL && no->chave != chave)
    {
        no = no->prox;
    }
    return no;
}

void RemoveElemento(listaEncadeada *L, int chave)
{

    No *anterior = NULL;
    No *no = L->cabeca;
    // percorre toda a lista
    while ( no != NULL && no->chave != chave)
    {
        anterior = no;
        no = no->prox;
    }
    if (no == NULL)
    {
        printf("no invalido.");
    }
    // caso o no seja a cabeca
    else if (anterior == NULL)
    {
        L->cabeca = no->prox;
    }
    else
    {
        anterior->prox = no->prox;
    }
    free(no);
}

/**
 * @brief retorna o nó de um indice
 *
 */
No *acessaElemento(listaEncadeada *L, int i)
{

    No *no = L->cabeca;
    int j = 0;
    // percorre toda a lista
    while (j != i)
    {
        no = no->prox;
        j++;
    }
    if(no==NULL) {
        printf("indice invalido");
        exit(1);
    }
    return no;
}

void insere(listaEncadeada *L, int x, int i)
{
    if (L == NULL)
        return;
    No *no = L->cabeca;
    No *anterior = NULL;
    No *novo = malloc(sizeof(No));
    if (novo == NULL)
    {
        printf("erro ao alocar memoria.");
        exit(1);
    }
    novo->chave = x;
    novo->prox = NULL;
    if (i == 0)
    { // no inicio da lista
        novo->prox = L->cabeca;
        L->cabeca = novo;
    }
    else
    {
        int j = 0;
        // percorre toda a lista
        while (j != i)
        {
            anterior = no;
            no = no->prox;
            j++;
        }
        if (anterior != NULL)
        {
            anterior->prox = novo;
            novo->prox = no;
        }
    }
}

void imprimeLista(listaEncadeada *lista){
    
    No *no = lista->cabeca;
    while(no!= NULL){
        printf("%d ", no->chave);
        no = no->prox;
    }
    printf("\n");
}

int main()
{
    listaEncadeada *lista = criaLista();
    insere(lista, 2,0);
    insere(lista, 22,1);
    insere(lista, 3,2);
    insere(lista, 44,3);
    
    RemoveElemento(lista,2);
    printf("%d\n",lista->cabeca->chave);

    No *no = acessaElemento(lista,2);
    printf("%d", no->chave);
    printf("\n");
    imprimeLista(lista);
    return 0;
}
