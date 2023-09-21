#include <stdio.h>
#include <assert.h>

int soma(int v[], int n){
    if (n == 1) {
        if (v[0] > 0)
            return v[0];
        else
            return 0;
    }
    else if (n > 1){
        if (v[0] > 0){
            int result = v[0] + soma(v+1,n-1);
            return result;
        }
        else
            return soma(v+1,n-1);
    }
    else {
        return 0;
    }
}

int main() {
    int v[8] = {1,2,3,4,5,6,-5,0};
    int tamanho = 8;
    int soma_vetor = soma(v, tamanho);
    printf("O resultado eh: %d\n", soma_vetor);

    int v2[6] = {1,2,3,4,5,6};
    int tamanho2 = 6;
    int soma_vetor2 = soma(v2, tamanho2);
    assert(soma_vetor == soma_vetor2);
}