#include <stdio.h>
#include <stdlib.h>

// 4.8.1 Descrever em C
// uma lista duplamente encadeada
struct cel {
    int conteudo;
    struct cel *seg;
    struct cel *ant;
};

typedef struct cel celula;

// 4.8.2 Remover de uma lista duplamente encadeada
// a célula cujo endereço é p
// que dados essa funcao recebe?
// que coisa devolve?
void remover_celula(celula *p){
    // vamos considerar uma lista com cabeçalho
    celula *anterior = p -> ant;
    if (p -> seg != NULL) {
        anterior -> seg = p -> seg;
        p -> ant = anterior;
    } else {
        anterior -> seg = NULL;
    }
    free(p);
}

// 4.8.3 Suponha uma lista duplamente encadeada
// Escreva uma função que insira uma nova célula com conteúdo y
// logo após a célula cujo endereço é p. Que dados sua função recebe?
// Que coisa devolve?
void inserir_celula(celula *p, int valor){
    
    celula *next = p -> seg;

    // criando celula nova a realocando
    celula *nova = malloc(sizeof(celula));
    nova -> conteudo = valor;
    nova -> seg = next;
    nova -> ant = p;

    // ajustando ponteiros
    p -> seg = nova;
    next -> ant = nova;
}

// 4.8.4 Problema de Josephus. Imagine n pessoas dispostas
// em círculo. Suponha que as pessoas estão numeradas de 1 a n
// no sentido horário. Começando com a pessoa de número 1, percorra
// o círculo no sentido horário e elimine cada m-ésima pessoa enquanto
// o círculo tiver duas ou mais pessoas. (Veja Josephus problem na Wikipédia[21]).
// Qual o número de sobrevivente. Escreva uma função que resolva o problema.

// funcao que irá ajudar na josephus
int len(celula *primaria){
    celula *iterativa = primaria;
    int contagem = 1;
    while (iterativa -> seg != primaria){
        iterativa = iterativa -> seg;
        contagem++;
    }
    return contagem;
}

celula *busca(celula *primaria, int passos){
    celula *resultado = primaria;
    while (passos > 0) {
        resultado = resultado -> seg;
        passos--;
    }
    return resultado;
}

celula *josephus(celula *primaria, int m){
    int n = len(primaria);
    celula *dinamica = malloc(sizeof(celula));
    celula *remover = busca(primaria, m);
    while (n > 1) {
        dinamica = remover -> seg;
        dinamica -> ant = remover -> ant;
        printf("Sera removido: %d\n", remover -> conteudo);
        remover_celula(remover);
        remover = busca(dinamica, m);
        n--;
    }
    return dinamica;
}

// funcoes auxiliares
void print_celulas(celula *primaria){
    printf("[ ");
    celula *loop = primaria;
    while (loop != NULL) {
        printf("%d ", loop -> conteudo);
        loop = loop -> seg;
    }
    printf("]\n");
}

celula *from_vector_to_circular(int v[], int n){
    int k = 1;
    celula *primaria = malloc(sizeof(celula));
    primaria -> conteudo = v[0];
    celula *dinamica = primaria;
    while (k < n){
        celula *nova = malloc(sizeof(celula));
        nova -> conteudo = v[k];
        nova -> ant = dinamica;
        dinamica -> seg = nova;
        dinamica = nova;
        k++;
    }
    dinamica -> seg = primaria;
    primaria -> ant = dinamica;
    return primaria;
}

int main() {
    celula *primaria = malloc(sizeof(celula));
    celula *secundaria = malloc(sizeof(celula));
    celula *terciaria = malloc(sizeof(celula));
    primaria -> seg = secundaria;
    primaria -> ant = NULL;
    secundaria -> seg = terciaria;
    secundaria -> ant = primaria;
    terciaria -> seg = NULL;
    terciaria -> ant = secundaria;
    primaria -> conteudo = 1;
    secundaria -> conteudo = 2;
    terciaria -> conteudo = 3;
    print_celulas(primaria);
    remover_celula(secundaria);
    print_celulas(primaria);

    inserir_celula(primaria, 2);
    print_celulas(primaria);
    terciaria -> seg = primaria;
    printf("A celula tem %d elementos\n", len(primaria));

    int vetor[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    celula *lista_josephus = from_vector_to_circular(vetor, 12);
    celula *resultado = josephus(lista_josephus, 1);
    printf("O sobrevivente foi %d", resultado -> conteudo);
}