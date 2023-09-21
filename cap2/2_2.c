#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// retorna o elemento com o maior valor
// de um vetor
int maximo_recursiva(int v[], int n){
    if (n==1){
        return v[0];
    }
    else {
        int x;
        x = maximo_recursiva(v, n-1);
        if (x > v[n-1]) {
            return x;
        }
        else {
            return v[n-1];
        }
    }
}

// 2.2.1 
int maximo_iterativa(int v[], int n){
    int resultado = v[0];
    for (int j=1; j<n; j++){
        if (v[j] > resultado) {
            resultado = v[j];
        }
    }
    return resultado;
}

// 2.2.2 -> criticar a função abaixo
int maximo_r1(int v[], int n) {
    int x;
    if (n == 1) 
        return v[0];
    // este segundo if é desnecessário
    if (n == 2) {
        if (v[0] < v[1]) 
            return v[1];
        else 
            return v[0];
    }
    x = maximo_r1(v, n-1);
    if (x < v[n-1]) 
        return v[n-1];
    else 
        return x;
}

// 2.2.3 -> criticar a função abaixo
int maximo_r2(int v[], int n){
    if (n==1) return v[0];
    // calcula o maximo aqui
    if (maximo_r2(v, n-1) < v[n-1])
        return v[n-1];
    // calcula novamente o maximo aqui em baixo
    else
        return maximo_r2(v, n-1);
}

// 2.2.4 

// se X -> 3
// teremos 2 + 3 * (1) = 5
// se X -> 4
// teremos 5 + 4 * (2) = 13 (esta seria a resposta)
// se X -> 5
// teremos 13 + 5 * (5) = 38
// ...
int X (int n){
    if (n==1 || n==2) 
        return n;
    else 
        return X(n-1) + n * X(n-2);
}

// 2.2.5 -> verificar o que há de errado
// o problema é que cai em uma recursão indefinida
// o que quebra o programa
int XX (int n){
    if (n==0) 
        return 0;
    else 
        return XX(n/3+1) + n;
}

//2.3.1
int maximo2r(int v[], int n){
    int x;
    if (n==1) return v[0];
    x = maximo2r(v+1,n-1); 
    if (x > v[0]) return x;
    return v[0];
}

int main(int argc, char *argv[]) {

    int n = strtol(argv[1], NULL, 10); // tamanho da array definido no argumento do executavel
    int v[n];
    // popular a array com valores randômicos
    for (int i = 0; i < n; i++) {
        v[i] = rand() % 1000;
    }

    // eval recursiva
    double startTime = (double)clock()/CLOCKS_PER_SEC;
    int maximo1;
    for (int iter = 0; iter < n; iter++){
        maximo1 = maximo_recursiva(v, n);
    };
    double endTime = (double)clock()/CLOCKS_PER_SEC;
    double time_taken1 = endTime - startTime; // calculate the elapsed time

    // eval iterativa
    startTime = (double)clock()/CLOCKS_PER_SEC;
    int maximo2;
    for (int iter = 0; iter < n; iter++){
        maximo2 = maximo_iterativa(v,n);
    };
    endTime = (double)clock()/CLOCKS_PER_SEC;
    double time_taken2 = endTime - startTime; 

    // eval recursiva 2
    startTime = (double)clock()/CLOCKS_PER_SEC;
    int maximo3;
    for (int iter = 0; iter < n; iter++){
        maximo3 = maximo2r(v,n);
    };
    endTime = (double)clock()/CLOCKS_PER_SEC;
    double time_taken3 = endTime - startTime; 

    // verifica se o resultado está correto
    printf("O maximo encontrado pela funcao recursiva foi: %d\
    \n O maximo encontrado pela funcao iterativa foi: %d\
    \n O maximo encontrado pela funcao recursiva 2 foi: %d", maximo1, maximo2, maximo3);

    // printa os times
    printf("\nO tempo de execucao da funcao recursiva foi: %f\
    \n O tempo de execucao da funcao iterativa foi: %f\
    \n O tempo de execucao da funcao recursiva (2) foi: %f", time_taken1, time_taken2, time_taken3);
    getchar();
}