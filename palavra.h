#include <stdio.h>
//struct palavra guarda o peso, a palavra e o numero de impressoes feitas
struct p
{
    double peso;
    char palavra[10];
    int impressoes;
};
typedef struct p Palavra;
//lista simplesmente encadeada de previsoes que contem uma palavra
struct lpr
{
    Palavra info;
    struct ListaPalavra *previsoes;
};
typedef struct lpr ListaPrevisoes;
//lista simplesmente encadeada de Palavras que contem outra lista (de previsoes)
struct lp
{
    Palavra info;
    int tamanho;
    struct ListaPalavra *proximo;
    struct ListaPrevisoes *previsoes;
};
typedef struct lp ListaPalavra;
//imprime a lista encadeada preenchida no arquivo de saida
void imprimeSaida(ListaPalavra* ptLista, FILE* saida);
//preenche um lista de previsoes de uma lista lendo do arquivo de consulta
void preencheListaPrevisoes(FILE *wiktionary, int maximo, ListaPalavra *listaEntrada);
//inicializa a lista de palavras
ListaPalavra* inicializaLista(void);
//insere uma palavra numa lista
ListaPalavra* inserePalavra(ListaPalavra* l, Palavra dados);
//insere uma palavra numa lista de previsao
ListaPrevisoes* inserePrevisao(ListaPrevisoes *l, Palavra dados);
//le do arquivo de entrada e preenche uma lista simplesmente encadeada
ListaPalavra *preencheListaPalavras(ListaPalavra *listaEntrada, FILE *consulta);
