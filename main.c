#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "palavra.h"


int main(){
    //lista de palavras do wiki
    ListaPalavra *listaWiki = inicializaLista();
    //lista de palavras de entrada
    ListaPalavra *listaEntrada = inicializaLista();
    //arvore de processamento
    FILE *consulta = fopen("palavras/consulta.txt", "r"), *wiktionary;
    FILE *saida = fopen("palavras/saida.txt", "w+");
    Palavra auxWiki, auxIn;
    char linha1[50], *ptr;
    double peso;
    float diff, count = 0, auxcont = 0;
    int maximo = 5, auxiliar = 0;
    clock_t t1 = clock(),t2;

    //le o arquivo de entrada
    if(consulta){
        auxIn.peso = 0;
        while(!feof(consulta)){
            fscanf(consulta, "%s", auxIn.palavra);
            //organiza a estrutura de lista de entrada
            listaEntrada = inserePalavra(listaEntrada, auxIn);
        }
    }else
        return 0;

    fclose(consulta);
    wiktionary = fopen("palavras/wiktionary.txt", "r");
    //lê a lista de palavras wiki
    if(wiktionary){
        //percorre a lista de palavras de entrada
        while(listaEntrada != NULL){
            printf("Palavra: %s ", listaEntrada->info.palavra);
            //percorre as palavras wiki
            while(!feof(wiktionary) && auxiliar < maximo){
                count++;
                auxcont++;
                fscanf(wiktionary, "%s %s", linha1, auxWiki.palavra);
                peso = strtod(linha1, &ptr);
                auxWiki.peso = peso;
                //se a lista de entrada dá match na lista wiki
                if(strncmp(auxWiki.palavra, listaEntrada->info.palavra, strlen(listaEntrada->info.palavra)) == 0){
                    listaWiki = inserePalavra(listaWiki, auxWiki);
                    auxiliar++;
                }
            }
            listaEntrada = listaEntrada->proximo;
            auxiliar = 0;
            printf("cont: %.0f\n", auxcont);
            auxcont = 0;
            rewind(wiktionary);
        }
        //PreFixadoEsq(arvoreWiki);
    }
    else
        return 0;

    if(saida){
        //while(listaEntrada != NULL){
          //  fputs(saida, listaEntrada->info.palavra);
            while(listaWiki != NULL){
                fprintf(saida, "%10.0lf %s\n", listaWiki->info.peso, listaWiki->info.palavra);
                listaWiki = listaWiki->proximo;
            }
            //listaEntrada = listaEntrada->proximo;
        //}
        fclose(saida);
    }

    t2 = clock();
    diff = (((float)t2 - (float)t1) / 1000.0F );
    printf("Tempo: %fs\ncount: %.0f",diff, count);

    return 1;
}
