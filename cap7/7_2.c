#include <stdio.h>
#include <assert.h>

// Busca sequencial
int BuscaSequencial(int x, int n, int v[]){
    int j = 0;
    while (j < n && v[j] < x) ++j;
    return j;
}

// 7.2.1 Critique a seguinte formulação de problema de busca:
// dado x e um vetor crescente v[0..n-1], encontrar um índice
// j tal que v[j-1] <= x <= v[j]. Critique a formulação
// baseada em "v[j-1] < x < v[j]"

// R: Neste caso, teríamos que checar tanto o índice atual
// quando o índice anterior, portanto estaríamos multiplicando
// o número de operações por 2, embora o consumo de tempo
// da função continuaria sendo proporcional a n

// 7.2.2 INVARIANTE. Na função BuscaSequencial, qual o invariante
// do processo iterativo controlado pelo while

// R: x > v[j-1] !E (-inf, v[j]) 
// !E => pertence

// 7.2.3 Critique a seguinte versão da função BuscaSequencial
int CriticarBuscaSequencial(int x, int n, int v[]){
    int j = 0;
    while (v[j] < x && j < n) j++;
    return j;
}

// R: na última iteração caso j = n, estará acessando
// um elemento fora do vetor. O que pode ser prevenido
// alterando a ordem das condicionais do while

// 7.2.4 VERSÃO RECURSIVA. Escreva uma versão recursiva
// da função BuscaSequencial

// SR -> Sequenical Recursiva
int BuscaSR(int x, int n, int v[], int j){
    if ((n == 0) || (j == n) || (v[j] >= x)) return j;
    else return BuscaSR(x, n, v, j+1);
}

int main(){
    int x = 5;
    int v[6] = {1,2,3,4,5,6};
    int n = 6;
    
    int j1 = BuscaSequencial(x, n, v);
    int j = 0;
    j = BuscaSR(x, n, v, j);
    assert(j1 == j);
}