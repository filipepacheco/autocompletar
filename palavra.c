#include <stdio.h>
#include <stdlib.h>
#include "palavra.h"

Palavra* inicializa(void){
    return NULL;
}

Palavra* inserePalavra(Palavra* l, dadosPalavra dados){
    Palavra* novo;
    Palavra* ant = NULL;
    Palavra* ptaux = l;

    novo = malloc(sizeof(Palavra));
    novo->info = dados;

    while ((ptaux != NULL) && (ptaux->info.nome[0] < dados.nome[0]) && (ptaux->info.codigo < dados.codigo)){
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
