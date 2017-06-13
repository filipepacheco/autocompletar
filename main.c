#include <stdio.h>
#include <stdlib.h>
#include "palavra.h"
#include <string.h>

struct ListaEntrada{
    char palavra[10];
    struct ListaEntrada *proximo;
}; typedef struct ListaEntrada ListaEntrada;

ListaEntrada* inicializaEntrada(void){
    return NULL;
}

struct TNodoA
{
    int valor;
    struct TNodoA *esq;
    struct TNodoA *dir;
};
typedef struct TNodoA TipoNodo;

TipoNodo* cria_arvore(void)
{
    return NULL;
}

TipoNodo* InsereArvore(TipoNodo* a, int n)
{
    if (a == NULL)
    {
        a = (TipoNodo*) malloc(sizeof(TipoNodo));
        a->valor = n;
        a->esq = NULL;
        a->dir = NULL;
    }
    else if (n < (a->valor))
        a->esq = InsereArvore(a->esq,n);
    else
        a->dir = InsereArvore(a->dir,n);
    return a;
}

ListaEntrada* insereEntrada(ListaEntrada* l, char palavra[10]){
    ListaEntrada* novo;
    ListaEntrada* ant = NULL;
    ListaEntrada* ptaux = l;

    novo = malloc(sizeof(ListaEntrada));
    strcpy(novo->palavra, palavra);

    while ((ptaux != NULL) && (ptaux->palavra[0] < palavra[0])){
        ant = ptaux;
        ptaux = ptaux->proximo;
    }

    if(ant == NULL){
        novo->proximo = l;
        l = novo;
    }else{
        novo->proximo = ptaux;
        ant->proximo = novo;
    }
    return l;
}

void imprime(Palavra* ptLista){
	Palavra* ptaux;
	if (ptLista == NULL)
		puts("lista vazia");
	else
		for (ptaux=ptLista; ptaux!=NULL; ptaux=ptaux->proximo) printf("peso = %.0lf palavra = %s\n",ptaux->info.codigo,ptaux->info.nome);
}

void imprimeEntrada(ListaEntrada* ptLista){
	ListaEntrada* ptaux;
	if (ptLista == NULL)
		puts("lista vazia");
	else
		for (ptaux=ptLista; ptaux!=NULL; ptaux=ptaux->proximo) printf("palavra = %s\n",ptaux->palavra);
}

int main(){
    Palavra *listaWiki = inicializa();
    ListaEntrada *listaEntrada = inicializaEntrada();
    FILE *wiktionary = fopen("palavras/wiktionary.txt", "r");
    FILE *consulta = fopen("palavras/consulta.txt", "r");
    char palavraAux[50];
    dadosPalavra auxWiki;
    char linha1[50];
    char *ptr;
    double peso;

    if(consulta){
        while(!feof(consulta)){
            fscanf(consulta, "%s", palavraAux);
            listaEntrada = insereEntrada(listaEntrada, palavraAux);
        }
        imprimeEntrada(listaEntrada);
    }

    if(wiktionary){
        while(listaEntrada != NULL){
            while(!feof(wiktionary)){
                fscanf(wiktionary, "%s %s", linha1, auxWiki.nome);
                peso = strtod(linha1, &ptr);
                auxWiki.codigo = peso;
                if(strncmp(auxWiki.nome, listaEntrada->palavra, strlen(listaEntrada->palavra)) == 0){
                    listaWiki = inserePalavra(listaWiki, auxWiki);
                }
            }
            listaEntrada = listaEntrada->proximo;
            rewind(wiktionary);
        }
        imprime(listaWiki);
    }

    return 0;
}
