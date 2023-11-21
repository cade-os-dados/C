#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

struct cel {
    int conteudo;
    struct cel *seg;
};

typedef struct cel celula;

celula *nova (int init_conteudo, celula *next) {
    celula *new = malloc(sizeof(celula));
    new -> conteudo = init_conteudo;
    new -> seg = next;
    return new;
}

/* Esta função recebe uma lista encadeada primaria com cabeça
e remove da lista a primeira celula que contiver x, se tal
celula existir*/
void buscaRemove(int x, celula *primaria){
    celula *p, *q;
    p = primaria;
    q = primaria -> seg;
    while (q != NULL && q -> conteudo != x){
        p = q;
        q = q -> seg;
    }
    if (q != NULL) {
        p -> seg = q -> seg;
        free (q);
    }
}

/* Recebe uma lista encadeada primaria com cabeça e insere 
uma nova celula na lista imediatamente antes da primeria
que contiver x. Se nenhuma celula contiver x, a nova celula
sera inserida no fim da lista. A nova celula tera conteudo y*/
void buscaInsere(int y, int x, celula *primaria){
    celula *p, *q, *nova;
    nova = malloc(sizeof(celula));
    nova -> conteudo = y;
    p = primaria;
    q = primaria -> seg;
    while (q != NULL && q -> conteudo != x){
        p = q;
        q = q -> seg;
    }
    nova -> seg = q;
    p -> seg = nova;
}

// 4.6.1 Escreva uma versao da funcao buscaRemove
// para listas encadeadas sem cabeca
void buscaRemoveSemCabeca(int x, celula *primaria){
    celula *next, *atual;
    atual = primaria;
    next = primaria -> seg;
    while (next -> seg != NULL && atual -> conteudo != x){
        atual = next;
        next = next -> seg;
    }
    if (atual -> conteudo == x) {
        atual -> conteudo = next -> conteudo;
        atual -> seg = next -> seg;
        free (next);
    }
    // caso seja o ultimo elemento da lista encadeada
    else if (next -> conteudo == x) {
        atual -> seg = NULL;
        free (next);
    }
}

// 4.6.2 Escreva uma versão da função buscaInsere para 
// listas encadeadas sem cabeça 
buscaInsereSemCabeca(int y, int x, celula *primaria){
    // wip
}

int main() {
    celula *p4 = nova(15, NULL);
    celula *p3 = nova(12, p4);
    celula *p2 = nova(13, p3);
    celula *p = nova(11, p2);
    buscaRemoveSemCabeca(11, p);
    assert(p -> conteudo == 13);
    buscaRemoveSemCabeca(15, p);
    assert(p -> seg -> conteudo == 12);
    assert(p -> seg -> seg == 0); // 0 <=> NULL
    printf("OK");
}