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

void imprime(ListaPalavra* ptLista){
	ListaPalavra* ptaux;
	if (ptLista == NULL)
		puts("lista vazia");
	else
		for (ptaux=ptLista; ptaux!=NULL; ptaux=ptaux->proximo) printf("peso = %.0lf palavra = %s\n",ptaux->info.peso,ptaux->info.palavra);
}
