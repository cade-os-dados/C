# include <stdio.h>
# include <assert.h>

struct search {
    int (*binaria)(int, int, int[]);
};

extern const struct search busca;
