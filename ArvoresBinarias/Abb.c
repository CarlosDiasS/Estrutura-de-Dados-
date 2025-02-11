#include "Abb.h"

No *criaNo(int n){
    No *aux = malloc(sizeof(No));
    if(!aux) exit(1);
    aux->valor = n;
    aux->dir = NULL;
    aux->esq = NULL;
    aux->pai = NULL;
    return aux;
}

/*
    estrutura fila auxiliar
    -> utilizada para Busca em Largura

*/
Fila *criaFila(){
    Fila *aux = malloc(sizeof(Fila));
    if(!aux) exit(1);
    aux->inicio = 0;
    aux->qtdElementos = 0;
    aux->fim = 0;
    return aux;
}

int filaVazia(Fila *fila){
    return (fila->qtdElementos==0)?1:0;
}

//enfilera e desenfilera

void enfileraFila(No *novo, Fila *fila){

    fila->vet[fila->fim] = novo;
    if(fila->fim == fila->qtdElementos){
        fila->fim = 1;
    }
    else{
        fila->fim++;
    }
}

No *desenfileraFila(Fila *fila){
    No *aux = fila->vet[fila->inicio];
    if(fila->inicio == fila->qtdElementos){
        fila->inicio = 1;
    }
    else{
        fila->inicio++;
    }
    return aux;
}

/*
    estrutura pilha auxiliar
    -> utilizada para Busca em Profundidade
    -> pode ser substituida por recursao 

*/
Pilha *criaPilha(){
    Pilha *aux = malloc(sizeof(Pilha));
    if(!aux) exit(1);
    aux->topo = 0;
    return aux;
}

int alturaAbb(No *no){

    if(no == NULL) return -1;
    int altDir = alturaAbb(no->dir);
    int AltEsq = alturaAbb(no->esq);
    //+1 devido ao no pai
    if(AltEsq > altDir){
        return AltEsq +1;
    }
    else{
        return altDir +1;
    }
}

No *maximoAbb(No * aux){

    while (aux->dir != NULL)
    {
        aux = aux->dir;
    }
    return aux;
}

No *minimoAbb(No * aux){
    
    while (aux->esq != NULL)
    {
        aux = aux->esq;
    }
    return aux;
}

int sucessorAbb(Arvore *arvore){

    if(!arvore) exit(1);
    No * aux = arvore->raiz;

    aux = aux->dir;
    while(aux->esq !=NULL){
        aux = aux->esq;
    }
    return aux->valor;
}

int antecessorAbb(Arvore *arvore){
     if(!arvore) exit(1);
    No * aux = arvore->raiz;

    aux = aux->esq;
    while(aux->dir !=NULL){
        aux = aux->dir;
    }
    return aux->valor;
}

void insereAbb(int n, Arvore *arvore){

    No *novo  = criaNo(n);
    No *aux = NULL;
    No *aux2 = arvore->raiz;
    while(aux2 !=NULL){
        aux = aux2;
        if(novo->valor < aux2->valor){
            aux2 = aux2->esq;
        }
        else{
            aux2 = aux2->dir;
        }
    }
    novo->pai = aux;
    //se a arvore estiver vazia 
    if(aux ==NULL){
        arvore->raiz = novo;
        printf("No adicionado.\n");
    }
    else if(novo->valor < aux->valor){
        aux->esq = novo;
        printf("No adicionado.\n");
    }
    else{
        aux->dir = novo;
        printf("No adicionado.\n");
    }
}
/*
    Visita primeiro a sub-arvore da esquerda 
    imprime o no atual
    Visita a sub-arvore da direita

    -> imprime os elementos ordenados
 */
void percursoEmOrdem( No *aux){

    if(!aux) return;
    percursoEmOrdem(aux->esq);
    printf("%d ", aux->valor);
    percursoEmOrdem(aux->dir);
}
/*
    Visita primeiro a sub-arvore da esquerda 
    Visita a sub-arvore da direita
    imprime o no atual

    -> imprime os elementos em forma de vetor como uma arvore
    -> ideal para notacao polonesa
 */
void percursoPosOrdem( No *aux){

    if(!aux) return;
    percursoEmOrdem(aux->esq);
    percursoEmOrdem(aux->dir);
    printf("%d", aux->valor);
}
/*
    Percoore todos os nos de um nivel 
    ->garante o caminho mais curto em um grafo n ponderado

*/
void buscaLargura(Arvore *arvore){
    Fila *fila = criaFila();
    No *aux = arvore->raiz;
    if(!aux) return;
    enfileraFila(aux, fila);
    while(!filaVazia(fila)){
        aux = desenfileraFila(fila);
        printf("%d", aux->valor);
        enfileraFila(aux->dir,fila);
        enfileraFila(aux->esq,fila);
    }
}

No *buscaAbb(int n, No * aux){

    if(aux == NULL) exit(1);

    //caso base
    if(!n|| n == aux->valor) return aux;

    if(n < aux->valor){
        return buscaAbb(n,aux->esq);
    }
    else{
        return buscaAbb(n,aux->dir);
    }
}

void transplante(Arvore *arvore, No * a, No * b){

    //sem pai
    if(a->pai == NULL){
        arvore->raiz = b;
    }
    //nos vizinhos iguais
    else if(a == a->pai->esq){
        a->pai->esq = b;
    }
    //nos vizinhos diferentes 
    else{
        a->pai->dir = b;
    }
    //se b existir, recebe o pai de a
    if(b != NULL){
        b->pai = a->pai;
    }
}
/*
    troca as sub-arvores a partir do transplante

*/
void deleteAbb(int n, Arvore *arvore){

    No *temp  = buscaAbb(n, arvore->raiz);
    if(temp == NULL){
        printf("Elemento nao encontrado.\n");
        return;
    }

    //no filho a esquerda vazio 
    if(temp->esq == NULL){
        transplante(arvore,temp, temp->dir);
    }
    //no filho a direita vazio
    else if(temp->dir == NULL){
        transplante(arvore, temp, temp->esq);
    }
    else{
        No *x = minimoAbb(temp->dir);
        if(x->valor !=n){
            transplante(arvore,x,x->dir);
            x->dir = temp->dir;
            x->dir->pai = x;
        }
        transplante(arvore,temp,x);
        x->esq = temp->esq;
        x->esq->pai = x;
    }
    free(temp);
}

void printNivelArvore(No *no, int nivel){

    if(no ==NULL) return;
    if(nivel == 1){
        printf("%d ",no->valor);
        return;
    }
    printNivelArvore(no->esq,nivel-1);
    printNivelArvore(no->dir,nivel-1);

}

void imprimeLinhaLinha(No *no)
{
    int alt = alturaAbb(no);
    for(int i=0;i<=alt;i++){
        printNivelArvore(no, i+1);
        printf("\n");
    }
}

void imprimeArvore(No *raiz, int espaco, char *prefixo, int isEsquerda) {
    if (raiz == NULL) return;

    // Ajusta prefixo para exibir a estrutura correta
    printf("%s", prefixo);
    printf("%s── %d\n", isEsquerda ? "├" : "└", raiz->valor);

    // Atualiza o prefixo para os filhos
    char novoPrefixo[100];
    snprintf(novoPrefixo, sizeof(novoPrefixo), "%s%s   ", prefixo, isEsquerda ? "│" : " ");

    if (raiz->dir) imprimeArvore(raiz->dir, espaco + 1, novoPrefixo, 1);
    if (raiz->esq) imprimeArvore(raiz->esq, espaco + 1, novoPrefixo, 0);
}

void imprimeFormatado(Arvore* arv){
    imprimeArvore(arv->raiz,0,"",0);
}

/*
    Ex. 1

*/
void numFolhas(No *aux, int *cont){

    if(!aux) return;
    //caso base 
    if(aux->esq == NULL && aux->dir == NULL){
        (*cont)++;
        return;
    }
    numFolhas(aux->esq,cont);
    numFolhas(aux->dir,cont);
}

/*
    Ex. 2 Calculo do número
    de arestas entre n e a raiz

    -> incremente o caminho de baixo para cima
    Enquanto o no nao for a raiz da arvore: no = no->pai
*/
int profundidadeNo(int n, Arvore *arvore){

    if(!arvore || !arvore->raiz) return -1;

    No *no = buscaAbb(n,arvore->raiz);
    if(!no) return -1;
    int trace = 0;
    No *aux = arvore->raiz;

    while(no != aux){
        no = no->pai;
        trace++;
    }
    return trace;
}
/*
    Ex. 3 Diferenca entre profundidades

*/
int diffProfundidade(int a, int b, Arvore *arvore){

    if(!arvore || !arvore->raiz) return -1;

    //chamar profundidadeNo para cada um
    // if comparando qual e maior e subtraindo o menor 

    int temp1 = profundidadeNo(a,arvore);
    int temp2 = profundidadeNo(b, arvore);
    int result = 0;
    if(temp1>temp2){
        result = temp1 - temp2;
    }
    else{
        result = temp2  - temp1;
    }
    return result;
}

/*
    Ex. 4 Ancestral Comum mais baixo entre dois nos 
    -> recursao
*/
No *ancestralComum(int a, int b, No *no){

    if(no ==NULL) return NULL;

    if(no->valor == a || no->valor == b) return no;

    No *resEsq = ancestralComum(a,b, no->esq);
    No *resDir = ancestralComum(a,b, no->dir);

    //se ambas as chamadas recursivas retornaram um no,
    //significa que o no informado é o ancestral comum
    //Pois dele surgem no->dir e no->esq 
    if(resEsq !=NULL && resDir != NULL) return no;
    
    if(resEsq == NULL){
        return ancestralComum(a,b,no->dir);
    }
    else{
        return ancestralComum(a,b,no->esq);
    }
}

/*
    Ex. 5 Distancia entre dois nos da arvore
    -> soma a distancia ate o anc comum dos dois nos
    -> garante o menor caminho, por conta do anc comum  
*/
int distanciaNos(int a, int b, Arvore *arvore){

    No *anc = ancestralComum(a,b,arvore->raiz);

    if(!anc) return -1;

    int distanciaX = diffProfundidade(a, anc->valor,arvore);
    int distanciaY = diffProfundidade(b,anc->valor,arvore);
    return distanciaX + distanciaY;

}
/*
    Ex. 6 
    -> um simples for gera uma arvore degenarada(semelhante à lista encadeada)
    ->tentativa recursiva O(log N)
*/
//deve receber um vetor ordenado 
//rever
void vetorToABB(int *vet,int inicio, int fim, Arvore *arvore){

    // for(int i=0;i<size;i++){
    //     insereAbb(vet[i],arvore);
    // }
    //caso base : vetor inserido totalmente
    if(inicio>fim) return;

    int meio = (inicio+fim)/2;

    insereAbb(vet[meio],arvore);

    //subvetor a esquerda
    vetorToABB(vet,inicio,meio-1,arvore);
    //subvetor a direita
    vetorToABB(vet,meio+1,fim,arvore);
}

/*
    Ex. 7 Arvore binaria 
*/
int isBinaria(No *aux){

    //caso base
    if(aux == NULL) return 1;
    //caso base
    if(aux->esq == NULL && aux->dir == NULL) return 1;
    //verificacao da condicao binaria
    if(aux->esq != NULL && aux->dir != NULL){
        if(aux->valor == (aux->esq->valor + aux->dir->valor)) {
            //sub-arvores a esquerda e direita 
            return isBinaria(aux->dir) && isBinaria(aux->esq);
        }
    }
    return 0;
}

void insereArvoreBinaria(int n, Arvore* Arvore){
}

/*
    Ex. 8 Somar todos os valores de uma Arvore
    -> semelhante a busca em Largura
    -> Utiliza uma fila auxiliar
    -> soma os valores da desenfileração dessa fila
    ->ate a fila ficar vazia(folhas da arvore alcançadas)
*/
int somaValoresAb(Arvore *arvore){

    int cont = 0;
    Fila * fila =criaFila();
    No *aux = arvore->raiz;
    if(!aux) return 0;
    enfileraFila(aux, fila);
    while(!filaVazia(fila)){
        aux = desenfileraFila(fila);
        cont += aux->valor;
        //sub-arvores
        if(aux->esq != NULL) enfileraFila(aux->esq,fila);
        if(aux->dir != NULL) enfileraFila(aux->dir,fila);
    }
    free(fila);
    return cont;
}

int main()
{
    Arvore * arvore;
    arvore->raiz = NULL;

    insereAbb(12, arvore);
    insereAbb(5, arvore);
    insereAbb(2, arvore);
    insereAbb(9, arvore);
    insereAbb(18,arvore);
    insereAbb(15, arvore);
    insereAbb(19, arvore);
    insereAbb(13, arvore);
    insereAbb(17, arvore);

    percursoEmOrdem(arvore->raiz);
    //deleteAbb(12,arvore);
    printf("\n");
    percursoEmOrdem(arvore->raiz);
    printf("\n");
    printNivelArvore(arvore->raiz,2);
    printf("\n");
    printf("\n");
    imprimeFormatado(arvore);
    printf("\n");
    int cont = 0;
    numFolhas(arvore->raiz,&cont);
    printf("Quantidade de folhas: %d\n", cont);
    printf("Profundidade do no 13: %d\n",profundidadeNo(13,arvore));
    printf("Diferenca de profundidade entre 18 e 13: %d\n",diffProfundidade(18,13,arvore));
    printf("Diferenca de profundidade entre 12 e 13: %d\n",diffProfundidade(12,13,arvore));
    No *anc = ancestralComum(13,19,arvore->raiz);
    printf("Ancestral comum entre 13 e 19: %d\n",anc->valor);
    printf("Distancia relativa entre 2 e 13: %d\n",distanciaNos(2,13,arvore));

    int vet[] = {1,2,3,4,5,6,7,8,9};
    int n = sizeof(vet)/sizeof(vet[0]);
    printf("%d\n", n);
    Arvore *abb = (Arvore*)malloc(sizeof(Arvore));
    abb->raiz = NULL;
    vetorToABB(vet,0,n,arvore);
    printf("\n");
    percursoEmOrdem(abb->raiz);
    imprimeFormatado(abb);
    imprimeLinhaLinha(abb->raiz);

    // Arvore *bin = (Arvore*)malloc(sizeof(Arvore));
    // bin->raiz = NULL;
    // insereArvoreBinaria(10,bin);
    // insereArvoreBinaria(4,bin);
    // insereArvoreBinaria(6,bin);
    // insereArvoreBinaria(3,bin);
    // insereArvoreBinaria(3,bin);
    // insereArvoreBinaria(2,bin);
    // insereArvoreBinaria(2,bin);

    Arvore * arvore2 = malloc(sizeof(Arvore));
    arvore2->raiz = NULL;

    insereAbb(12, arvore2);
    insereAbb(5, arvore2);
    insereAbb(2, arvore2);
    insereAbb(9, arvore2);
    insereAbb(18,arvore2);
    insereAbb(15, arvore2);
    insereAbb(19, arvore2);
    insereAbb(13, arvore2);
    insereAbb(17, arvore2);

    printf("Soma dos valores da arvore: %d\n", somaValoresAb(arvore2));

    return 0;
}
