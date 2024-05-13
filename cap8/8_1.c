#include <assert.h>
#include <stdio.h>

/* Exercícios

* 8.1.1 Escreva uma função que verifique se
* um dado vetor v[0..n-1] é crescente
*/

// R:
int crescente(int v[], int n){
    for (int i = 0; i < n - 1; i++){
        if (v[i] > v[i+1]) 
            return 0;
    }
    return 1;
}

int main(void) {
    int vetor[5] = {1,2,3,4,5};
    int vetor2[5] = {1,2,3,6,5};
    int vetor3[5] = {1,3,2,4,5};

    assert(crescente(vetor, 5) == 1);
    assert(crescente(vetor2, 5) == 0);
    assert(crescente(vetor3, 5) == 0);

    printf("OK");
}
