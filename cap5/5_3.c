// implementação circular
// quando não sabemos no inicio do programa qual será o tamanho da lista
# include<stdlib.h>
# include<stdio.h>

typedef struct cel {
    int valor;
    struct cel *seg;
} celula;

int Remove (celula **es, celula **et){
    celula *p;
    int x;
    p = *es;
    x = p->valor;
    *es = p -> seg;
    free (p);
    if (*es == NULL) *et = NULL;
    return x;
}

void Insere (int y, celula **es, celula **et){
    celula *nova;
    nova = malloc(sizeof(celula));
    nova -> valor = y;
    nova -> seg = NULL;
    if (*et == NULL) *et = *es = nova;
    else {
        (*et) -> seg = nova;
        *et = nova;
    }
}

void printFila(celula *es, celula *et){
    celula *loop = es;
    printf("< ");
    while (loop != et->seg){
        printf("%d ", loop->valor);
        loop = loop -> seg;
    }
    printf(">");
}

int main() {
    celula *s, *t;
    s = t = NULL;
    Insere(5, &s, &t);
    Insere(15, &s, &t);
    Insere(10, &s, &t);
   
    printFila(s, t);
    // printf("%d\n", s->valor);
    // printf("%d\n", s->seg->valor);
}