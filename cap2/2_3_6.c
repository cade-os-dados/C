#include <stdio.h>
#include <time.h>

int fibo_recursiva(int n){
    if (n == 0 || n == 1) 
        return n;
    else 
        return fibo_recursiva(n - 1) + fibo_recursiva(n - 2);
}

int fibo_iterativa(int n){
    if (n == 0 || n == 1) 
        return n;
    else{
        int result;
        int fibo_1 = 0;
        int fibo_2 = 1;
        for (int i=1;i<n;i++){
           result = fibo_1 + fibo_2;
           fibo_1 = fibo_2;
           fibo_2 = result; 
        }
        return result;
    }
}

int main(){
    int ITERACOES = 43;
    
    double startTime = (double)clock()/CLOCKS_PER_SEC;
    int fibonacci_recur = fibo_recursiva(ITERACOES);
    double endTime = (double)clock()/CLOCKS_PER_SEC;
    double time_taken1 = endTime - startTime; // calculate the elapsed time
    
    double startTime2 = (double)clock()/CLOCKS_PER_SEC;
    int fibonacci_iter = fibo_iterativa(ITERACOES);
    double endTime2 = (double)clock()/CLOCKS_PER_SEC;
    double time_taken2 = endTime2 - startTime2; // calculate the elapsed time
    
    printf("O resultado da funcao recursiva eh: %d \nO resultado da funcao iterativa eh: %f\n", fibonacci_recur, time_taken1);
    printf("O resultado da funcao iterativa eh: %d \nO resultado da funcao iterativa eh: %f\n", fibonacci_iter, time_taken2);
}

// o livro pergunta qual é mais eficiente
// como vemos no benchmark, a versão iterativa é mais eficiente
// devido a armazenar os cálculos anteriores em cache
// enquanto na versão recursiva não é possível aplicar cache