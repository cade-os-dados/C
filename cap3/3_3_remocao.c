#include <stdio.h>

/* Remove o elemento de índice k do vetor v[0..n-1] e
devolve o novo valor de n. A função supõe 0 <= k < n*/
int Remove (int k, int v[], int n){
    int j;
    for (j=k; j < n-1; j++)
        v[j] = v[j+1];
    return n-1;
}

// versao recursiva
int RemoveR (int k, int v[], int n){
    if (k == n-1) return n-1;
    else {
        v[k] = v[k+1];
        return RemoveR(k+1,v,n);
    }
}

// 3.3.1 Critique a seguinte variante da parte central 
// do código da função Remove
// a funcao esta incorreta tendo em vista que substitui
// o elemento pelo posterior de trás para frente
// fazendo com que todos elementos fiquem iguais ao último elemento
int Remove2 (int k, int v[], int n){
    int j;
    for (j = n-2; j >= k; j--) v[j] = v[j+1];
    return n-1;
}

// 3.3.3 Critique a seguinte variante da parte central 
// do código da função Remove
int Remove3 (int k, int v[], int n){
    int j;
    for (j = k; j < n-1; j++) v[j] = v[j+1];
    v[n-1] = 0; // passo desnecessário
    return n-1;
}

// 3.3.4 Discuta a seguinte versão da função RemoveR
int RemoveR2 (int k, int v[], int n){
    // [k..n-1]
    if (k < n-1){
        RemoveR2(k, v, n-1); // [k..n-2] => [k..n-3] => ... => [k..k+1]
        v[n-2] = v[n-1]; // substitui
    }
    return n-1;
}

int main(){
    int v[5] = {1, 2, 12, 5, 24};
    int n = 5;
    printf("Vetor antes: [ ");
    for (int i=0;i<n;i++){
        printf("%d ", v[i]);
    }
    printf("]");
    n = RemoveR2(2, v, n);
    printf("\nVetor depois: [ ");
    for (int i=0;i<n;i++){
        printf("%d ", v[i]);
    }
    printf("]");
}