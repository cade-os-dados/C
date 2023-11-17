#include <stdio.h>

/* Insere y entre as posições k-1 e k do vetor v[0..n-1]
e devolve o novo valor de n. Supõe que 0 <= k <= n */
int Insere(int k, int y, int v[], int n){
    int j;
    for (j=n;j>k;j--)
        v[j] = v[j-1];
    v[k] = y;
    return n+1;
}

int InsereR(int k, int y, int v[], int n){
    if (k==n) v[n] = y;
    else {
        v[n] = v[n-1];
        InsereR(k, y, v, n-1);
    }
    return n+1;
}

// 3.4.1 Critique a seguinte versão da função InsereR
// o problema é que sempre retornará n = 1
int insereR2(int k, int y, int v[], int n) {
    if (k==n) {
        v[n] = y;
        return n+1;
    } else {
        v[n] = v[n-1];
        return insereR2(k, y, v, n-1);
    }
}

// 3.4.2 Discuta a seguinte variante da função InsereR
int insereR3(int k, int y, int v[], int n){
    if (k==n){
        v[n] = y;
        return n+1; // retorna corretamente n + 1
    } else {
        int z = v[k]; // salva o valor substituido
        v[k]= y;
        return insereR3(k+1, z, v, n); // insere o valor substituído no próximo endereço do vetor
    }
}

int main(){
    int N = 10;
    int v[N];
    int n = 0;
    n = Insere(0, 12, v, n);
    n = InsereR(1,13,v,n);
    n = Insere(0, 15, v, n);
    n = insereR3(3, 14, v, n); 
    for (int i=0; i<n;i++){
        printf("%d ", v[i]);
    }
      
    n = insereR2(0, 15, v, n);
    printf("\n");
    for (int i=0; i<n;i++){
        printf("%d ", v[i]);
    }
}