#include "palavra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

ListaPalavra* inicializaLista(void){
    return NULL;
}

ListaPalavra* inserePalavra(ListaPalavra* l, Palavra dados){
    ListaPalavra* novo;
    ListaPalavra* ant = NULL;
    ListaPalavra* ptaux = l;

    novo = malloc(sizeof(ListaPalavra));
    novo->info = dados;

    while ((ptaux != NULL)){
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

ListaPalavra *preencheListaPalavras(ListaPalavra *listaEntrada, FILE *consulta){
    Palavra auxIn;

    auxIn.peso = 0;
    while(!feof(consulta)){
        fscanf(consulta, "%s", auxIn.palavra);
        //organiza a estrutura de lista de entrada
        listaEntrada = inserePalavra(listaEntrada, auxIn);
    }

    return listaEntrada;
}


int imprimeSaida(FILE *saida, FILE *wiktionary, int maximo, ListaPalavra *listaEntrada)
{
    Palavra auxWiki;
    char linha1[50], *ptr;
    float auxcont = 0;
    int auxiliar;

    while(listaEntrada != NULL)
    {
        auxiliar = 0;
        fprintf(saida, "%s\n", listaEntrada->info.palavra);
        //percorre as palavras wiki
        while(!feof(wiktionary) && auxiliar < maximo)
        {
            auxcont++;
            fscanf(wiktionary, "%s %s", linha1, auxWiki.palavra);
            auxWiki.peso = strtod(linha1, &ptr);
            //se a lista de entrada dá match na lista wiki
            if(strncmp(auxWiki.palavra, listaEntrada->info.palavra, strlen(listaEntrada->info.palavra)) == 0){
                auxiliar = auxiliar + 1;
                fprintf(saida, "%15.0lf %s\n", auxWiki.peso, auxWiki.palavra);
                //listaWiki = inserePalavra(listaWiki, auxWiki);
            }
        }
        listaEntrada = listaEntrada->proximo;
        if(auxiliar == 0){
            fprintf(saida, "Nenhum resultado encontrado\n");
        }
        auxiliar = 0;
        auxcont = 0;
        rewind(wiktionary);
    }

    return 1;
}

void imprime(ListaPalavra* ptLista){
	ListaPalavra* ptaux;
	if (ptLista == NULL)
		puts("lista vazia");
	else
		for (ptaux=ptLista; ptaux!=NULL; ptaux=ptaux->proximo) printf("peso = %.0lf palavra = %s\n",ptaux->info.peso,ptaux->info.palavra);
}
