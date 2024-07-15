#include "permutacao.h"

// Função para inverter a parte à direita do vetor
void reverse(int arr[], int start, int end) {
    while (start < end) {
        swap(arr, start, end);
        start++;
        end--;
    }
}

/* Esta função retorna o menor vetor arranjo lexicograficamente 
* maior que o vetor inserido
* obs: se for o último vetor, retorna 0
* obs2: copilot que gerou esta função */
int nextArrangement(int arr[], int n) {
    int i = n - 2;
    
    /* i = max(k), k E [0, n-2], arr[k] >= arr[k+1]*/
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }
    if (i < 0) { return 0; } // Não há mais arranjos

    int j = n - 1;
    /* j = max(p), p E [0, n-1], arr[p] > arr[i]*/
    while (arr[j] <= arr[i]) {
        j--;
    }
    swap(arr, i, j);
    reverse(arr, i + 1, n - 1);
    return 1; // Próximo arranjo gerado
}
