#include <stdio.h>

int Max(int v[], int n, int tamanho) {
    int x = v[0];
    for (int j=1; j<tamanho; j++)
        if (x < v[j]) 
            x = v[j];
    if (n > x)
        return n;
    else
        return x;
}

int main() {
    int v[6] = {13,5,29,112,2,1100};
    int tamanho = sizeof(v)/sizeof(v[0]); // calcula a quantidade de elementos do vetor
    int resultado = Max(v, 225, tamanho);
    printf("O resultado eh %d", resultado);
}