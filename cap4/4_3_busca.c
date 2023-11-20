#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

struct cel {
    int conteudo;
    struct cel *seg;
};

typedef struct cel celula;

celula *busca (int x, celula *primaria) {
    celula *p;
    p = primaria->seg;
    while (p != NULL && p->conteudo != x){
        p = p->seg;
    }
    return p;
}

celula *buscaR (int x, celula *primaria){
    if (primaria->seg == NULL)
        return NULL;
    if (primaria -> seg -> conteudo == x)
        return primaria->seg;
    return buscaR(x, primaria->seg);
}

// 4.3.1 Que acontece se trocarmos "while (p != NULL && p-> conteudo != x)"
// por "while (p->conteudo != x && p != NULL)" na funcao Busca?
// ocorrerá uma exceção caso a lista encadeada tenha apenas uma célula
// pois quando se verifica p != NULL primeiramente, se p for NULL então
// devido ao short circuit evaluation, o programa nem irá verificar
// a condição -> conteudo != x

// 4.3.2 Critique a seguinte variante da função Busca
// R: a função pula o loop pois instancia achou = 0
// e só roda o loop se achou != 0
celula *busca2 (int x, celula *primaria){
    int achou = 0;
    celula *p;
    p = primaria -> seg;
    while (p != NULL && achou != 0){
        if (p->conteudo == x) achou = 1; 
        p = p->seg;
    }
    if (achou) return p;
    else return NULL;
}

// 4.3.3 Escreva uma versão da função Busca para listas sem cabeça
celula *busca_sem_cabeca(int x, celula *primaria){
    celula *p = primaria;
    while (p != NULL && p->conteudo != x){
        p = p->seg;
    }
    return p;
}

// 4.3.4 Mínimo. Escreva uma função que encontra uma célula
// de conteúdo mínimo. Faça duas versões: uma iterativa
// e uma recursiva
celula *minimo (celula *primaria){
    // sem cabeça
    celula *p = primaria;
    int menor = p -> conteudo;
    while (p -> seg != NULL) {
        p = p -> seg;
        if (p -> conteudo < menor)
            menor = p -> conteudo;
    }
    return p;
}

celula *minimoR (celula *menor, celula *atual){
    if (atual -> conteudo < menor -> conteudo)
        menor = atual;
    if (atual -> seg != NULL) {
        atual = atual -> seg;
        return minimoR(menor, atual);
    } else {
        return menor;
    }
}

// 4.3.5 Lista Crescente Uma lista é crescente se o conteúdo
// de cada célula não é maior que o conteúdo da célula seguinte
// escreva uma funcao que faça uma busca em uma lista crescente
// Faça versões para listas com e sem cabeça. Faça uma versão
// recursiva e outra iterativa
celula *busca_crescente(int x, celula *primaria, int cabeca){
    celula *p;
    if (cabeca) p = primaria -> seg;
    else p = primaria;
    while (p -> seg != NULL && p -> conteudo < x)
        p = p -> seg;
    return p;
}

celula *buscaCrescenteR(int x, celula *primaria, int cabeca){
    celula *p;
    if (cabeca) p = primaria -> seg;
    else p = primaria;
    if (p -> seg != NULL && p -> conteudo < x)
        p = buscaCrescenteR(x, p -> seg, 0);
    return p;
}

int main() {
    celula *p = malloc(sizeof(celula));
    celula *p2 = malloc(sizeof(celula));
    celula *p3 = malloc(sizeof(celula));
    p -> conteudo = 4;
    p2 -> conteudo = 15;
    p3 -> conteudo = 2;
    p -> seg = p2;
    p2 -> seg = p3;
    p3 -> seg = NULL;

    int valor = 15;
    celula *resultado = busca_sem_cabeca(valor, p);
    assert(resultado == p2);

    celula *menor = minimo(p);
    assert(menor == p3);

    celula *menorR = minimoR(p, p);
    assert(menorR == p3);

    celula *c = malloc(sizeof(celula));
    celula *c1 = malloc(sizeof(celula));
    celula *c2 = malloc(sizeof(celula));
    c -> conteudo = 1;
    c1 -> conteudo = 10;
    c2 -> conteudo = 100;
    c -> seg = c1;
    c1 -> seg = c2;
    c2 -> seg = NULL;
    
    celula *assertion_cel = busca_crescente(99, c, 0);
    celula *assertion_cel2 = buscaCrescenteR(99, c, 0);
    assert(assertion_cel == c2);
    assert(assertion_cel2 == c2);
    printf("Programa executado com sucesso!");
}