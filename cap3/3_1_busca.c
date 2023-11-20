#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 3.1.1 Qual a invariante do processo iterativo de busca?

int Busca (int x, int v[], int n){
    int k;
    k = n - 1;
    /* (invariante) k > 0 se x pertencer a v[0..n-1] */
    while(k >= 0 && v[k] != x)
        k -= 1;
    return k;
}

// 3.1.2 Analise a seguinte variante do código da função de busca

// Análise: esta função verifica para cada k se o valor do vetor
// no índice k é igual a x. Sendo que k percorre o intervalo [n-1..0]
// se não encontrar um valor no vetor igual a x retorna -1
int Busca2 (int x, int v[], int n){
    int k;
    for (k = n-1; k>= 0; k--){
        if (v[k] == x) return k;
    }
    return -1;
}

// 3.1.3 Critique a seguinte função de Busca:

// esta função executa uma condição desnecessária
int Busca3 (int x, int v[], int n){
    int k = 0;
    while (k < n && v[k] != x) k+=1;
    // já foi verificado que v[k] == x acima
    if (v[k] == x) return k;
    else return -1;
}

// 3.1.4 Critique a seguinte função de Busca

// A função está incorreta porque não da break quando encontra o valor
// assim sera n-1 se o último valor for x se não será -1
int Busca4 (int x, int v[], int n){
    int sol;
    for (int k=0; k<n;k++){
        if (v[k] == x) sol = k;
        else sol = -1;
    }
    return sol;
}

// 3.1.5 Tome uma decisão de projeto diferente da adotada no texto:
// se x não estiver em v[0..n-1], a função deve devolver n.
// Escreva a versão correspondente da função Busca. Para evitar o grande
// número de comparações de k com n, coloque uma "sentinela" em v[n].
int Busca5(int x, int v[], int n) {
    int i = 0;
    // Adiciona uma sentinela no final do array
    v[n] = x; 
    while (v[i] != x) {
        i++;
    }
    if (i < n) return i; // Retorna a posição de x se encontrado
    else return n; // Retorna n se x não estiver presente
}

// 3.1.6 Considere o problema de determinar o valor de um elemento máximo
// de um vetor v[0..n-1]. A seguinte função resolve o problema?
// R: sim, resolve...
int maximo (int n, int v[]){
    int j, x;
    x = v[0];
    for (j=1;j<n;j++){
        if (x < v[j]) x = v[j];
    }
    return x;
}

int main(){
    int n = 100000000;
    int numero_descobrir = 120000;
    int *vetor = malloc(n*sizeof(int));
    srand(time(NULL));
    for (int i=0;i<n;i++){
        vetor[i] = rand();
    }
     
    double startTime = (double)clock()/CLOCKS_PER_SEC;
    int indice4 = Busca(numero_descobrir, vetor, n);
    double endTime = (double)clock()/CLOCKS_PER_SEC;
    double time_taken = endTime - startTime; // calculate the elapsed time
    
    printf("Indice da busca: %d \nO tempo de execucao da funcao original foi: %f s\n", indice4, time_taken);

    double startTime1 = (double)clock()/CLOCKS_PER_SEC;
    int indice5 = Busca5(numero_descobrir, vetor, n);
    double endTime1 = (double)clock()/CLOCKS_PER_SEC;
    double time_taken1 = endTime1 - startTime1; // calculate the elapsed time
    
    printf("Indice da busca: %d \nO tempo de execucao da funcao otimizada foi: %f s\n", indice5, time_taken1);
}