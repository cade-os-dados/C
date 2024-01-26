#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "include/whitespaces.h"

// 6.1.1
// Suponha que, diferentemente da convenção adotada no texto, a parte do vetor
// ocupada pela pilha é p[0..t]. Escreva o comando que remove um elemento da pilha.
// Escreva o comando que insere um objeto na pilha.

int insere(int p[], int y, int t, int n){
    if (t == n) {
        printf("A pilha esta cheia\n");
        return t;
    } else {
        p[t++] = y;
        return t;
    }
}

int pop(int p[], int *t){
    if (*t == 0) {
        printf("A pilha esta vazia\n");
    }
    else {
        *t = *t-1;
        return p[*t];
    }
}

void print_vetor(int v[], int len){
    printf("< ");
    for (int i = 0; i < len; i++){
        printf("%d ", v[i]);
    }
    printf(">\n");
}

// 6.1.2 INVERSÃO DE PALAVRAS
// Escreva uma função que inverta a ordem das letras de cada palavra de uma sentença,
// preservando a ordem das palavras. Suponha que as palavras da sentença são separadas
// por espaços. A aplicação da operação à sentença AMU MEGASNEM ATERCES, por exemplo, 
// deve produzir UMA MENSAGEM SECRETA.

// obs: não utilizei o conceito de pilha por ser mais vantajoso
// nesse caso fazer swap dos caracteres, mas poderia criar um vetor
// para cada palavra e dar pop no vetor, pegar o valor do pop
// e jogar em outra vetor que estaria ordenado de maneira invertida
// quando a pilha ficasse vazia

celula *inverter(char *mensagem){
    celula *primaria = tokenize(mensagem); // celula com cabeca
    celula *copia = primaria;
    while (copia -> seg != NULL) {
        copia = copia -> seg;
        char *valor = copia -> conteudo;
        // troca as posições i com i-1, até a metade do vetor
        int tamanho = strLen(valor);
        int limite = tamanho / 2;
        for (int i = 1; i <= limite; i++){
            char swap = valor[i-1]; // cache
            valor[i-1] = valor[tamanho-i];
            valor[tamanho-i] = swap;
        }
    }
    return primaria;
}

// 6.1.3 PERMUTAÇÕES PRODUZIDAS PELO DESEMPILHAR
// Suponha que os números inteiros 1, 2, 3, 4 são colocados
// nesta ordem, numa pilha inicialmente vazia. Depois de cada
// operação de empilhar, você pode retirar zero ou mais elementos
// da pilha. Cada número retido da pilha é impresso numa folha
// de papel. Por exemplo, a sequência de operações E, E, D, E, D, D, E, D
// onde E significa "empilhar o próximo número da sequência" e D significa
// "desempilhar", produz a impressão da sequência 2, 3, 1, 4. Quais das 24
// permutações de 1, 2, 3, 4 podem ser obtidas dessa maneira?

// podemos criar um código força bruta...
int permutacoes() {
    int total = 0;
    // para cada combinação de E e D
    // verificar se a combinação gerada já foi gerada anteriormente
    // se não foi gerada, então soma 1 no valor total
    
    // wip algoritmo de permutacao
    int v[3] = {0,0,0};
    int possibilidades = pow(2, 8);
    int j = 0;
    print_vetor(v, 3);
    while (j < 2) {
        for (int i = j; i < 3; i++){
            v[i] = v[i] ^ 1; // bit flip
            print_vetor(v, 3);
        }
        printf("OK\n");
        j++;
    }
    return total;
}

int main(){
    int n = 12; int p[n]; int t = 0;
    pop(p, &t);
    assert(t == 0);
    for (int i=0;i<13;i++) {
        printf("Inserindo: %d. t = %d\n", i % 5, t);
        t = insere(p, i % 5, t, n);
    }
    print_vetor(p, t);
    assert(t == 12);

    int ultimo_valor = pop(p, &t);
    printf("Ultimo valor: %d\n", ultimo_valor);
    assert(t == 11);

    char *m = strdup("AMU MEGASNEM ATERCES");
    celula *mensagem_invertida = inverter(m);
    print_celula(mensagem_invertida);

    int resultado = permutacoes();
}