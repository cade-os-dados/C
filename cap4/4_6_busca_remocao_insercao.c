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

void print_celulas(celula *primaria){
    printf("[ ");
    celula *loop = primaria;
    while (loop != NULL) {
        printf("%d ", loop -> conteudo);
        loop = loop -> seg;
    }
    printf("]");
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
celula *buscaInsereSemCabeca(int y, int x, celula *primaria){
    celula *nova;
    nova = malloc(sizeof(celula));
    nova -> conteudo = y;
    if (primaria -> conteudo == x){
        nova -> seg = primaria;
        return nova;
    } else {
        celula *anterior = primaria;
        // busca
        while (anterior -> seg != NULL && anterior -> seg -> conteudo != x){
            anterior = anterior -> seg;
        }
        nova -> seg = anterior -> seg;
        anterior -> seg = nova;
        return primaria;
    }
}

// 4.6.3 Escreva uma função para remover de uma lista encadeada todos 
// os elementos que contêm x. Faça uma versão iterativa e uma versão recursiva
celula *busca(int x, celula *primaria){
    celula *anterior = primaria;
    while (anterior -> seg != NULL && anterior -> seg -> conteudo != x){
        anterior = anterior -> seg;
    }
    return anterior;
}

// iterativa
void buscaRemoveTodas(int x, celula *primaria){
    celula *anterior = busca(x, primaria);
    while (anterior -> seg != NULL && anterior -> seg -> conteudo == x){
        celula *remover = anterior -> seg;
        anterior -> seg = remover -> seg;
        free (remover);
        anterior = busca(x, primaria);
    }
}

// recursiva
void buscaRemoveTodasR(int x, celula *primaria){
    celula *anterior = busca(x, primaria);
    if (anterior -> seg != NULL){
        if (anterior -> seg -> conteudo == x) {
            celula *remover = anterior -> seg;
            anterior -> seg = remover -> seg;
            free (remover);
        }
        buscaRemoveTodasR(x, primaria);
    }
}

// 4.6.4 Escreva uma função que remova de uma lista
// encadeada uma célula cujo conteúdo tem valor mínimo
// Faça uma versão iterativa e uma recursiva

// iterativa
celula *minimo(celula *primaria){
    celula *anterior = primaria, *loop = primaria -> seg;
    while (loop -> seg != NULL){
        if (loop -> seg -> conteudo < anterior -> seg -> conteudo)
            anterior = loop;
        loop = loop -> seg;
    }
    return anterior;
}

// recursiva
celula *minimoR(celula *menor, celula *primaria){
    celula *menor_anterior;
    if (primaria -> seg != NULL){
        menor_anterior = minimoR(menor, primaria -> seg);
        if (menor_anterior -> seg -> conteudo < menor -> seg -> conteudo)
            menor = menor_anterior;
    }
    return menor;
}

void removeMinimo(celula *primaria){
    celula *anterior = minimo(primaria);
    celula *remover = anterior -> seg;
    anterior -> seg = remover -> seg;
    free (remover);
}

int main() {
    // criando lista encadeada
    celula *p4 = nova(15, NULL);
    celula *p3 = nova(12, p4);
    celula *p2 = nova(13, p3);
    celula *p = nova(11, p2);

    // testando remocao
    buscaRemoveSemCabeca(11, p);
    assert(p -> conteudo == 13);
    buscaRemoveSemCabeca(15, p);
    assert(p -> seg -> conteudo == 12);
    assert(p -> seg -> seg == 0); // 0 <=> NULL

    // testando insercao
    p = buscaInsereSemCabeca(17, 13, p);
    assert(p -> conteudo == 17);
    assert(p -> seg -> conteudo == 13);
    p = buscaInsereSemCabeca(13, 13, p);
    p = buscaInsereSemCabeca(15, 13, p);

    // remocao completa iterativa e recursiva
    buscaRemoveTodas(13, p);
    celula *find = busca(13, p);
    assert(find -> seg == 0); // NULL
    buscaRemoveTodasR(15, p);
    find = busca(15, p);
    assert(find -> seg == 0); // NULL

    // encontrar celula anterior à celula
    // cujo valor é valor minimo
    find = minimo(p);
    assert(find -> seg -> conteudo == 12);
    find = minimoR(p, p);
    assert(find -> seg -> conteudo == 12);

    // remocao
    removeMinimo(p);
    assert(p -> seg == 0);
    assert(p -> conteudo == 17);

    printf("OK");
}