#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

struct cel {
    int conteudo;
    struct cel *seg;
};

typedef struct cel celula;

// A função insere uma nova célula em uma lista encadeada 
// entre a célula p e a seguinte (supõe-se que p != NULL)
// A nova célula terá conteúdo y

void insere (int y, celula *p) {
    celula *nova;
    nova = malloc(sizeof(celula));
    nova -> conteudo = y;
    nova -> seg = p -> seg;
    p -> seg = nova;
}

// 4.5.1 Por que a seguinte versão de Insere não funciona?
// R: pelo teste aqui funciona corretamente...
void insere2(int y, celula *p){
    celula nova;
    nova.conteudo = y;
    nova.seg = p -> seg; 
    p->seg = &nova;
}

// 4.5.2 Escreva uma função que insira uma nova célula
// entre a célula cujo endereço é p e a anterior
celula *find_previous(celula *p, celula *primaria){
    celula *anterior = malloc(sizeof(celula));
    anterior -> conteudo = primaria -> conteudo;
    anterior -> seg = primaria -> seg;
    while (anterior -> seg != NULL && anterior -> seg != &*p)
        anterior = anterior -> seg;
    return anterior;
}

void insert_between(int y, celula *p, celula *primaria){
    celula *anterior = find_previous(p, primaria);
    celula *atual = malloc(sizeof(celula));
    atual -> conteudo = y;
    anterior -> seg = atual;
    atual -> seg = p -> seg;
}

int main() {
    celula *p = malloc(sizeof(celula));
    celula *p2 = malloc(sizeof(celula));
    p -> conteudo = 10;
    p -> seg = p2;
    p2 -> conteudo = 5;
    p2 -> seg = NULL;
    insere2(20, p);
    assert (p-> conteudo == 10);
    assert (p -> seg -> conteudo == 20);
    assert (p -> seg -> seg -> conteudo == 5);
    for (celula *loop = p; loop != NULL; loop = loop->seg) {
        printf("%d ", loop->conteudo);
    }

    // wip
    // insert_between(50, p->seg->seg, p);
    // for (celula *loop = p; loop != NULL; loop = loop->seg) {
    //     printf("%d ", loop->conteudo);
    // }
}