#include <stdio.h>

// 3.2.1 Critique a seguinte função. Ela promete decidir se x está em v[0..n-1],
// devolvendo 1 em caso afirmativo e 0 em caso negativo.
// R: ela calcula retroativamente sem necessidade, percorrendo todo o vetor
// ao invés de parar quando encontra o valor
int muitofeio (int x, int v[], int n){
    if (n==0) return 0;
    else {
        int achei;
        achei = muitofeio(x, v, n-1); // ineficiente
        if (achei || x == v[n-1]) return 1;
        else return 0;
    }
}

// 3.2.2 O autor da função abaixo afirma que ela decide se x está no vetor
// v[0..n-1]. Critique o código.

// esta funcao tem comportamento indeterminado se x não estiver em v
// pois não trata o caso de que x não está em v
// por testes emíricos a função fica no loop até que, através
// do comportamento indeterminado, encontre um valor igual a x
// retornando sempre 1
int busc (int x, int v[], int n){
    int valor = v[n-1];
    if (valor == x) return 1;
    else return busc(x, v, n-1);
}

// 3.2.3 Escreva um programa para testar o funcionamento da função BuscaR.
// O seu programa deve gerar um vetor aleatório (veja Apêndice I) para fazer o teste.
// Acrescente ao seu programa uma função que confira a resposta dada por BuscaR.
int BuscaR(int x, int v[], int n) {
    if (n == 0) return -1;
    if (x == v[n-1]) return n-1;
    return BuscaR(x,v,n-1);
}


int main() {
    int v[5] = {1,2,3,4,5};
    int achou = busc(7, v, 5);
    printf("%d", achou);
}