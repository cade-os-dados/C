# include<stdio.h>

// macro
# define len(array) (sizeof(array)/sizeof(array[0]))

// 5.1.1 Suponha que, diferentemente da convenção adotada no texto
// a parte do vetor ocupada na fila é f[s..t]. Escreva o comando
// que remove um elemento da fila. Escreva o comando que insere
// um objeto y na fila.
int empty(int s, int t){
    return s == t;
}

int full(int t, int tamanho){
    return t == tamanho;
}

int pop(int s, int t){
    // se não for vazia
    if (empty(s, t) == 0){
        return s+1;
    } else {
        return s;
    }
}

int push(int f[], int t, int n, int y){
    if (full(t, n) == 0){
        f[t++] = y;
        return t;
    } else {
        return t;
    }
}

void print_fila(int f[], int s, int t){
    printf("< ");
    for (int i = s; i < t; i++){
        printf("%d ", f[i]);
    }
    printf(">");
}

int main(){
    int fila[5];
    int s = 0;
    int t = 0;
    for (int i=0; i < 5; i++){
        t = push(fila, t, len(fila), i+2);
    }
    s = pop(s, t);
    print_fila(fila, s, t);
}
