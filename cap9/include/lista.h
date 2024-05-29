# ifndef LISTA
# define LISTA
struct cel {
    int conteudo;
    struct cel *seg;
};

typedef struct cel celula;

celula *new(int);
celula *next(celula *);
void print_celula(celula *);
celula *from_array(int *, int);
void assert_eq_celula(celula *, celula *);
int lenList(celula *);
# endif
