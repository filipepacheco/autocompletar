#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "palavra.h"


int main(int argc, char *argv[]){
    //abre os arquivos de entrada, processamento e saída.
    FILE *wiktionary = fopen(argv[1], "r");
    if(!wiktionary){
        printf("Nao foi possivel abrir o arquivo %s", argv[1]);
        return 0;
    }
    FILE *consulta = fopen(argv[2], "r");
    if(!consulta){
        printf("Nao foi possivel abrir o arquivo %s", argv[2]);
        return 0;
    }
    FILE *saida = fopen(argv[3], "w+");
    if(!saida){
        printf("Nao foi possivel abrir o arquivo %s", argv[3]);
        return 0;
    }

    ListaPalavra *listaEntrada = inicializaLista(); //lista de palavras de entrada
    Palavra auxWiki;
    char linha1[50], *ptr;
    float auxcont = 0;
    int auxiliar = 0;
    int maximo = atoi(argv[4]);
    clock_t t1 = clock();

    listaEntrada = preencheListaPalavras(listaEntrada, consulta);
    //percorre a lista de palavras de entrada

    while(listaEntrada != NULL){
        fprintf(saida, "%s\n", listaEntrada->info.palavra);
        //percorre as palavras wiki
        while(!feof(wiktionary) && auxiliar < maximo){
            auxcont++;
            fscanf(wiktionary, "%s %s", linha1, auxWiki.palavra);
            auxWiki.peso = strtod(linha1, &ptr);
            //se a lista de entrada dá match na lista wiki
            if(strncmp(auxWiki.palavra, listaEntrada->info.palavra, strlen(listaEntrada->info.palavra)) == 0){
                fprintf(saida, "%15.0lf %s\n", auxWiki.peso, auxWiki.palavra);
                //listaWiki = inserePalavra(listaWiki, auxWiki);
                auxiliar++;
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
    fprintf(saida, "\nTempo: %lf\n", (double)(clock() - t1) / CLOCKS_PER_SEC);
    fclose(saida);
    fclose(wiktionary);
    fclose(consulta);
    return 1;
}
