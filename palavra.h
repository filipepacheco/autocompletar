//struct palavra que guarda o peso e a string com a palavra
struct p{
    double peso;
    char palavra[10];
}; typedef struct p Palavra;
//lista simplesmente encadeada de Palavras
struct lp{
    Palavra info;
    struct ListaPalavra *proximo;
}; typedef struct lp ListaPalavra;
//lista simplesmente encadeada que armazena a entrada
struct le{
    char palavra[10];
    struct ListaEntrada *proximo;
}; typedef struct le ListaEntrada;

//inicializa a lista de palavras
ListaPalavra* inicializaLista(void);
//insere uma palavra numa lista ordenada pelo peso e alfabeto de palavras
ListaPalavra* inserePalavra(ListaPalavra* l, Palavra dados);
//imprime uma lista de palavras
void imprime(ListaPalavra* ptLista);
