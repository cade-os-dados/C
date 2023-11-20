# include <stdio.h>

// vamos desenvolver um algoritmo de busca e remoção
// que devolve o novo valor de n

void bubbleSort(int v[], int n){
    int elemento;
    int swaps = 1;
    while (swaps > 0){
        swaps = 0;
        for (int i=0; i<n-1; i++){
            elemento = v[i];
            // swap
            if (elemento > v[i+1]){
                v[i] = v[i+1];
                v[i+1] = elemento;
                swaps++;
            }
        }
    }
}

int buscaBinaria(int k, int v[], int inicio, int final){
    if (inicio>=final)
        return -1;
    int busca = (final + inicio) / 2;
    if (v[busca] == k)
        return busca;
    else if (v[busca] > k)
        return buscaBinaria(k, v, inicio, busca-1);
    else
        return buscaBinaria(k, v, busca+1, final);
}

int remover(int k, int v[], int n){
    int indice = buscaBinaria(k, v, 0, n);
    while (indice != -1){
        for (int i = indice; i<n-1;i++)
            v[i] = v[i+1];
        n = n-1;
        indice = buscaBinaria(k, v, 0, n);
    }
    return n;
}

void print_vetor(int v[], int n){
    printf("[ ");
    for (int i=0;i<n;i++){
        printf("%d ", v[i]);
    }
    printf("]\n");
}

// funcao do livro
// muito mais simples...
int removeZeros(int v[], int n){
    int i = 0, j;
    for (j=0; j < n; j++){
        if (v[j] != 0){
            v[i] = v[j];
            i += 1;
        }
    }
    return i;
}

int removeZerosR(int v[], int n){
    int m;
    if (n==0) return 0;
    m = removeZerosR(v, n-1);
    // mantem o índice
    if (v[n-1] == 0) return m;
    // passa o valor para o índice
    v[m] = v[n-1];
    // passa para o próximo índice
    return m+1;
}

// 3.5.1 Critique a seguinte variante da função RemoveZeros
int removeZeros2(int v[], int n){
    int i, j;
    for (i = n-1; i >= 0; i--){
        // ineficiente
        // está realocando o vetor todo, toda vez que encontra zeros
        if (v[i] == 0){ 
            for (j=i;j<n-1;j++) v[j] = v[j+1]; 
            --n;
        }
    }
    return n;
}

// 3.5.2 Critique a seguinte versão da função removeZeros
// funcao nao funciona se tiver dois zeros seguidos
int removeZeros3(int v[], int n){
    int i, j;
    for (i=0; i < n; i++)
        if (v[i] == 0) {
            for (j = i; j+1 < n; j++) v[j] = v[j+1];
            n -= 1;
        }
    return n;
}

// 3.5.3 Critique a seguinte versão da função removeZeros.
// Há alguma maneira simples de corrigir o código?
int removeZeros4(int v[], int n){
    int i,z = 0;
    for (i=0; i < n; i++){
        if (v[i] == 0) z += 1; 
        v[i-z] = v[i]; // tem comportamento indefinido
        // quando i = 0 e z = 1
        // criando problema de vazamento de memória
    }
    return n - z;
}

// para corrigir podemos acrescentar
// a instrucao else
int removeZeros5(int v[], int n){
    int i,z = 0;
    for (i=0; i < n; i++){
        if (v[i] == 0) z += 1; 
        else v[i-z] = v[i];
        
    }
    return n - z;
}

int main(){
    // testando sort
    int v[17] = {1,2,4,5,3,5,1,0,3,4,3,3,2,1,2,12,0};
    int n = sizeof(v) / sizeof(v[0]);
    bubbleSort(v, n);
    n = remover(3, v, n);
    print_vetor(v, n);
    // n = removeZeros2(v, n); // funciona
    // n = removeZeros3(v, n); // nao funciona
    n = removeZeros5(v, n);
    print_vetor(v, n);
}