# ifndef LISTA
# define LISTA
struct cel {
    char *conteudo;
    struct cel *seg;
};

typedef struct cel celula;

celula *next(celula *);
void print_celula(celula *);
celula *busca(int, celula *);
void permutacaoCelula(celula *, celula *);
void permutacaoCelulaBusca(int, int, celula *);
celula *from_array(char **, int);
void assert_eq_celula(celula *, celula *);
# endif
