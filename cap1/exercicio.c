#include <stdio.h>
#include <math.h>

// Exercícios 1.1
// Neste exercício basta comentar o que a função faz

// esta funcao soma os valores de um vetor,
// sendo necessário indicar no parâmetro n o tamanho do vetor
int soma(int n, int v[]) {
    int i, x = 0;
    for (i = 0; i < n; i++)
        x += v[i];
    return x;
}

// conta quantos passos são necessários para encontrar x
// obs: é necessário inserir o tamanho do vetor no argumento n
int onde (int x, int v[], int n) {
    int j = 0;
    while (j < n && v[j] != x)
        j += 1;
    return j;
}

// calcular log base 2 de n para um vetor
void log_2 (int n, double v[]) {
    printf("--------------------------\n|");
    for (int i=0; i < n; i++)
        printf("%.2f|", v[i]);
    printf("\n--------------------------\n|");
    for (int i=0; i < n; i++)
        v[i] = log2(v[i]);
    for (int i=0; i < n; i++)
        printf("%.2f|", v[i]);
    printf("\n--------------------------\n");
}

int main() {
    int v[] = {1,2,3,4,5};
    int tamanho = sizeof(v) / sizeof(v[0]);
    int resultado = soma(tamanho, v );
    int contagem = onde(2, v, tamanho);
    double v2[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    log_2(tamanho, v2);
    printf(" Resultado: %d \n Contagem: %d\n", resultado, contagem);
}