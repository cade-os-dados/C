typedef struct
{
    int idx;
    void* valores[100];
} pilha;

void* pop(pilha* p);
void* get(pilha *p);
void push(pilha* p, void* v);