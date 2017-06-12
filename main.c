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

ListaEntrada* insereListaEntrada(ListaEntrada l, char palavra[50]){

}

void imprime(Palavra* ptLista){
	Palavra* ptaux;
	if (ptLista == NULL)
		puts("lista vazia");
	else
		for (ptaux=ptLista; ptaux!=NULL; ptaux=ptaux->proximo) printf("peso = %.0lf palavra = %s\n",ptaux->info.codigo,ptaux->info.nome);
}

int main(){
    //Palavra *listaWiki = inicializa();
    ListaEntrada *listaEntrada = inicializaEntrada();
    //FILE *wiktionary = fopen("palavras/wiktionary.txt", "r");
    FILE *consulta = fopen("palavras/consulta.txt", "r");
    char palavraAux[50];
    //dadosPalavra auxWiki;
    //char linha1[50];
    //char *ptr;
    //double peso;

    if(consulta){
        while(!feof(consulta)){
            fscanf(consulta, "%s", palavraAux);
            puts(palavraAux);
        }
    }

    /*if(arq){
        while(!feof(arq)){
            fscanf(arq, "%s %s", linha1, auxWiki.nome);
            peso = strtod(linha1, &ptr);
            auxWiki.codigo = peso;
            if(strncmp(auxWiki.nome, entrada, (sizeof(entrada) / sizeof(char)) - 1) == 0)
                listaWiki = inserePalavra(listaWiki, auxWiki);
            //printf("%.0lf %s\n",auxWiki.codigo, auxWiki.nome);
        }
        imprime(listaWiki);
    }*/

    return 0;
}
