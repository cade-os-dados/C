#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

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

// funcao auxiliar para checar se a busca
// recursiva esta funcionando corretamente
int Busca(int x, int v[], int n) {
    for (int i = n - 1; i >= 0; i--) {
        if (v[i] == x) return i;
    }
    return -1;
}

void teste(int n){
    srand(time(NULL));
    int v[n];
    for (int i=0;i<n;i++){
        v[i] = rand() % 100;
    }
    int aleatorio = rand() % 100;
    int resultado = BuscaR(aleatorio, v, n);
    int resultado_busca_binaria = Busca(aleatorio, v, n);
    if (resultado != resultado_busca_binaria) {
        printf("\nErro: BuscaR(%d, v, %d) = %d, Busca(%d, v, %d) = %d\n", aleatorio, n, resultado, aleatorio, n, resultado_busca_binaria);
    }
    else {
        printf("OK");
    }
}


int main() {
    teste(200);
}